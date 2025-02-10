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
    char s_number[32];
    int scale = 0;
    printf("%f\n", src);
    sprintf(s_number, "%E", src);
    printf("%s\n", s_number);
    strtok(s_number, ".");
    strcat(s_number, strtok(NULL, "."));
    printf("%s\n", s_number);
    char *mantissa = strtok(s_number, "E");
    printf("%s\n", mantissa);
    char *s_scale = strtok(NULL, "E");
    printf("%s\n", s_scale);
    scale = atoi(s_scale);
    printf("%d\n", scale);
    if (scale > 0) {
      scale = 7 - scale;
      if (scale >= 0) {
        set_scale(dst, scale);
      }
    } else if (strrchr(mantissa, '0')) {
      set_scale(dst, abs(scale));
    } else {
      set_scale(dst, 7);
    }
    printf("%d\n", get_scale(*dst));
  }
  return status;
}