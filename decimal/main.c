#include "s21_decimal.h"

int main() {
  s21_decimal num1 = {{0x00000010, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal num2 = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
  // s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  printf("%d\n", s21_is_greater(num1, num2));
  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", res.bits[0], res.bits[1],
  //        res.bits[2], res.bits[3]);
  // printf("|%8u| |%8X| |%8X| |%8X|\n",b.bits[0], res.bits[1], res.bits[2],
  // res.bits[3]);
}