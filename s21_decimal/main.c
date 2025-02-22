#include <stdio.h>
#include "s21_decimal.h"

int main() {
    s21_decimal num1 = {{0x00000009, 0x00000000, 0x00000000, 0x00000000}};
    s21_decimal num2 = {{0x00000002, 0x00000000, 0x00000000, 0x00000000}};
    s21_decimal result;

    if (s21_div(num1, num2, &result) == 0) {
        printf("Сложение прошло успешно\n");
    } else {
        printf("Ошибка сложения\n");
    }
    printf("|%.8X| |%.8X| |%.8X| |%.8X|\n",result.bits[0],result.bits[1],result.bits[2],result.bits[3]);
    // double_decimal amir  = create_double_decimal_from_decimal(s21_decimal_abs(create_zero_decimal()));

    // printf("|%.8x||%.8x||%.8x||%.8x||%.8x||%.8x||%.8x||%.8x|",amir.decimal[1].bits[0],
    //     amir.decimal[1].bits[1],
    //     amir.decimal[1].bits[2],
    //     amir.decimal[1].bits[3],
    //     amir.decimal[0].bits[0],
    //     amir.decimal[0].bits[1],
    //     amir.decimal[0].bits[2],
    //     amir.decimal[0].bits[3]
    // );

    return 0;
}



