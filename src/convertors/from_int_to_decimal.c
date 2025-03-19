#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return 1;
  }

  *dst = create_zero_decimal();

  if (src < 0) {
    set_sign(dst, 1);
    src = -src;
  }

  dst->bits[0] = src;

  return 0;
}