#include "s21_decimal.h"

int main() {
  // s21_decimal num1 = {{0x00000100, 0x00000000, 0x00000000, 0x00000000}};
  // s21_decimal num2 = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  // s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  // printf("%d\n", s21_div(num1, num2, &res));
  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", res.bits[0], res.bits[1],
  //        res.bits[2], res.bits[3]);
  float number = 128.456;
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_from_float_to_decimal(number, &res);
  printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", res.bits[0], res.bits[1],
         res.bits[2], res.bits[3]);
}