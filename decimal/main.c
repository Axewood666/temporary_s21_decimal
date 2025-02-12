#include "s21_decimal.h"

int main() {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00000000}};
  float result_float = 0;
  // float extended_float = 123456;
  printf("%d\n", s21_from_decimal_to_float(number_decimal, &result_float));
  printf("%f", result_float);
  // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n", number_decimal.bits[0],
  //        number_decimal.bits[1], number_decimal.bits[2],
  //        number_decimal.bits[3]);
}
