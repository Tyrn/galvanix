#include "unity.h"
#include "pmru.h"
#include <string.h>
#include <stdbool.h>

void setUp(void)
{
}

void tearDown(void)
{
}

typedef char cell_matrix_type[LCD_CELL_HEIGHT][LCD_CELL_WIDTH + 1];

char* create_cell_line(int8_t ln)
{
  static char line[LCD_CELL_WIDTH + 1];

  memset(line, '\0', LCD_CELL_WIDTH + 1);
  ln <<= 8 - LCD_CELL_WIDTH;
  for (int i = 0; i < LCD_CELL_WIDTH; i++)
  {
    line[i] = (ln < 0) ? '*' : ' ';
    ln <<= 1;
  }
  return line;
}

void test_create_cell_line(void)
{
  TEST_ASSERT_EQUAL_STRING(create_cell_line(0x15), "* * *");
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
  cell_matrix_type m1 =
  {
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "*****",
      "    *"
  };
  cell_matrix_type m2 =
  {
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "*****",
      "    *"
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(&m1, &m2));
}

void test_pmru_lcd_cell_stub(void)
{
  cell_matrix_type matrix =
  {
      "     ",
      " * * ",
      "*****",
      "*****",
      "*****",
      " *** ",
      "  *  ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'*'), &matrix));
}

void test_pmru_lcd_cell_b(void)
{
  cell_matrix_type matrix =
  {
      "**** ",
      "*    ",
      "*    ",
      "**** ",
      "*   *",
      "*   *",
      "**** ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Б'), &matrix));
}

void test_pmru_lcd_cell_g(void)
{
  cell_matrix_type matrix =
  {
      "*****",
      "*    ",
      "*    ",
      "*    ",
      "*    ",
      "*    ",
      "*    ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Г'), &matrix));
}

void test_pmru_lcd_cell_d(void)
{
  cell_matrix_type matrix =
  {
      "  ** ",
      " * * ",
      " * * ",
      " * * ",
      " * * ",
      "*****",
      "*   *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Д'), &matrix));
}

void test_pmru_lcd_cell_yo(void)
{
  cell_matrix_type matrix =
  {
      " * * ",
      "*****",
      "*    ",
      "**** ",
      "*    ",
      "*    ",
      "*****",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ё'), &matrix));
}

void test_pmru_lcd_cell_zh(void)
{
  cell_matrix_type matrix =
  {
      "  *  ",
      "* * *",
      "* * *",
      " *** ",
      "* * *",
      "* * *",
      "  *  ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ж'), &matrix));
}

void test_pmru_lcd_cell_z(void)
{
  cell_matrix_type matrix =
  {
      " *** ",
      "*   *",
      "    *",
      "  ** ",
      "    *",
      "*   *",
      " *** ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'З'), &matrix));
}

void test_pmru_lcd_cell_i(void)
{
  cell_matrix_type matrix =
  {
      "*   *",
      "*   *",
      "*  **",
      "* * *",
      "**  *",
      "*   *",
      "*   *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'И'), &matrix));
}

void test_pmru_lcd_cell_j(void)
{
  cell_matrix_type matrix =
  {
      " *** ",
      "* * *",
      "*   *",
      "*  **",
      "* * *",
      "**  *",
      "*   *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Й'), &matrix));
}

void test_pmru_lcd_cell_l(void)
{
  cell_matrix_type matrix =
  {
      "  ***",
      " *  *",
      " *  *",
      " *  *",
      " *  *",
      " *  *",
      "*   *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Л'), &matrix));
}

void test_pmru_lcd_cell_p(void)
{
  cell_matrix_type matrix =
  {
      "*****",
      "*   *",
      "*   *",
      "*   *",
      "*   *",
      "*   *",
      "*   *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'П'), &matrix));
}

void test_pmru_lcd_cell_u(void)
{
  cell_matrix_type matrix =
  {
      "*   *",
      "*   *",
      "*   *",
      " ****",
      "    *",
      "    *",
      " *** ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'У'), &matrix));
}

void test_pmru_lcd_cell_f(void)
{
  cell_matrix_type matrix =
  {
      " *** ",
      "* * *",
      "* * *",
      "* * *",
      " *** ",
      "  *  ",
      "  *  ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ф'), &matrix));
}

void test_pmru_lcd_cell_ts(void)
{
  cell_matrix_type matrix =
  {
      "*  * ",
      "*  * ",
      "*  * ",
      "*  * ",
      "*  * ",
      "*****",
      "    *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ц'), &matrix));
}

void test_pmru_lcd_cell_ch(void)
{
  cell_matrix_type matrix =
  {
      "*   *",
      "*   *",
      "*   *",
      " ****",
      "    *",
      "    *",
      "    *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ч'), &matrix));
}

void test_pmru_lcd_cell_sh(void)
{
  cell_matrix_type matrix =
  {
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "*****",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ш'), &matrix));
}

void test_pmru_lcd_cell_shch(void)
{
  cell_matrix_type matrix =
  {
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "* * *",
      "*****",
      "    *"
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Щ'), &matrix));
}

void test_pmru_lcd_cell_ie(void)
{
  cell_matrix_type matrix =
  {
      "**   ",
      " *   ",
      " *   ",
      " *** ",
      " *  *",
      " *  *",
      " *** ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ъ'), &matrix));
}

void test_pmru_lcd_cell_y(void)
{
  cell_matrix_type matrix =
  {
      "*   *",
      "*   *",
      "**  *",
      "* * *",
      "* * *",
      "* * *",
      "**  *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ы'), &matrix));
}

void test_pmru_lcd_cell_q(void)
{
  cell_matrix_type matrix =
  {
      "*    ",
      "*    ",
      "*    ",
      "***  ",
      "*  * ",
      "*  * ",
      "***  ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ь'), &matrix));
}

void test_pmru_lcd_cell_eh(void)
{
  cell_matrix_type matrix =
  {
      " *** ",
      "*   *",
      "    *",
      " ****",
      "    *",
      "*   *",
      " *** ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Э'), &matrix));
}

void test_pmru_lcd_cell_yu(void)
{
  cell_matrix_type matrix =
  {
      "*  * ",
      "* * *",
      "* * *",
      "*** *",
      "* * *",
      "* * *",
      "*  * ",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Ю'), &matrix));
}

void test_pmru_lcd_cell_ya(void)
{
  cell_matrix_type matrix =
  {
      " ****",
      "*   *",
      "*   *",
      " ****",
      "  * *",
      " *  *",
      "*   *",
      "     "
  };

  TEST_ASSERT_TRUE(cell_matrix_eq(create_cell_matrix(L'Я'), &matrix));
}
// @formatter:on
