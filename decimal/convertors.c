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
    sprintf(s_number, "%E", src);
    strtok(s_number, ".");
    strcat(s_number, strtok(NULL, "."));
    char *s_mantissa_with_zeros = strtok(s_number, "E");
    char *s_scale = strtok(NULL, "E");
    int e_scale = atoi(s_scale);
    int zero_count = 0;
    for (int i = strlen(s_mantissa_with_zeros) - 1; i > 0; i--) {
      if (s_mantissa_with_zeros[i] == '0') {
        zero_count++;
      }
    }
    int number_count = strlen(s_mantissa_with_zeros) - zero_count;
    if (e_scale > 0) {
      scale = 6 - zero_count - e_scale;
    } else {
      scale = number_count - 1 - e_scale;
    }
    if (scale <= 28) {
      char s_mantissa[number_count + 1];
      strncpy(s_mantissa, s_mantissa_with_zeros, number_count);
      s_mantissa[number_count] = '\0';
      int mantissa = atoi(s_mantissa);
      if (scale < 0) {
        mantissa *= pow(10, -scale);
        scale = 0;
      }
      set_scale(dst, scale);
      if (src < 0) {
        set_sign(dst, 1);
        mantissa *= -1;
      }
      dst->bits[0] = mantissa;
      status = 0;
    }
  }
  return status;
}

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