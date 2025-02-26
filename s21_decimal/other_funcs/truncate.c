#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int status = 0;
    int sign = get_sign(value);
    if (result) {
      int scale = get_scale(value);
      if (sign) {
        s21_negate(value, &value);
      }
      if (scale == 0) {
        *result = value;
      } else {
        s21_decimal temp = value;
        null_tech_bits(&temp);
        s21_decimal temp2 = {{0, 0, 0, 0}};
        s21_decimal ten = get_ten_pow(scale); 
        div_int(&temp, &ten, &temp2);
        *result = temp2;
        set_scale(result, 0);
        if (sign) {
          s21_negate(*result, result);
        }
      }
    } else {
      status = 1;
    }
    return status;
  }