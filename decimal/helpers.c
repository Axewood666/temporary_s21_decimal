#include "s21_decimal.h"

// Вспомогательная функция для извлечения знака
int get_sign(s21_decimal value) { return (value.bits[3] & SIGN_MASK) != 0; }

// Вспомогательная функция для извлечения масштаба
int get_scale(s21_decimal value) { return (value.bits[3] & SCALE_MASK) >> 16; }

// Установить знак результата
void set_sign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= SIGN_MASK;
  } else {
    value->bits[3] &= ~SIGN_MASK;
  }
}

// Установить масштаб результата
void set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= ~SCALE_MASK;    // Очистить текущий масштаб
  value->bits[3] |= (scale << 16);  // Установить новый масштаб
}

// хз че делает двойное отрицание если честно)
int get_bit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

void set_bit(s21_decimal *value, int position, int sum) {
  if (position / 32 < 4 && sum) {
    value->bits[position / 32] |= (1u << (position % 32));
  } else if (position / 32 < 4 && !sum) {
    value->bits[position / 32] &= ~(1u << (position % 32));
  }
}

void multiply_by_10(s21_decimal *value) {
  s21_decimal temp = *value;
  s21_decimal result = {{0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_mul(temp, ten, &result);
  *value = result;
}

void align_scales(int scale_first, int scale_second, s21_decimal *aligned_first,
                  s21_decimal *aligned_second) {
  while (scale_first < scale_second) {
    multiply_by_10(aligned_first);
    scale_first++;
  }

  while (scale_second < scale_first) {
    multiply_by_10(aligned_second);
    scale_second++;
  }
  set_scale(aligned_first, scale_first);
  set_scale(aligned_second, scale_second);
}

void invert(s21_decimal *value) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal add_one = {{1, 0, 0, 0}};
  set_scale(&add_one, get_scale(*value));
  for (int i = 0; i < 3; i++) {
    value->bits[i] = ~value->bits[i];
  }
  s21_add(*value, add_one, &result);
  for (int i = 0; i < 3; i++) {
    value->bits[i] = result.bits[i];
  }
  set_bit(value, 96, 1);
}

int get_lastbit(s21_decimal value) { return get_bit(value, 0); }

void shift_right(s21_decimal *value) {
  // тут храниться последние биты 1 и 2 bits
  int last_bits[2] = {get_bit(*value, 32), get_bit(*value, 64)};
  for (int i = 2; i >= 0; i--) {
    value->bits[i] = value->bits[i] >> 1;
  }
  set_bit(value, 63, last_bits[1]);
  set_bit(value, 31, last_bits[0]);
}
void shift_left(s21_decimal *value) {
  // тут храниться последние биты 1 и 2 bits
  int last_bits[2] = {get_bit(*value, 31), get_bit(*value, 63)};
  for (int i = 2; i >= 0; i--) {
    value->bits[i] = value->bits[i] << 1;
  }
  set_bit(value, 64, last_bits[1]);
  set_bit(value, 32, last_bits[0]);
}

int find_first_one(s21_decimal *value) {
  int return_position = -1;
  for (int position = 95; position >= 0 && return_position < 0; position--) {
    if (get_bit(*value, position)) {
      return_position = position;
    }
  }
  return return_position;
}

int normalization_bit(s21_decimal *value, int second_pos, int first_pos) {
  int difference = first_pos - second_pos;
  for (int i = 0; i < difference; i++) {
    shift_left(value);
  }
  return difference;
}

void thrust(s21_decimal *value, int bit) {
  shift_left(value);
  if (bit) {
    value->bits[0] |= 0x00000001;
  }
}

void zero_or_one_insertion(s21_decimal *value_1, s21_decimal *value_2,
                           s21_decimal *Q) {
  if (s21_is_less(*value_1, *value_2)) {
    thrust(Q, 0);
  } else {
    s21_sub(*value_1, *value_2, value_1);
    thrust(Q, 1);
  }
}

int getFloatExp(float *value) {
  return ((*((int *)value) & ~(1u << 31)) >> 23) - 127;
}