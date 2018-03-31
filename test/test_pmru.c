#include "unity.h"
#include "pmru.h"
#include <string.h>

static
char rus[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
static
char mix[] = "AБBГДEЁЖЗИЙKЛMHOПPCTУФXЦЧШЩЪЫЬЭЮЯ"; // 11 characters replaced
                                                  // with English counterparts.


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
  pmru_nc_add_char(&nc, pmru_wchar_head("Б"));
  pmru_nc_add_char(&nc, pmru_wchar_head("Г"));
  pmru_nc_add_char(&nc, pmru_wchar_head("Г"));
  pmru_nc_add_char(&nc, pmru_wchar_head("Д"));
  TEST_ASSERT_TRUE(nc.len == 5);
  TEST_ASSERT_TRUE(sizeof(wchar_t) == 4);
}

void test_pmru_pmru_nc_add_str(void)
{
  struct pmru_nc nc;

  pmru_nc_add_str(&nc, "abba");
  TEST_ASSERT_TRUE(nc.len == 0);
  pmru_nc_add_str(&nc, "ЙKЛMHOПPCTУ");
  TEST_ASSERT_TRUE(nc.len == 4);
  pmru_nc_add_str(&nc, mix);
  TEST_ASSERT_TRUE(nc.len == 8);
}
