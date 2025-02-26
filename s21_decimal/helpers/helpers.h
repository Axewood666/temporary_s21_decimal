#ifndef HELPERS_H
#define HELPERS_H

#include "../s21_decimal.h"

#define SIGN_MASK 0x80000000
#define SCALE_MASK 0x00ff0000
#define CHECK_MASK 0x7F00FFFF
typedef struct s21_decimal s21_decimal;
typedef struct double_decimal double_decimal;

int check_bits(s21_decimal value);
int is_correct_decimal(s21_decimal value);
s21_decimal create_zero_decimal();
void clear_decimal(s21_decimal *value);
void null_tech_bits(s21_decimal *value);
int get_sign(s21_decimal value);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
void set_sign(s21_decimal *value, int sign);
s21_decimal s21_decimal_abs(s21_decimal value);
void align_scales(s21_decimal value_1, s21_decimal value_2,double_decimal *value_1d,double_decimal *value_2d);
s21_decimal get_ten_pow(int number);
double_decimal binary_mul_big(double_decimal value_1,s21_decimal value_2);
double_decimal create_double_decimal_from_decimal(s21_decimal value);
int get_bit(s21_decimal value, int bit);
int get_bit_big(double_decimal value, int bit);
void set_bit(s21_decimal *value, int position, int sum);
void set_bit_big(double_decimal *value, int position, int sum);
int find_first_bit(s21_decimal value);
double_decimal double_decimal_add(double_decimal value_1,double_decimal value_2);
s21_decimal s21_decimal_add(s21_decimal value_1,s21_decimal value_2);
void shift_left_big(double_decimal *value,int count);
void shift_right_big(double_decimal *value,int count);
void shift_left(s21_decimal *value);
void shift_right(s21_decimal *value);
int s21_decimal_binary_equal_zero(s21_decimal decimal);
s21_decimal s21_decimal_get_max();
s21_decimal s21_decimal_get_ten();
int get_shift_to_decimal(double_decimal value);
double_decimal double_decimal_binary_division(double_decimal value_1,double_decimal value_2,double_decimal *remainder);
int s21_decimal_binary_compare(s21_decimal value_1,s21_decimal value_2);
int double_decimal_binary_compare(double_decimal value_1,double_decimal value_2);
double_decimal big_binary_sub(double_decimal value_1,double_decimal value_2);
s21_decimal decimal_binary_not(s21_decimal value);
s21_decimal s21_decimal_get_one();
s21_decimal s21_round_bank(s21_decimal integer, s21_decimal fractional);
int s21_decimal_even(s21_decimal value);
int get_first_digit_after_decimal(s21_decimal value);
s21_decimal s21_decimal_get_inf();
double_decimal decimal_binay_mul(s21_decimal value_1,s21_decimal value_2);
int normalization_bit(s21_decimal *value, int second_pos, int first_pos);
void thrust(s21_decimal *value, int bit);
int zero_or_one_insertion(s21_decimal *value_1, s21_decimal *value_2,
    s21_decimal *Q);
int div_int(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *Q);
int getFloatExp(float *value);
int s21_is_empty_mant(s21_decimal value);
#endif