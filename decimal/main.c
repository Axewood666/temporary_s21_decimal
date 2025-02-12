#include "s21_decimal.h"

int main() {
  s21_decimal d_num = {{0, 0x00000000, 0x00000000, 0x00000000}};
  float f_num = 123.456;
  s21_from_float_to_decimal(f_num, &d_num);
  printf("\n");
  f_num = 123;
  s21_from_float_to_decimal(f_num, &d_num);
  printf("\n");
  f_num = 123.456789;
  s21_from_float_to_decimal(f_num, &d_num);
  printf("\n");
  f_num = 0.001234;
  s21_from_float_to_decimal(f_num, &d_num);
  printf("\n");
  f_num = 0.0012345678;
  s21_from_float_to_decimal(f_num, &d_num);

  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", result.bits[0], result.bits[1],
  //        result.bits[2], result.bits[3]);
}
