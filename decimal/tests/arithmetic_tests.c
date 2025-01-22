#include <check.h>

#include "../s21_decimal.h"

void comparison(s21_decimal num1, s21_decimal num2) {
  ck_assert_int_eq(num1.bits[0], num2.bits[0]);
  ck_assert_int_eq(num1.bits[1], num2.bits[1]);
  ck_assert_int_eq(num1.bits[2], num2.bits[2]);
  ck_assert_int_eq(num1.bits[3], num2.bits[3]);
}

START_TEST(add_int_both_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000030, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_int_both_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000030, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_not_int_both_positive) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00004662, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_not_int_both_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00004662, 0x00000000, 0x00000000, 0x80030000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_not_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00001A06, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(add_not_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00001A06, 0x00000000, 0x00000000, 0x80030000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_int_both_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_int_both_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000030, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000030, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_not_int_both_positive) {
  s21_decimal num2 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num1 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00001A06, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_sub(num2, num1, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_not_int_both_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00001A06, 0x00000000, 0x00000000, 0x80030000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_not_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00004662, 0x00000000, 0x00000000, 0x00030000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_not_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00004662, 0x00000000, 0x00000000, 0x80030000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(sub_int_equals) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal num2 = {{0x000004D2, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(arithmetic_too_large_both_max) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 1);
}
END_TEST

START_TEST(arithmetic_too_large_first_max) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00100000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 1);
}
END_TEST

START_TEST(arithmetic_too_large_second_max) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00100000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 1);
}
END_TEST

START_TEST(arithmetic_too_small_add_1) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res), 2);
}
END_TEST

START_TEST(arithmetic_too_small_add_2) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res), 2);
}
END_TEST

START_TEST(arithmetic_too_large_sub_1) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res), 1);
}
END_TEST

START_TEST(arithmetic_too_small_sub_1) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res), 2);
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
  tcase_add_test(tc, add_not_int_first_positive_second_negative);
  tcase_add_test(tc, add_not_int_first_negative_second_positive);

  tcase_add_test(tc, sub_int_both_positive);
  tcase_add_test(tc, sub_int_both_negative);
  tcase_add_test(tc, sub_int_first_positive_second_negative);
  tcase_add_test(tc, sub_int_first_negative_second_positive);
  tcase_add_test(tc, sub_not_int_both_positive);
  tcase_add_test(tc, sub_not_int_both_negative);
  tcase_add_test(tc, sub_not_int_first_positive_second_negative);
  tcase_add_test(tc, sub_not_int_first_negative_second_positive);
  tcase_add_test(tc, sub_int_equals);

  tcase_add_test(tc, arithmetic_too_large_both_max);
  tcase_add_test(tc, arithmetic_too_large_first_max);
  tcase_add_test(tc, arithmetic_too_large_second_max);
  tcase_add_test(tc, arithmetic_too_small_add_1);
  // tcase_add_test(tc, arithmetic_too_small_add_2);
  tcase_add_test(tc, arithmetic_too_large_sub_1);
  tcase_add_test(tc, arithmetic_too_small_sub_1);

  suite_add_tcase(s, tc);
  return s;
}