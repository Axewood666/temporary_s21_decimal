#include "../s21_decimal.h"

int check_invalid_conditions(float src, s21_decimal *dst) {
  return (dst == NULL || isnan(src) || isinf(src) || fabs(src) > MAX_DECIMAL ||
          (fabs(src) != 0 && fabs(src) < MIN_DECIMAL));
}

void parse_float_string(char *str_number, char *mantissa, int *exponent) {
  char *exp_pos = strchr(str_number, 'E');
  int mantissa_len = exp_pos - str_number;
  int mantissa_idx = 0;

  for (int i = 0; i < mantissa_len; i++) {
    if (str_number[i] != '.') {
      mantissa[mantissa_idx++] = str_number[i];
    }
  }

  *exponent = atoi(exp_pos + 1);
}

void build_decimal_from_mantissa(const char *mantissa, s21_decimal *result) {
  s21_decimal ten = create_zero_decimal();
  ten.bits[0] = 10;

  for (int i = 0; mantissa[i] != '\0'; i++) {
    s21_mul(*result, ten, result);

    s21_decimal digit = create_zero_decimal();
    digit.bits[0] = mantissa[i] - '0';
    s21_add(*result, digit, result);
  }
}

void adjust_decimal_scale(s21_decimal *result, int *scale) {
  s21_decimal ten = create_zero_decimal();
  ten.bits[0] = 10;

  if (*scale < 0) {
    for (int i = 0; i < -*scale; i++) {
      s21_mul(*result, ten, result);
    }
    *scale = 0;
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (check_invalid_conditions(src, dst)) {
    return 1;
  }

  *dst = create_zero_decimal();

  if (src != 0.0f) {
    char str_number[32] = {0};
    sprintf(str_number, "%E", fabs(src));

    char mantissa[32] = {0};
    int exponent = 0;

    parse_float_string(str_number, mantissa, &exponent);

    int trailing_zeros = 0;
    for (int i = strlen(mantissa) - 1; i > 0 && mantissa[i] == '0'; i--) {
      trailing_zeros++;
      mantissa[i] = '\0';
    }

    int scale = 6 - exponent - trailing_zeros;

    s21_decimal result = create_zero_decimal();
    build_decimal_from_mantissa(mantissa, &result);
    adjust_decimal_scale(&result, &scale);

    *dst = result;
    set_scale(dst, scale);
    if (src < 0) {
      set_sign(dst, 1);
    }
  }

  return 0;
}
