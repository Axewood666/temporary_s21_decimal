#include "s21_decimal.h"

int main() {
  s21_decimal num1 = {{0x000004D2, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal num2 = {{0x0000162E, 0x00000000, 0x00000000, 0x00030000}};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  printf("%d\n", s21_add(num1, num2, &res));
  printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", res.bits[0], res.bits[1],
         res.bits[2], res.bits[3]);
  // printf("|%8u| |%8X| |%8X| |%8X|\n",b.bits[0], res.bits[1], res.bits[2],
  // res.bits[3]);
}