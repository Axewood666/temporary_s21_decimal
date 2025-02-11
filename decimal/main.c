#include "s21_decimal.h"

int main() {
  s21_decimal num1 = {{0, 0x00000000, 0x00000000, 0x80050000}};
  s21_decimal result = {{0, 0, 0, 0}};

  // Округление 123.45677 до 123
  s21_floor(num1, &result);
  printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", result.bits[0], result.bits[1],
         result.bits[2], result.bits[3]);
  // // Округление 123.567 до 124
  // s21_from_float_to_decimal(123.567, &num1);
  // s21_round(num1, &result);
  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", result.bits[0], result.bits[1],
  //        result.bits[2], result.bits[3]);
  // printf("%d\n", div_int(&num1, &num2, &res));
  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", res.bits[0], res.bits[1],
  //        res.bits[2], res.bits[3]);
  // float number = 123.456;
  // s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  // s21_from_float_to_decimal(number, &res);

  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", res.bits[0], res.bits[1],
  //        res.bits[2], res.bits[3]);

  // s21_decimal num1 = {{0x075BCD15, 0, 0, 0x80030000}};  // 1234567.89
  // int first_digit = get_first_digit_after_decimal(num1);
  // printf("First digit after decimal: %d\n",
  //        first_digit);  // Ожидаемый результат: 5
}
