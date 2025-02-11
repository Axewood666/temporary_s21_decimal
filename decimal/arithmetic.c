#include "s21_decimal.h"

int add_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int carry = 0;  // перенос
  int flag = 0;
  for (int i = 0; i < 96; i++) {
    int bit_1 = get_bit(value_1, i);
    int bit_2 = get_bit(value_2, i);
    int sum = bit_1 + bit_2 + carry;
    set_bit(result, i, sum % 2);
    carry = sum / 2;
    if (i == 95 && carry == 1 &&
        !(get_bit(value_1, 96) || get_bit(value_2, 96)))
      flag = 1;
  }
  return flag;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  s21_decimal inital_value_1 = value_1;
  s21_decimal inital_value_2 = value_2;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;

  if (sign_1 == sign_2) {
    align_scales(get_scale(value_1), get_scale(value_2), &value_1, &value_2);
    if (add_bits(value_1, value_2, result) == 1) {
      if ((!get_scale(inital_value_1) || !get_scale(inital_value_2)) &&
          !sign_1) {
        status = 1;
      } else if ((!get_scale(value_1) || !get_scale(value_2)) && sign_1) {
        status = 2;
      } else if ((get_scale(value_1) > 0) & (get_scale(value_2) > 0)) {
        // реализовать банковское округление
      }
    } else {
      set_sign(result, sign_1);
      set_scale(result, get_scale(value_1));
    }
  } else if (sign_1 == 0) {
    set_sign(&value_2, 0);
    status = s21_sub(value_1, value_2, result);
  } else if (sign_1 == 1) {
    set_sign(&value_1, 0);
    status = s21_sub(value_1, value_2, result);
  }
  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  if (sign_1 == sign_2) {
    align_scales(get_scale(value_1), get_scale(value_2), &value_1, &value_2);
    if (s21_is_not_equal(value_1, value_2)) {
      set_sign(&value_1, 0);
      set_sign(&value_2, 0);
      if (s21_is_less(value_1, value_2)) {
        invert(&value_1);
        status = s21_add(value_1, value_2, result);
        set_sign(result, !sign_2);
      } else {
        invert(&value_2);
        status = s21_add(value_1, value_2, result);
        set_sign(result, sign_1);
      }
    }
  } else {
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    status = s21_add(value_1, value_2, result);
    status = status ? (sign_1 ? 2 : 1) : status;
    set_sign(result, sign_1);
  }
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  int result_sign = sign_1 ^ sign_2;
  int result_scale = scale_1 + scale_2;
  // if (result_scale > 28) {
  //   return -1;
  // }
  s21_decimal summator = {{0}};
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  while (value_2.bits[0] != 0) {
    int last_bit_2 = get_lastbit(value_2);
    if (last_bit_2) {
      status = s21_add(value_1, summator, &summator);
    }
    shift_left(&value_1);
    shift_right(&value_2);
  }
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  set_sign(&summator, result_sign);
  set_scale(&summator, result_scale);
  *result = summator;
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  s21_decimal zero = {{0}};
  if (s21_is_equal(value_2, zero)) {
    return 3;
  }

  int sign = get_sign(value_1) ^ get_sign(value_2);
  int fractional_bits = get_scale(value_2) - get_scale(value_1);
  fractional_bits =
      (fractional_bits < 0) ? fractional_bits * (-1) : fractional_bits;
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  s21_decimal Q = {{0}};

  // int first_bit_pos_1 = find_first_one(&value_1);
  // int first_bit_pos_2 = find_first_one(&value_2);
  // int difference_in_positions =
  //     normalization_bit(&value_2, first_bit_pos_2, first_bit_pos_1);
  // for (int i = 0; i < difference_in_positions + 1; i++) {
  //   status = zero_or_one_insertion(&value_1, &value_2, &Q);
  //   if (i != first_bit_pos_1 - first_bit_pos_2) {
  //     shift_right(&value_2);
  //   }
  // }

  status = div_int(&value_1, &value_2, &Q);

  while (s21_is_not_equal(value_1, zero)) {
    multiply_by_10(&value_1);
    multiply_by_10(&Q);
    s21_decimal temp = {{0}};
    int first_bit_pos_1 = find_first_one(&value_1);
    int first_bit_pos_2 = find_first_one(&value_2);
    int difference_in_positions =
        normalization_bit(&value_2, first_bit_pos_2, first_bit_pos_1);
    for (int i = 0;
         i < difference_in_positions + 1 && s21_is_not_equal(value_1, zero);
         i++) {
      zero_or_one_insertion(&value_1, &value_2, &temp);
      shift_right(&value_2);
    }
    status = s21_add(Q, temp, &Q);
    fractional_bits++;
  }

  *result = Q;
  set_scale(result, fractional_bits);
  set_sign(result, sign);
  return status;
}