#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return 1;
  }
  int sign = get_sign(src);
  int scale = get_scale(src);

  *dst = 0.0;
  double tmp = 0.0;

  for (int i = 0; i < BITS_COUNT; i++) {
    if (get_bit(src, i)) {
      tmp += pow(2, i);
    }
  }

  *dst = tmp * pow(10, -scale);
  if (sign == 1) {
    *dst = -*dst;
  }
  return 0;
}