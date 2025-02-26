#include <stdio.h>
#include "s21_decimal.h"

int main() {
    s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950334
    s21_decimal num2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 11.884224377139650639031592551
    s21_decimal result;

    if (s21_div(num1, num2, &result) == 0) {
        printf("Сложение прошло успешно\n");
    } else {
        printf("Ошибка сложения\n");
    }
    printf("|%.8X| |%.8X| |%.8X| |%.8X|\n",result.bits[0],result.bits[1],result.bits[2],result.bits[3]);
    // double_decimal amir  = create_double_decimal_from_decimal(s21_decimal_abs(create_zero_decimal()));
    // s21_decimal num1 = {{0x00000008,0x00000000,0x00000000,0x00000000}};
    // s21_decimal num2 = {{0x00000008,0x00000000,0x00000000,0x00000000}};
    // double_decimal result = big_binary_sub(create_double_decimal_from_decimal(num1),create_double_decimal_from_decimal(num2));
    // printf("divindend -> |%.8x||%.8x||%.8x||%.8x||%.8x||%.8x||%.8x||%.8x|\n",result.decimal[0].bits[0],
    //     result.decimal[0].bits[1],
    //     result.decimal[0].bits[2],
    //     result.decimal[0].bits[3],
    //     result.decimal[1].bits[0],
    //     result.decimal[1].bits[1],
    //     result.decimal[1].bits[2],
    //     result.decimal[1].bits[3]
    // );

    
    
    return 0;
}



