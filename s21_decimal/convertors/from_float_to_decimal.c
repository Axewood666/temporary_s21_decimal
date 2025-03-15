#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL || isnan(src) || isinf(src) || fabs(src) > MAX_DECIMAL ||
      (fabs(src) != 0 && fabs(src) < MIN_DECIMAL)) {
    return 1;
  }
  *dst = create_zero_decimal();

  if (src != 0.0f) {
    char s_number[32];
    sprintf(s_number, "%E", fabs(src));

    char *e_pos = strchr(s_number, 'E');

    int mantissa_len = e_pos - s_number;
    char mantissa_str[32] = {0};
    int j = 0;

    for (int i = 0; i < mantissa_len; i++) {
      if (s_number[i] != '.') {
        mantissa_str[j++] = s_number[i];
      }
    }

    int zero_count = 0;
    for (int i = strlen(mantissa_str) - 1; i > 0 && mantissa_str[i] == '0';
         i--) {
      zero_count++;
      mantissa_str[i] = '\0';
    }

    int e_scale = atoi(e_pos + 1);
    int scale = 6 - e_scale - zero_count;

    s21_decimal tmp = create_zero_decimal();
    s21_decimal ten = create_zero_decimal();
    ten.bits[0] = 10;

    for (int i = 0; mantissa_str[i] != '\0'; i++) {
      s21_mul(tmp, ten, &tmp);

      s21_decimal digit = create_zero_decimal();
      digit.bits[0] = mantissa_str[i] - '0';
      s21_add(tmp, digit, &tmp);
    }

    if (scale < 0) {
      for (int i = 0; i < -scale; i++) {
        s21_mul(tmp, ten, &tmp);
      }
      scale = 0;
    } else if (scale > 28) {
      s21_decimal ten = create_zero_decimal();
      ten.bits[0] = 10;

      for (int i = 0; i < scale - 28; i++) {
        s21_div(tmp, ten, &tmp);
      }
      scale = 28;
    }

    *dst = tmp;
    set_scale(dst, scale);
    if (src < 0) {
      set_sign(dst, 1);
    }
  }

  return 0;
}