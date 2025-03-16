#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return 1;
  }
  int status = 0;
  int sign = get_sign(value);
  int scale = get_scale(value);

  if (sign) {
    s21_negate(value, &value);
  }

  if (scale == 0) {
    *result = value;
  } else {
    s21_decimal temp = value;
    null_tech_bits(&temp);
    s21_decimal temp_result = {{0, 0, 0, 0}};
    s21_decimal ten_pow = get_ten_pow(scale);

    div_int(&temp, &ten_pow, &temp_result);
    *result = temp_result;
    set_scale(result, 0);

    if (sign) {
      s21_negate(*result, result);
    }
  }

  return status;
}