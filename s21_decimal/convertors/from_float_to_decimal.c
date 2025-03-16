#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL || isnan(src) || isinf(src) || fabs(src) > MAX_DECIMAL ||
      (fabs(src) != 0 && fabs(src) < MIN_DECIMAL)) {
    return 1;
  }

  *dst = create_zero_decimal();

  if (src != 0.0f) {
    char str_number[32] = {0};
    sprintf(str_number, "%E", fabs(src));

    char *exp_pos = strchr(str_number, 'E');
    int mantissa_len = exp_pos - str_number;
    char mantissa[32] = {0};
    int mantissa_idx = 0;

    for (int i = 0; i < mantissa_len; i++) {
      if (str_number[i] != '.') {
        mantissa[mantissa_idx++] = str_number[i];
      }
    }

    int trailing_zeros = 0;
    for (int i = strlen(mantissa) - 1; i > 0 && mantissa[i] == '0'; i--) {
      trailing_zeros++;
      mantissa[i] = '\0';
    }

    int exponent = atoi(exp_pos + 1);
    int scale = 6 - exponent - trailing_zeros;

    s21_decimal result = create_zero_decimal();
    s21_decimal ten = create_zero_decimal();
    ten.bits[0] = 10;

    for (int i = 0; mantissa[i] != '\0'; i++) {
      s21_mul(result, ten, &result);

      s21_decimal digit = create_zero_decimal();
      digit.bits[0] = mantissa[i] - '0';
      s21_add(result, digit, &result);
    }

    if (scale < 0) {
      for (int i = 0; i < -scale; i++) {
        s21_mul(result, ten, &result);
      }
      scale = 0;
    } else if (scale > 28) {
      for (int i = 0; i < scale - 28; i++) {
        s21_div(result, ten, &result);
      }
      scale = 28;
    }

    *dst = result;
    set_scale(dst, scale);
    if (src < 0) {
      set_sign(dst, 1);
    }
  }

  return 0;
}