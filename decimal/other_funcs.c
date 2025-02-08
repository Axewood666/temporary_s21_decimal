#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    int scale = get_scale(value);
    if (scale == 0) {
      *result = value;
    } else {
      s21_decimal temp = value;
      s21_decimal temp2 = {{0, 0, 0, 0}};
      set_scale(&temp, 0);
      s21_decimal ten = {{10, 0, 0, 0}};
      for (int i = 0; i < scale; i++) {
        div_int(&temp, &ten, &temp2);
        temp = temp2;
        temp2.bits[0] = 0;
        temp2.bits[1] = 0;
        temp2.bits[2] = 0;
        temp2.bits[3] = 0;
      }
      *result = temp;
      set_scale(result, 0);
    }
  } else {
    status = 1;
  }
  return status;
}
