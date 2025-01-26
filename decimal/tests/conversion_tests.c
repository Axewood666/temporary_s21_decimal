#include "helpers_test.h"

START_TEST(float_to_decimal_1) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00030000}};
  float number_float = 123.456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

Suite *test_conversion(void) {
  Suite *s = suite_create("Conversion test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, float_to_decimal_1);

  suite_add_tcase(s, tc);
  return s;
}