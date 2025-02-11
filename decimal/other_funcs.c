#include "s21_decimal.h"

// Округление до ближайшего целого числа в сторону отриц бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    s21_decimal int_part = {{0, 0, 0, 0}};
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal zero = {{0, 0, 0, 0}};
    int sign = get_sign(value);
    if (sign) {
      s21_truncate(value, &int_part);
      s21_sub(int_part, one, &int_part);
      *result = int_part;
    } else {
      s21_truncate(value, &int_part);
      *result = int_part;
    }
  } else
    status = 1;
  return status;
}

// Округление до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    s21_decimal int_part = {{0, 0, 0, 0}};
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal zero = {{0, 0, 0, 0}};
    s21_truncate(value, &int_part);
    if (get_first_digit_after_decimal(value) >= 5) {
      s21_decimal rounded = {{0, 0, 0, 0}};
      status = s21_add(int_part, one, &rounded);
      *result = (status == 0) ? rounded : zero;
    } else {
      *result = int_part;
    }
  } else {
    status = 1;
  }
  return status;
}

// Возвращает целую часть числа
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  int sign = get_sign(value);
  if (result) {
    int scale = get_scale(value);
    if (sign) {
      s21_negate(value, &value);
    }
    if (scale == 0) {
      *result = value;
    } else {
      s21_decimal temp = value;
      set_scale(&temp, 0);
      s21_decimal temp2 = {{0, 0, 0, 0}};
      s21_decimal ten = {{10, 0, 0, 0}};
      for (int i = 0; i < scale; i++) {
        div_int(&temp, &ten, &temp2);
        temp = temp2;
        temp2.bits[0] = 0;
        temp2.bits[1] = 0;
        temp2.bits[2] = 0;
        temp2.bits[3] = 0;
      }
      *result = temp;
      set_scale(result, 0);
      if (sign) {
        s21_negate(*result, result);
      }
    }
  } else {
    status = 1;
  }
  return status;
}

// Возвращает результат умножения числа на -1
int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    *result = value;
    result->bits[3] ^= SIGN_MASK;
  } else {
    status = 1;
  }
  return status;
}