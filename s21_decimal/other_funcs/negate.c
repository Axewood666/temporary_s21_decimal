#include "../s21_decimal.h"


int s21_negate(s21_decimal value, s21_decimal *result) {
    int status = 0;
    if (result) {
      *result = value;
      result->bits[3] ^= SIGN_MASK;
    } else {
      status = 1;
    }
    return status;
  }