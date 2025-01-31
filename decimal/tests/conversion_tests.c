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

START_TEST(int_to_decimal_zero) {
  s21_decimal number_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int number_int = 0;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_positive) {
  s21_decimal number_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {{0x0000007B, 0x00000000, 0x00000000, 0x00000000}}; // 123 в decimal
  int number_int = 123;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_negative) {
  s21_decimal number_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {{0x0000007B, 0x00000000, 0x00000000, 0x80000000}}; // -123 в decimal
  int number_int = -123;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_max_int) {
  s21_decimal number_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}}; // INT_MAX
  int number_int = 2147483647;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_min_int) {
  s21_decimal number_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x80000000}}; // INT_MIN
  int number_int = -2147483647;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(decimal_to_int_zero) {
  s21_decimal number_decimal = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int result_int = 0;
  int expected_int = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_positive) {
  s21_decimal number_decimal = {{0x0000007B, 0x00000000, 0x00000000, 0x00000000}}; // 123 в decimal
  int result_int = 0;
  int expected_int = 123;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_negative) {
  s21_decimal number_decimal = {{0x0000007B, 0x00000000, 0x00000000, 0x80000000}}; // -123 в decimal
  int result_int = 0;
  int expected_int = -123;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_max_int) {
  s21_decimal number_decimal = {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}}; // INT_MAX
  int result_int = 0;
  int expected_int = 2147483647;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_min_int) {
  s21_decimal number_decimal = {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x80000000}}; // INT_MIN
  int result_int = 0;
  int expected_int = -2147483647;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_with_fraction) {
  s21_decimal number_decimal = {{0x0000007B, 0x00000000, 0x00000000, 0x00010000}}; // 123 * 10^(-1) = 12.3
  int result_int = 0;
  int expected_int = 12; // Должно округляться вниз
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST



Suite *test_conversion(void) {
  Suite *s = suite_create("Conversion test");
  TCase *tc = tcase_create("Tests");

  //tcase_add_test(tc, float_to_decimal_1);
  tcase_add_test(tc, int_to_decimal_zero);
  tcase_add_test(tc, int_to_decimal_positive);
  tcase_add_test(tc, int_to_decimal_negative);
  tcase_add_test(tc, int_to_decimal_max_int);
  tcase_add_test(tc, int_to_decimal_min_int);
  
  tcase_add_test(tc, decimal_to_int_zero);
  tcase_add_test(tc, decimal_to_int_positive);
  tcase_add_test(tc, decimal_to_int_negative);
  tcase_add_test(tc, decimal_to_int_max_int);
  tcase_add_test(tc, decimal_to_int_min_int);
  tcase_add_test(tc, decimal_to_int_with_fraction);

  suite_add_tcase(s, tc);
  return s;
}