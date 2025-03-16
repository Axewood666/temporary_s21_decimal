#include "helpers.h"

int is_correct_decimal(s21_decimal value) {
  int status = 1;
  int scale = get_scale(value);
  if (scale > 28 || scale < 0) {
    status = 0;
  }
  return status;
}

s21_decimal create_zero_decimal() {
  s21_decimal value;
  clear_decimal(&value);
  return value;
}

void clear_decimal(s21_decimal *value) {
  if (!value) {
    return;
  }
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

void null_tech_bits(s21_decimal *value) {
  if (!value) {
    return;
  }
  value->bits[3] = 0;
}

int get_sign(s21_decimal value) { return (value.bits[3] & SIGN_MASK) != 0; }

int get_scale(s21_decimal value) { return (value.bits[3] & SCALE_MASK) >> 16; }

int check_bits(s21_decimal value) { return (value.bits[3] & CHECK_MASK) == 0; }

void set_scale(s21_decimal *value, int scale) {
  if (!value) {
    return;
  }
  value->bits[3] &= ~SCALE_MASK;
  value->bits[3] |= (scale << 16);
}

void set_sign(s21_decimal *value, int sign) {
  if (!value) {
    return;
  }
  if (sign) {
    value->bits[3] |= SIGN_MASK;
  } else {
    value->bits[3] &= ~SIGN_MASK;
  }
}

s21_decimal s21_decimal_abs(s21_decimal value) {
  s21_decimal res = value;
  set_sign(&res, 0);
  return res;
}

s21_decimal mul_by_ten(s21_decimal value) {
  s21_decimal temp_1 = value;
  s21_decimal temp_2 = value;

  for (int i = 0; i < 3; i++) {
    shift_left(&temp_1);
  }
  shift_left(&temp_2);

  double_decimal temp_3 =
      double_decimal_add(create_double_decimal_from_decimal(temp_1),
                         create_double_decimal_from_decimal(temp_2));
  return temp_3.decimal[0];
}

s21_decimal get_ten_pow(int number) {
  s21_decimal result = {{1, 0, 0, 0}};
  if (number < 40) {
    for (int i = 0; i < number; i++) {
      result = mul_by_ten(result);
    }
  }
  return result;
}

double_decimal create_double_decimal_from_decimal(s21_decimal value) {
  double_decimal result;
  result.decimal[0] = value;
  result.decimal[1] = create_zero_decimal();
  return result;
}

int get_bit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

int get_bit_big(double_decimal value, int bit) {
  return !!(value.decimal[bit / 128].bits[(bit % 128) / 32] &
            (1u << ((bit % 128) % 32)));
}

void set_bit(s21_decimal *value, int position, int sum) {
  if (position / 32 < 4 && sum) {
    value->bits[position / 32] |= (1u << (position % 32));
  } else if (position / 32 < 4 && !sum) {
    value->bits[position / 32] &= ~(1u << (position % 32));
  }
}

void set_bit_big(double_decimal *value, int position, int sum) {
  if (sum) {
    value->decimal[position / 128].bits[(position % 128) / 32] |=
        (1u << (position % 32));
  } else {
    value->decimal[position / 128].bits[(position % 128) / 32] &=
        ~(1u << (position % 32));
  }
}

int find_first_bit(s21_decimal value) {
  int result = -1;
  int flag_stop = 0;

  for (int i = 128 - 1; i >= 0 && !flag_stop; i--) {
    if (get_bit(value, i)) {
      result = i;
      flag_stop = 1;
    }
  }
  return result;
}

void shift_left_big(double_decimal *value, int count) {
  if (!value) {
    return;
  }

  while (count > 0) {
    int temp_bit = get_bit_big(*value, 127);
    shift_left(&value->decimal[0]);
    shift_left(&value->decimal[1]);
    if (temp_bit) {
      set_bit_big(value, 128, temp_bit);
    }
    count--;
  }
}

void shift_right_big(double_decimal *value, int count) {
  if (!value) {
    return;
  }

  while (count > 0) {
    int temp_bit = get_bit_big(*value, 128);
    shift_right(&value->decimal[0]);
    shift_right(&value->decimal[1]);
    if (temp_bit) {
      set_bit_big(value, 127, temp_bit);
    }
    count--;
  }
}

int s21_set_bit(int number, int index) { return number | (1U << index); }

int s21_is_set_bit(int number, int index) { return !!(number & (1U << index)); }

void shift_left(s21_decimal *value) {
  if (!value) {
    return;
  }

  s21_decimal decimal = *value;
  s21_decimal result = create_zero_decimal();

  int b0 = s21_is_set_bit(decimal.bits[0], 32 - 1);
  unsigned int result0 = decimal.bits[0];
  result0 = result0 << 1;
  result.bits[0] = result0;

  int b1 = s21_is_set_bit(decimal.bits[1], 32 - 1);
  unsigned int result1 = decimal.bits[1];
  result1 = result1 << 1;
  result.bits[1] = result1;

  int b2 = s21_is_set_bit(decimal.bits[2], 32 - 1);
  unsigned int result2 = decimal.bits[2];
  result2 = result2 << 1;
  result.bits[2] = result2;

  unsigned int result3 = decimal.bits[3];
  result3 = result3 << 1;
  result.bits[3] = result3;

  if (b0) {
    result.bits[1] = s21_set_bit(result.bits[1], 0);
  }
  if (b1) {
    result.bits[2] = s21_set_bit(result.bits[2], 0);
  }
  if (b2) {
    result.bits[3] = s21_set_bit(result.bits[3], 0);
  }

  *value = result;
}

void shift_right(s21_decimal *value) {
  if (!value) {
    return;
  }

  s21_decimal decimal = *value;
  s21_decimal result = create_zero_decimal();

  int b3 = s21_is_set_bit(decimal.bits[3], 0);
  unsigned int result3 = decimal.bits[3];
  result3 = result3 >> 1;
  result.bits[3] = result3;

  int b2 = s21_is_set_bit(decimal.bits[2], 0);
  unsigned int result2 = decimal.bits[2];
  result2 = result2 >> 1;
  result.bits[2] = result2;

  int b1 = s21_is_set_bit(decimal.bits[1], 0);
  unsigned int result1 = decimal.bits[1];
  result1 = result1 >> 1;
  result.bits[1] = result1;

  unsigned int result0 = decimal.bits[0];
  result0 = result0 >> 1;
  result.bits[0] = result0;

  if (b3) {
    result.bits[2] = s21_set_bit(result.bits[2], 32 - 1);
  }
  if (b2) {
    result.bits[1] = s21_set_bit(result.bits[1], 32 - 1);
  }
  if (b1) {
    result.bits[0] = s21_set_bit(result.bits[0], 32 - 1);
  }

  *value = result;
}

int s21_decimal_binary_equal_zero(s21_decimal decimal) {
  return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 &&
         decimal.bits[3] == 0;
}

s21_decimal s21_decimal_get_max() {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  return result;
}

s21_decimal s21_decimal_get_ten() {
  s21_decimal result;
  clear_decimal(&result);
  result.bits[0] = 10;
  return result;
}

int s21_decimal_binary_compare(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int flag_for_break = 0;

  for (int i = 127; i >= 0 && !flag_for_break; i--) {
    int bit_1 = get_bit(value_1, i);
    int bit_2 = get_bit(value_2, i);

    if (bit_1 == 0 && bit_2 != 0) {
      result = -1;
    }
    if (bit_1 != 0 && bit_2 == 0) {
      result = 1;
    }
    if (result != 0) {
      flag_for_break = 1;
    }
  }
  return result;
}

int double_decimal_binary_compare(double_decimal value_1,
                                  double_decimal value_2) {
  int result_of_compare =
      s21_decimal_binary_compare(value_1.decimal[1], value_2.decimal[1]);
  if (result_of_compare == 0) {
    result_of_compare =
        s21_decimal_binary_compare(value_1.decimal[0], value_2.decimal[0]);
  }
  return result_of_compare;
}

s21_decimal decimal_binary_not(s21_decimal value) {
  s21_decimal result = create_zero_decimal();
  for (int i = 0; i < 4; i++) {
    result.bits[i] = ~value.bits[i];
  }
  return result;
}

s21_decimal s21_decimal_get_one() {
  s21_decimal result;
  clear_decimal(&result);
  result.bits[0] = 1;
  return result;
}

int s21_decimal_even(s21_decimal value) { return (value.bits[0] & 1) != 1; }

int normalization_bit(s21_decimal *value, int second_pos, int first_pos) {
  int difference = first_pos - second_pos;
  for (int i = 0; i < difference; i++) {
    shift_left(value);
  }
  return difference;
}

void thrust(s21_decimal *value, int bit) {
  if (!value) {
    return;
  }
  shift_left(value);
  if (bit) {
    value->bits[0] |= 0x00000001;
  }
}

int zero_or_one_insertion(s21_decimal *value_1, s21_decimal *value_2,
                          s21_decimal *Q) {
  int status = 0;
  if (s21_is_less(*value_1, *value_2)) {
    thrust(Q, 0);
  } else {
    status = s21_sub(*value_1, *value_2, value_1);
    thrust(Q, 1);
  }
  return status;
}

int div_int(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *Q) {
  int status = 0;
  int first_bit_pos_1 = find_first_bit(*value_1);
  int first_bit_pos_2 = find_first_bit(*value_2);
  int difference_in_positions =
      normalization_bit(value_2, first_bit_pos_2, first_bit_pos_1);

  for (int i = 0; i < difference_in_positions + 1; i++) {
    status = zero_or_one_insertion(value_1, value_2, Q);
    if (i != first_bit_pos_1 - first_bit_pos_2) {
      shift_right(value_2);
    }
  }
  return status;
}

int get_first_digit_after_decimal(s21_decimal value) {
  int first_digit = 0;
  int scale = get_scale(value);
  int sign = get_sign(value);

  if (sign) {
    s21_negate(value, &value);
  }
  if (scale > 0) {
    s21_decimal temp = value;
    set_scale(&temp, 0);
    s21_decimal ten = get_ten_pow(scale - 1);
    s21_decimal result = {{0, 0, 0, 0}};
    div_int(&temp, &ten, &result);
    first_digit = result.bits[0] % 10;
  }
  return first_digit;
}

s21_decimal s21_decimal_get_inf() {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  return result;
}

int getFloatExp(float *value) {
  if (!value) {
    return 0;
  }
  return ((*((int *)value) & ~(1u << 31)) >> 23) - 127;
}

int s21_is_empty_mant(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}
