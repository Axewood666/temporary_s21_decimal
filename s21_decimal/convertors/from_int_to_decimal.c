#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int res = 1;
    if (dst) {
      for (int i = 0; i < 4; i++) {
        dst->bits[i] = 0;
      }
      if (src < 0) {
        set_sign(dst, 1);
        src *= -1;
      }
      dst->bits[0] = src;
      res = 0;
    }
    return res;
  }
  