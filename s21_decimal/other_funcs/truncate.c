#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return 1;
  }
  int sign = get_sign(value);
  int scale = get_scale(value);
  if (sign) s21_negate(value, &value);
  if (scale == 0) {
    *result = value;
  } else {
    s21_decimal temp = value;
    set_scale(&temp, 0);
    s21_decimal quotient = {{0, 0, 0, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    for (int i = 0; i < scale; i++) {
      div_int(&temp, &ten, &quotient);
      temp = quotient;
      quotient.bits[0] = 0;
      quotient.bits[1] = 0;
      quotient.bits[2] = 0;
      quotient.bits[3] = 0;
    }
    *result = temp;
    set_scale(result, 0);
    if (sign) s21_negate(*result, result);
  }
  return 0;
}