#include "../s21_decimal.h"
#include <check.h>

START_TEST(test_test)
{
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite *test_arithmetic(void)
{
  Suite *s = suite_create("Arithmetic test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, test_test);

  suite_add_tcase(s, tc);
  return s;
}