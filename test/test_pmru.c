#include "unity.h"
#include "pmru.h"
#include <string.h>
#include <stdbool.h>

static
char rus[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
static
char mix[] = "AБBГДEЁЖЗИЙKЛMHOПPCTУФXЦЧШЩЪЫЬЭЮЯ"; /* 11 characters replaced with English counterparts. */

void setUp(void)
{
}

void tearDown(void)
{
}

void test_pmru_pmru_s_next(void)
{
  char tst[] = "aБГdЮЯ";
  struct pmru_s uni;

  pmru_s_first(&uni, tst);
  TEST_ASSERT_EQUAL_STRING(tst, uni.c);
  TEST_ASSERT_TRUE(uni.width == 1);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("БГdЮЯ", uni.c);
  TEST_ASSERT_TRUE(uni.width == 2);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("ГdЮЯ", uni.c);
  TEST_ASSERT_TRUE(uni.width == 2);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("dЮЯ", uni.c);
  TEST_ASSERT_TRUE(uni.width == 1);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("ЮЯ", uni.c);
  TEST_ASSERT_TRUE(uni.width == 2);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("Я", uni.c);
  TEST_ASSERT_TRUE(uni.width == 2);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("", uni.c);
  TEST_ASSERT_TRUE(uni.width == 0);
  pmru_s_next(&uni);
  TEST_ASSERT_EQUAL_STRING("", uni.c);
  TEST_ASSERT_TRUE(uni.width == 0);
}

void test_pmru_pmru_s_len(void)
{
  TEST_ASSERT_TRUE(strlen(rus) == 66);
  TEST_ASSERT_TRUE(strlen(mix) == 55);
  TEST_ASSERT_TRUE(pmru_s_len(rus) == 33);
  TEST_ASSERT_TRUE(pmru_s_len(mix) == 33);
  TEST_ASSERT_TRUE(pmru_s_len("") == 0);
  TEST_ASSERT_TRUE(pmru_s_len("Б") == 1);
  TEST_ASSERT_TRUE(pmru_s_len("Q") == 1);
}

void test_pmru_pmru_nc_add_char(void)
{
  struct pmru_nc nc;

  pmru_nc_reset(&nc);
  pmru_nc_add_char(&nc, L'Ж');
  pmru_nc_add_char(&nc, L'Ф');
  pmru_nc_add_char(&nc, L'Ж');
  pmru_nc_add_char(&nc, pmru_unichar_head("Б"));
  pmru_nc_add_char(&nc, pmru_unichar_head("Г"));
  pmru_nc_add_char(&nc, pmru_unichar_head("Г"));
  pmru_nc_add_char(&nc, pmru_unichar_head("Д"));
  TEST_ASSERT_TRUE(nc.notch == 5);
  TEST_ASSERT_TRUE(sizeof(unichar_t) == 2);
}

void test_pmru_pmru_nc_add_str(void)
{
  struct pmru_nc nc;

  pmru_nc_add_str(&nc, "abba");
  TEST_ASSERT_TRUE(nc.notch == 0);
  pmru_nc_add_str(&nc, "ЙKЛMHOПPCTУ");
  TEST_ASSERT_TRUE(nc.notch == 4);
  pmru_nc_add_str(&nc, mix);
  TEST_ASSERT_TRUE(nc.notch == 8);
}

void test_pmru_pmru_lcd_byte(void)
{
  TEST_ASSERT_TRUE(pmru_lcd_byte(0x28, 0) == 0x80842024);
  TEST_ASSERT_TRUE(pmru_lcd_byte(0x28, 1) == 0x81852125);
}

typedef char cell_matrix_type[LCD_CELL_HEIGHT][LCD_CELL_WIDTH + 1];

char* create_cell_line(int8_t ln)
{
  static char line[LCD_CELL_WIDTH + 1];

  memset(line, '\0', LCD_CELL_WIDTH + 1);
  for (int i = 0; i < LCD_CELL_WIDTH; i++)
  {
    line[i] = (ln < 0) ? '*' : ' ';
    ln <<= 1;
  }
  return line;
}

void test_create_cell_line(void)
{
  TEST_ASSERT_EQUAL_STRING(create_cell_line(0x15), "   * * *");
}

cell_matrix_type* create_cell_matrix(unichar_t cyr_ch)
{
  static cell_matrix_type matrix;
  uint8_t *cell = pmru_get_cell(cyr_ch);

  for (int i = 0; i < LCD_CELL_HEIGHT; i++)
  {
    strcpy(matrix[i], create_cell_line(cell[i]));
  }
  return &matrix;
}

bool cell_matrix_eq(cell_matrix_type *m1, cell_matrix_type *m2)
{
  for (int i = 0; i < LCD_CELL_HEIGHT; i++)
  {
    if (strcmp((*m1)[i], (*m2)[i]))
    {
      return false;
    }
  }
  return true;
}

// @formatter:off
void test_cell_matrix_eq(void)
{
  static cell_matrix_type m1 =
  {
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   *****",
      "       *"
  };
  static cell_matrix_type m2 =
  {
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   *****",
      "       *"
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(&m1, &m2));
}
/*
void test_pmru_lcd_cell_(void)
{
  static cell_matrix_type matrix =
  {
      "        ",
      "        ",
      "        ",
      "        ",
      "        ",
      "        ",
      "        ",
      "        "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L''), &matrix));
}
*/
void test_pmru_lcd_cell_shch(void)
{
  static cell_matrix_type matrix =
  {
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   * * *",
      "   *****",
      "       *"
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Щ'), &matrix));
}
// @formatter:on
