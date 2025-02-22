#include "helpers_test.h"

START_TEST(equal_true) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 1);
}
END_TEST

START_TEST(equal_false) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 0);
}
END_TEST

START_TEST(equal_false_different_scales) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00100000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(num1, num2), 0);
}
END_TEST

START_TEST(not_equal_true) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 0);
}
END_TEST

START_TEST(not_equal_false) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), 1);
}
END_TEST

START_TEST(greater_true) {
  s21_decimal num1 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 1);
}
END_TEST

START_TEST(greater_false) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 0);
}
END_TEST

START_TEST(greater_false_different_sign) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_greater(num1, num2), 0);
}
END_TEST

START_TEST(less_true) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_less(num1, num2), 1);
}
END_TEST

START_TEST(less_false) {
  s21_decimal num1 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_less(num1, num2), 0);
}
END_TEST

START_TEST(less_false_different_sign) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_less(num1, num2), 1);
}
END_TEST

START_TEST(greater_or_equal_true) {
  s21_decimal num1 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(greater_or_equal_false) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 0);
}
END_TEST

START_TEST(greater_or_equal_false_different_sign) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), 0);
}
END_TEST

START_TEST(less_or_equal_true) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

START_TEST(less_or_equal_false) {
  s21_decimal num1 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 0);
}
END_TEST

START_TEST(less_or_equal_false_different_sign) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), 1);
}
END_TEST

Suite *test_comparison(void) {
  Suite *s = suite_create("Comparison test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, equal_true);
  tcase_add_test(tc, equal_false);
  tcase_add_test(tc, equal_false_different_scales);

  tcase_add_test(tc, not_equal_true);
  tcase_add_test(tc, not_equal_false);

  tcase_add_test(tc, greater_true);
  tcase_add_test(tc, greater_false);
  tcase_add_test(tc, greater_false_different_sign);

  tcase_add_test(tc, less_true);
  tcase_add_test(tc, less_false);
  tcase_add_test(tc, less_false_different_sign);

  tcase_add_test(tc, greater_or_equal_true);
  tcase_add_test(tc, greater_or_equal_false);
  tcase_add_test(tc, greater_or_equal_false_different_sign);

  tcase_add_test(tc, less_or_equal_true);
  tcase_add_test(tc, less_or_equal_false);
  tcase_add_test(tc, less_or_equal_false_different_sign);

  suite_add_tcase(s, tc);
  return s;
}