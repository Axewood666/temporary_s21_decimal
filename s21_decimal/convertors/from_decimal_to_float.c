#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst)
{
  if (!dst)
  {
    return 1;
  }

  const int sign = get_sign(src);
  const int scale = get_scale(src);
  double tmp = 0.0;
  *dst = 0.0;

  for (int i = 0; i < BITS_COUNT; i++)
  {
    if (get_bit(src, i))
    {
      tmp += pow(2, i);
    }
  }

  tmp *= pow(10, -scale);
  *dst = sign ? -tmp : tmp;

  return 0;
}