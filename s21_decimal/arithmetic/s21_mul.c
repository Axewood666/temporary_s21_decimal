#include "../s21_decimal.h"

int auxiliary_mul(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  int status = ARITHMETIC_OK;
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  null_tech_bits(&value_1);
  null_tech_bits(&value_2);
  double_decimal res = decimal_binay_mul(value_1, value_2);

  int shift = get_shift_to_decimal(res);

  int res_scale = scale_1 + scale_2 - shift;

  if (res_scale < 0) {
    status = ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    while (shift > 28) {
      res = double_decimal_binary_division(
          res, create_double_decimal_from_decimal(s21_decimal_get_ten()), NULL);
      shift--;
    }

    if (res_scale > 28) {
      double_decimal temp = res;
      int temp_scale = res_scale;
      while (temp_scale > 28) {
        temp = double_decimal_binary_division(
            temp, create_double_decimal_from_decimal(s21_decimal_get_ten()),
            NULL);
        temp_scale--;
      }
      shift = res_scale - temp_scale + shift;
      res_scale = temp_scale;
    }
    double_decimal remainder =
        create_double_decimal_from_decimal(create_zero_decimal());
    double_decimal powerten =
        create_double_decimal_from_decimal(get_ten_pow(shift));
    res = double_decimal_binary_division(res, powerten, &remainder);
    set_scale(&remainder.decimal[0], shift);

    res.decimal[0] = s21_round_bank(res.decimal[0], remainder.decimal[0]);

    set_scale(&res.decimal[0], res_scale);

    if (!s21_decimal_binary_equal_zero(res.decimal[1])) {
      status = ARITHMETIC_BIG;
    } else {
      *result = res.decimal[0];
    }
  }

  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = ARITHMETIC_OK;
  if (!result || !is_correct_scale(value_1) || !is_correct_scale(value_2)) {
    status = 4;
  } else {
    *result = create_zero_decimal();
    s21_decimal res = create_zero_decimal();
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);

    if (sign_1 == 0 && sign_2 == 0) {
      status = auxiliary_mul(value_1, value_2, &res);
    } else if (sign_1 == 0 && sign_2 == 1) {
      status = auxiliary_mul(value_1, s21_decimal_abs(value_2), &res);
      s21_negate(res, &res);
    } else if (sign_1 == 1 && sign_2 == 0) {
      status = auxiliary_mul(s21_decimal_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign_1 == 1 && sign_2 == 1) {
      status = auxiliary_mul(s21_decimal_abs(value_1), s21_decimal_abs(value_2),
                             &res);
    }
    if (status == ARITHMETIC_BIG && get_sign(res) == 1) {
      status = ARITHMETIC_SMALL;
    }

    *result = res;
  }

  return status;
}
