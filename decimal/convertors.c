#include "s21_decimal.h"

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

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 1;

  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = (int)src.bits[0];
    if (get_sign(src)) {
      *dst *= -1;
    }
    *dst /= (int)pow(10, get_scale(src));
    res = 0;
  }

  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 1;
  if (dst && (getFloatExp(&src) < 96)) {
    for (int i = 0; i < 4; i++) dst->bits[i] = 0;
    int sign = 0;
    if (src < 0) {
      src *= -1;
      sign = 1;
    }
    int scale = 0;
    float temp = src;
    while (scale < 28 && (truncf(temp) / temp) != 1) {
      scale++;
      temp *= 10;
    }
    if (scale < 28) {
      set_sign(dst, sign);
      set_scale(dst, scale);
      int int_part = (int)temp;
      for (int i = 0; i < 96; i++) {
        set_bit(dst, i, int_part % 2);
        int_part /= 2;
      }
      status = 0;
    }
  }
  return status;
}