#include "s21_decimal.h"

int anothers21_mul(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int status = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  int result_sign = sign_1 ^ sign_2;
  int result_scale = scale_1 + scale_2;
  if (result_scale > 28) {
    return -1;
  }
  s21_decimal summator = {{0}};
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  while (value_2.bits[0] != 0 || value_2.bits[0] != 0 || value_2.bits[0] != 0) {
    int last_bit_2 = get_lastbit(value_2);
    if (last_bit_2) {
      status = s21_add(value_1, summator, &summator);
    }
    shift_left(&value_1);
    shift_right(&value_2);
  }
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  set_sign(&summator, result_sign);
  set_scale(&summator, result_scale);
  *result = summator;
  return status;
}