#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int res = 1;
    s21_decimal temp = {{0, 0, 0, 0}};
    s21_truncate(src, &temp);
    if (dst && temp.bits[1] == 0 && temp.bits[2] == 0) {
      long long value = temp.bits[0];
      int sign = get_sign(src);
      if (value <= 2147483647) {
        *dst = (int)value;
        if (sign) {
          *dst = -(*dst);
        }
        res = 0;
      }
    }
    return res;
  }