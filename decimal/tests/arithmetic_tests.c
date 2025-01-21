#include <check.h>

#include "../s21_decimal.h"

START_TEST(add_int_both_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000030, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  ck_assert_int_eq(res1.bits[0], res2.bits[0]);
  ck_assert_int_eq(res1.bits[1], res2.bits[1]);
  ck_assert_int_eq(res1.bits[2], res2.bits[2]);
  ck_assert_int_eq(res1.bits[3], res2.bits[3]);
}
END_TEST

START_TEST(add_int_both_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000030, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  ck_assert_int_eq(res1.bits[0], res2.bits[0]);
  ck_assert_int_eq(res1.bits[1], res2.bits[1]);
  ck_assert_int_eq(res1.bits[2], res2.bits[2]);
  ck_assert_int_eq(res1.bits[3], res2.bits[3]);
}
END_TEST

START_TEST(add_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  ck_assert_int_eq(res1.bits[0], res2.bits[0]);
  ck_assert_int_eq(res1.bits[1], res2.bits[1]);
  ck_assert_int_eq(res1.bits[2], res2.bits[2]);
  ck_assert_int_eq(res1.bits[3], res2.bits[3]);
}
END_TEST

START_TEST(add_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  ck_assert_int_eq(res1.bits[0], res2.bits[0]);
  ck_assert_int_eq(res1.bits[1], res2.bits[1]);
  ck_assert_int_eq(res1.bits[2], res2.bits[2]);
  ck_assert_int_eq(res1.bits[3], res2.bits[3]);
}
END_TEST

START_TEST(add_not_int_both_positive) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00004662, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  ck_assert_int_eq(res1.bits[0], res2.bits[0]);
  ck_assert_int_eq(res1.bits[1], res2.bits[1]);
  ck_assert_int_eq(res1.bits[2], res2.bits[2]);
  ck_assert_int_eq(res1.bits[3], res2.bits[3]);
}
END_TEST

START_TEST(add_not_int_both_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00004662, 0x00000000, 0x00000000, 0x80030000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  ck_assert_int_eq(res1.bits[0], res2.bits[0]);
  ck_assert_int_eq(res1.bits[1], res2.bits[1]);
  ck_assert_int_eq(res1.bits[2], res2.bits[2]);
  ck_assert_int_eq(res1.bits[3], res2.bits[3]);
}
END_TEST

Suite *test_arithmetic(void) {
  Suite *s = suite_create("Arithmetic test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, add_int_both_positive);
  tcase_add_test(tc, add_int_both_negative);
  tcase_add_test(tc, add_int_first_positive_second_negative);
  tcase_add_test(tc, add_int_first_negative_second_positive);
  tcase_add_test(tc, add_not_int_both_positive);
  tcase_add_test(tc, add_not_int_both_negative);

  suite_add_tcase(s, tc);
  return s;
}