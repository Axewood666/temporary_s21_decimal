#include "helpers_test.h"

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

START_TEST(add_too_large_both_max) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 1);
}
END_TEST

START_TEST(add_too_large_first_max) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00100000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 1);
}
END_TEST

START_TEST(add_too_large_second_max) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00100000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res1), 1);
}
END_TEST

START_TEST(add_zero_scale_negative_first_value) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal num2 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_add(num1, num2, &res), 2);
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

START_TEST(sub_too_large) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res), 1);
}
END_TEST

START_TEST(sub_too_small) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_sub(num1, num2, &res), 2);
}
END_TEST
//=========================================================================
START_TEST(mul_int_both_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000200, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_int_both_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000200, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000200, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000200, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_not_int_both_positive) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x006AE9BC, 0x00000000, 0x00000000, 0x00050000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_not_int_both_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x006AE9BC, 0x00000000, 0x00000000, 0x00050000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_not_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x80030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x006AE9BC, 0x00000000, 0x00000000, 0x80050000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_not_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x006AE9BC, 0x00000000, 0x00000000, 0x80050000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(mul_too_large) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res), 1);
}
END_TEST

START_TEST(mul_too_small) {
  s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal num2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res), 1);
}
END_TEST

START_TEST(mul_too_large_scale) {
  s21_decimal num1 = {{0x00000000, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal num2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_mul(num1, num2, &res), 1);
}
END_TEST

START_TEST(div_int_both_positive) {
  s21_decimal num1 = {{0x00000100, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000008, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(div_int_both_negative) {
  s21_decimal num1 = {{0x00000100, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000008, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(div_int_first_positive_second_negative) {
  s21_decimal num1 = {{0x00000100, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000008, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(div_int_first_negative_second_positive) {
  s21_decimal num1 = {{0x00000100, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x00000008, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(div_int_both_positive_with_not_int_result) {
  s21_decimal num1 = {{0x00000009, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000002, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x0000002D, 0x00000000, 0x00000000, 0x00010000}};
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(div_int_both_negative_with_not_int_result) {
  s21_decimal num1 = {{0x00000009, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000002, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {{0x0000002D, 0x00000000, 0x00000000, 0x00010000}};
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST
START_TEST(div_by_zero) {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal num2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_div(num1, num2, &res), 3);  // Ожидаем ошибку
}
END_TEST
START_TEST(div_not_int_both_positive) {
  s21_decimal num1 = {
      {0x00000112, 0x00000000, 0x00000000, 0x00020000}};  // 10.000
  s21_decimal num2 = {
      {0x00000004, 0x00000000, 0x00000000, 0x00000000}};  // 1.00
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {
      {0x000002AD, 0x00000000, 0x00000000, 0x00030000}};  // 10.00
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
}
END_TEST

START_TEST(div_not_int_one_positive) {
  s21_decimal num1 = {
      {0x00000112, 0x00000000, 0x00000000, 0x80020000}};  // 10.000
  s21_decimal num2 = {
      {0x00000004, 0x00000000, 0x00000000, 0x00010000}};  // 1.00
  s21_decimal res1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res2 = {
      {0x000002AD, 0x00000000, 0x00000000, 0x80020000}};  // 10.00
  ck_assert_int_eq(s21_div(num1, num2, &res1), 0);
  comparison(res1, res2);
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
  // tcase_add_test(tc, add_not_int_first_negative_second_positive);
  tcase_add_test(tc, add_too_large_both_max);
  tcase_add_test(tc, add_too_large_first_max);
  tcase_add_test(tc, add_too_large_second_max);
  tcase_add_test(tc, add_zero_scale_negative_first_value);

  tcase_add_test(tc, sub_int_both_positive);
  tcase_add_test(tc, sub_int_both_negative);
  tcase_add_test(tc, sub_int_first_positive_second_negative);
  tcase_add_test(tc, sub_int_first_negative_second_positive);
  tcase_add_test(tc, sub_not_int_both_positive);
  tcase_add_test(tc, sub_not_int_both_negative);
  tcase_add_test(tc, sub_not_int_first_positive_second_negative);
  tcase_add_test(tc, sub_not_int_first_negative_second_positive);
  tcase_add_test(tc, sub_int_equals);
  tcase_add_test(tc, sub_too_large);
  tcase_add_test(tc, sub_too_small);

  tcase_add_test(tc, mul_int_both_positive);
  tcase_add_test(tc, mul_int_both_negative);
  tcase_add_test(tc, mul_int_first_positive_second_negative);
  tcase_add_test(tc, mul_int_first_negative_second_positive);
  tcase_add_test(tc, mul_not_int_both_positive);
  tcase_add_test(tc, mul_not_int_both_negative);
  tcase_add_test(tc, mul_not_int_first_positive_second_negative);
  tcase_add_test(tc, mul_not_int_first_negative_second_positive);
  tcase_add_test(tc, mul_too_large);
  tcase_add_test(tc, mul_too_small);

  tcase_add_test(tc, div_int_both_positive);
  tcase_add_test(tc, div_int_both_negative);
  tcase_add_test(tc, div_int_first_positive_second_negative);
  tcase_add_test(tc, div_int_first_negative_second_positive);
  tcase_add_test(tc, div_int_both_positive_with_not_int_result);
  tcase_add_test(tc, div_int_both_negative_with_not_int_result);
  tcase_add_test(tc, div_by_zero);
  tcase_add_test(tc, div_not_int_both_positive);
  tcase_add_test(tc, div_not_int_one_positive);

  suite_add_tcase(s, tc);
  return s;
}