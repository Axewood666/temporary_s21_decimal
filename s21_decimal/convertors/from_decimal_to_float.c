#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int status = 1;
    if (dst && src.bits[1] == 0 && src.bits[2] == 0) {
      *dst = (float)src.bits[0] / pow(10, get_scale(src));
      if (get_sign(src)) {
        {
          *dst *= -1;
        }
      }
      status = 0;
    }
    return status;
  }