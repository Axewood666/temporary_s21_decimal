#ifndef S21_COMPARE
#define S21_COMPARE

#include <stdio.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

#define SCALE_MASK 0x00ff0000
#define SIGN_MASK 0x80000000

#define FALSE 0
#define TRUE 1

int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_not_equal(s21_decimal first, s21_decimal second);
int s21_is_greater(s21_decimal first, s21_decimal second);
int s21_is_less(s21_decimal first, s21_decimal second);
int s21_is_less_or_equal(s21_decimal first, s21_decimal second);
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int anothers21_mul(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
// помогающие функции
int get_sign(s21_decimal value);
int get_scale(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
void set_scale(s21_decimal *value, int scale);
void multiply_by_10(s21_decimal *value);
void align_scales(int scale_first, int scale_second, s21_decimal *aligned_first,
                  s21_decimal *aligned_second);
int get_bit(s21_decimal value, int bit);
void set_bit(s21_decimal *value, int position, int sum);
void invert(s21_decimal *value);
int get_lastbit(s21_decimal value);
void shift_left(s21_decimal *value);
void shift_right(s21_decimal *value);
void invert(s21_decimal *value);

#endif
