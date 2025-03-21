#include "helpers_test.h"

START_TEST(int_to_decimal_zero) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int number_int = 0;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_positive) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0000007B, 0x00000000, 0x00000000, 0x00000000}};
  int number_int = 123;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_negative) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0000007B, 0x00000000, 0x00000000, 0x80000000}};
  int number_int = -123;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_max_int) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}};  // INT_MAX
  int number_int = 2147483647;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_min_int) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x7FFFFFFF, 0x00000000, 0x00000000, 0x80000000}};  // INT_MIN
  int number_int = -2147483647;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(int_to_decimal_dst_null) {
  int number_int = -2147483647;
  ck_assert_int_eq(s21_from_int_to_decimal(number_int, NULL), 1);
}
END_TEST

START_TEST(decimal_to_int_zero) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int result_int = 0;
  int expected_int = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_positive) {
  s21_decimal number_decimal = {
      {0x0000007B, 0x00000000, 0x00000000, 0x00000000}};
  int result_int = 0;
  int expected_int = 123;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_negative) {
  s21_decimal number_decimal = {
      {0x0000007B, 0x00000000, 0x00000000, 0x80000000}};
  int result_int = 0;
  int expected_int = -123;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_max_int) {
  s21_decimal number_decimal = {
      {0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}};  // INT_MAX
  int result_int = 0;
  int expected_int = 2147483647;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_min_int) {
  s21_decimal number_decimal = {
      {0x7FFFFFFF, 0x00000000, 0x00000000, 0x80000000}};  // INT_MIN
  int result_int = 0;
  int expected_int = -2147483647;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_with_fraction) {
  s21_decimal number_decimal = {{0x0000007B, 0x00000000, 0x00000000,
                                 0x00010000}};  // 123 * 10^(-1) = 12.3
  int result_int = 0;
  int expected_int = 12;
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, &result_int), 0);
  ck_assert_int_eq(result_int, expected_int);
}
END_TEST

START_TEST(decimal_to_int_false_null_ptr) {
  s21_decimal number_decimal = {
      {0x0000007B, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(number_decimal, NULL), 1);
}
END_TEST

START_TEST(decimal_to_int_more_max_int_1) {
  s21_decimal number_decimal = {
      {0x7FFFFFFF, 0x00000001, 0x00000000, 0x00000000}};
  int result_int = 0;
  int res = s21_from_decimal_to_int(number_decimal, &result_int);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(decimal_to_int_more_max_int_2) {
  s21_decimal number_decimal = {
      {0x7FFFFFFF, 0x00000000, 0x00000001, 0x00000000}};
  int result_int = 0;
  int res = s21_from_decimal_to_int(number_decimal, &result_int);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(
    float_to_decimal_positive_number_without_fractional_part_greater_10) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00000000}};
  float number_float = 123456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(
    float_to_decimal_negative_number_without_fractional_part_greater_10) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80000000}};
  float number_float = -123456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(float_to_decimal_positive_number_with_fractional_part_greater_10) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00030000}};
  float number_float = 123.456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(float_to_decimal_negative_number_with_fractional_part_greater_10) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80030000}};
  float number_float = -123.456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(float_to_decimal_positive_number_with_fractional_part_between_1_10) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00050000}};
  float number_float = 1.23456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(float_to_decimal_positive_number_with_fractional_part_less_1) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00060000}};
  float number_float = 0.123456;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(
    float_to_decimal_positive_number_without_fractional_part_greater_10_round) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00BC6150, 0x00000000, 0x00000000, 0x00000000}};
  float number_float = 12345678;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(
    float_to_decimal_negative_number_with_fractional_part_greater_10_round) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x0012D688, 0x00000000, 0x00000000, 0x80040000}};
  float number_float = -123.456789;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(float_to_decimal_error_dst_null) {
  float number_float = -123.456789;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, NULL), 1);
}
END_TEST

START_TEST(float_to_decimal_zero) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  float number_float = 0;
  ck_assert_int_eq(s21_from_float_to_decimal(number_float, &number_decimal), 0);
  comparison(number_decimal, result_decimal);
}
END_TEST

START_TEST(float_to_decimal_scr_isnan) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  float number_float = 0;
  ck_assert_int_eq(s21_from_float_to_decimal(NAN, &number_decimal), 1);
}
END_TEST

START_TEST(float_to_decimal_scr_isinf) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  float number_float = 0;
  ck_assert_int_eq(s21_from_float_to_decimal(INFINITY, &number_decimal), 1);
}
END_TEST

START_TEST(decimal_to_float_positive_number_without_fractional_part) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00000000}};
  float result_float = 0;
  float extended_float = 123456;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &result_float), 0);
  ck_assert_float_eq(result_float, extended_float);
}
END_TEST

START_TEST(decimal_to_float_negative_number_without_fractional_part) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80000000}};
  float result_float = 0;
  float extended_float = -123456;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &result_float), 0);
  ck_assert_float_eq(result_float, extended_float);
}
END_TEST

START_TEST(decimal_to_float_positive_number_with_fractional_part) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00030000}};
  float result_float = 0;
  float extended_float = 123.456;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &result_float), 0);
  ck_assert_float_eq(result_float, extended_float);
}
END_TEST

START_TEST(decimal_to_float_negative_number_with_fractional_part) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80030000}};
  float result_float = 0;
  float extended_float = -123.456;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &result_float), 0);
  ck_assert_float_eq(result_float, extended_float);
}
END_TEST

START_TEST(decimal_to_float_error_dst_null) {
  s21_decimal number_decimal;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, NULL), 1);
}
END_TEST

START_TEST(decimal_to_float_error_dst_big_1) {
  s21_decimal number_decimal = {
      {0x0012D688, 0xFFFFFFFF, 0x00000000, 0x80040000}};
  float number_float = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &number_float), 1);
}
END_TEST

START_TEST(decimal_to_float_error_dst_big_2) {
  s21_decimal number_decimal = {
      {0x0012D688, 0x00000000, 0x0000000F, 0x80040000}};
  float number_float = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &number_float), 1);
}
END_TEST

START_TEST(decimal_to_float_zero) {
  s21_decimal number_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x80040000}};
  float result_float = 0;
  float extended_float = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(number_decimal, &result_float), 0);
  ck_assert_float_eq(result_float, extended_float);
}
END_TEST

Suite *test_conversion(void) {
  Suite *s = suite_create("Conversion test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, int_to_decimal_zero);
  tcase_add_test(tc, int_to_decimal_positive);
  tcase_add_test(tc, int_to_decimal_negative);
  tcase_add_test(tc, int_to_decimal_max_int);
  tcase_add_test(tc, int_to_decimal_min_int);
  tcase_add_test(tc, int_to_decimal_dst_null);

  tcase_add_test(tc, decimal_to_int_zero);
  tcase_add_test(tc, decimal_to_int_positive);
  tcase_add_test(tc, decimal_to_int_negative);
  tcase_add_test(tc, decimal_to_int_max_int);
  tcase_add_test(tc, decimal_to_int_min_int);
  tcase_add_test(tc, decimal_to_int_with_fraction);
  tcase_add_test(tc, decimal_to_int_false_null_ptr);
  tcase_add_test(tc, decimal_to_int_more_max_int_1);
  tcase_add_test(tc, decimal_to_int_more_max_int_2);

  tcase_add_test(
      tc, float_to_decimal_positive_number_without_fractional_part_greater_10);
  tcase_add_test(
      tc, float_to_decimal_negative_number_without_fractional_part_greater_10);
  tcase_add_test(
      tc, float_to_decimal_positive_number_with_fractional_part_greater_10);
  tcase_add_test(
      tc, float_to_decimal_negative_number_with_fractional_part_greater_10);
  tcase_add_test(
      tc, float_to_decimal_positive_number_with_fractional_part_between_1_10);
  tcase_add_test(tc,
                 float_to_decimal_positive_number_with_fractional_part_less_1);
  tcase_add_test(
      tc,
      float_to_decimal_positive_number_without_fractional_part_greater_10_round);
  tcase_add_test(
      tc,
      float_to_decimal_negative_number_with_fractional_part_greater_10_round);
  tcase_add_test(tc, float_to_decimal_error_dst_null);
  tcase_add_test(tc, float_to_decimal_zero);
  tcase_add_test(tc, float_to_decimal_scr_isnan);
  tcase_add_test(tc, float_to_decimal_scr_isinf);

  tcase_add_test(tc, decimal_to_float_positive_number_without_fractional_part);
  tcase_add_test(tc, decimal_to_float_negative_number_without_fractional_part);
  tcase_add_test(tc, decimal_to_float_positive_number_with_fractional_part);
  tcase_add_test(tc, decimal_to_float_negative_number_with_fractional_part);
  tcase_add_test(tc, decimal_to_float_error_dst_null);
  tcase_add_test(tc, decimal_to_float_zero);

  suite_add_tcase(s, tc);
  return s;
}