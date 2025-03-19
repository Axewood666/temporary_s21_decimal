#include "../s21_decimal.h"

int div_calc_fractional(double_decimal *res, double_decimal value_2d,
                        double_decimal *remainder) {
  int scale = 0;
  double_decimal number = *res;
  double_decimal temp;
  double_decimal temp_remainder = *remainder;
  int flag_stop = 0;

  while ((!s21_decimal_binary_equal_zero(temp_remainder.decimal[0]) ||
          !s21_decimal_binary_equal_zero(temp_remainder.decimal[1])) &&
         scale < 28 && !flag_stop) {
    double_decimal number_stored = number;
    double_decimal remainder_stored = temp_remainder;

    number = binary_mul_big(number, s21_decimal_get_ten());
    temp_remainder = binary_mul_big(temp_remainder, s21_decimal_get_ten());
    temp = double_decimal_binary_division(temp_remainder, value_2d,
                                          &temp_remainder);
    number = double_decimal_add(number, temp);

    if (!check_bits(number.decimal[0])) {
      number = number_stored;
      temp_remainder = remainder_stored;
      flag_stop = 1;
    } else {
      scale++;
    }
  }

  *res = number;
  *remainder = temp_remainder;

  return scale;
}

int auxiliary_div(double_decimal value_2d, double_decimal res,
                  double_decimal remainder, s21_decimal *result) {
  int status = ARITHMETIC_OK;

  int scale_1 = div_calc_fractional(&res, value_2d, &remainder);
  double_decimal temp_res =
      create_double_decimal_from_decimal(create_zero_decimal());
  int scale_2 = div_calc_fractional(&temp_res, value_2d, &remainder);

  set_scale(&temp_res.decimal[0], scale_2);
  res.decimal[0] = s21_round_bank(res.decimal[0], temp_res.decimal[0]);
  set_scale(&res.decimal[0], scale_1);

  if (!s21_decimal_binary_equal_zero(res.decimal[1])) {
    status = ARITHMETIC_BIG;
  } else {
    *result = res.decimal[0];
  }

  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result || !is_correct_scale(value_1) || !is_correct_scale(value_2)) {
    return 4;
  } else if (s21_is_equal(value_2, create_zero_decimal())) {
    return ARITHMETIC_ZERO_DIV;
  }

  int status = ARITHMETIC_OK;
  *result = create_zero_decimal();
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  double_decimal value_1d, value_2d;
  align_scales(value_1, value_2, &value_1d, &value_2d);

  double_decimal remainder =
      create_double_decimal_from_decimal(create_zero_decimal());
  double_decimal res =
      double_decimal_binary_division(value_1d, value_2d, &remainder);

  if (res.decimal[0].bits[3] != 0 ||
      !s21_decimal_binary_equal_zero(res.decimal[1])) {
    status = (sign_1 != sign_2) ? ARITHMETIC_SMALL : ARITHMETIC_BIG;
  } else {
    status = auxiliary_div(value_2d, res, remainder, result);
    if (sign_1 != sign_2) {
      set_sign(result, 1);
    }
    if (get_sign(*result) == 1 && status == ARITHMETIC_BIG) {
      status = ARITHMETIC_SMALL;
    }
  }

  return status;
}
