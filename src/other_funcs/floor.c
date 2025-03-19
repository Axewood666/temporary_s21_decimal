#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return 1;
  }
  int status = 0;

  s21_decimal int_part = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  int sign = get_sign(value);
  if (sign) {
    s21_truncate(value, &int_part);
    s21_sub(int_part, one, &int_part);
    *result = int_part;
  } else {
    s21_truncate(value, &int_part);
    *result = int_part;
  }

  return status;
}