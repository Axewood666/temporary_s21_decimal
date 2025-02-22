#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    int status = 0;
    if (result) {
      s21_decimal int_part = {{0, 0, 0, 0}};
      s21_decimal one = {{1, 0, 0, 0}};
      s21_decimal zero = {{0, 0, 0, 0}};
      s21_truncate(value, &int_part);
      if (get_first_digit_after_decimal(value) >= 5) {
        s21_decimal rounded = {{0, 0, 0, 0}};
        status = s21_add(int_part, one, &rounded);
        *result = (status == 0) ? rounded : zero;
      } else {
        *result = int_part;
      }
    } else {
      status = 1;
    }
    return status;
  }