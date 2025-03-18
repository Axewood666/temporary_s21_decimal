#include <limits.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) {
    return 1;
  }

  int status = 1;
  s21_decimal temp = create_zero_decimal();
  s21_truncate(src, &temp);
  printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", src.bits[0], src.bits[1],
         src.bits[2], src.bits[3]);
  printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", temp.bits[0], temp.bits[1],
         temp.bits[2], temp.bits[3]);
  printf("_________________________________\n");

  if (temp.bits[1] == 0 && temp.bits[2] == 0) {
    long long value = temp.bits[0];
    int sign = get_sign(src);

    if (value <= INT_MAX) {
      *dst = (int)value;
      if (sign) {
        *dst = -(*dst);
      }
      status = 0;
    }
  }

  return status;
}