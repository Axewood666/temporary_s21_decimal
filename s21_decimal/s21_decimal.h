#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/helpers.h"

#define ARITHMETIC_OK 0
#define ARITHMETIC_BIG 1
#define ARITHMETIC_SMALL 2
#define ARITHMETIC_ZERO_DIV 3
#define TRUE 1
#define FALSE 0
#define BITS_COUNT 96

#define MAX_DECIMAL 79228157791897854723898736640.0f
#define MIN_DECIMAL \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef struct double_decimal {
  s21_decimal decimal[2];
} double_decimal;

int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_not_equal(s21_decimal first, s21_decimal second);
int s21_is_greater(s21_decimal first, s21_decimal second);
int s21_is_less(s21_decimal first, s21_decimal second);
int s21_is_less_or_equal(s21_decimal first, s21_decimal second);
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

#endif