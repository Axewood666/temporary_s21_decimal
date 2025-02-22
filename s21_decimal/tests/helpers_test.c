#include "helpers_test.h"

void comparison(s21_decimal num1, s21_decimal num2) {
  ck_assert_int_eq(num1.bits[0], num2.bits[0]);
  ck_assert_int_eq(num1.bits[1], num2.bits[1]);
  ck_assert_int_eq(num1.bits[2], num2.bits[2]);
  ck_assert_int_eq(num1.bits[3], num2.bits[3]);
}