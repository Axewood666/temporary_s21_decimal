#include "main.h"

int main(){
    s21_decimal a = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
    s21_decimal b = {{0x00000010, 0x00000000, 0x00000000, 0x00000000}};
    // s21_decimal res;
    printf("%d\n", s21_is_less(a, b)); 
    // printf("|%8.8X| |%8.8X| |%8.8X| |%8.8X|\n",res.bits[0], res.bits[1], res.bits[2], res.bits[3]);
    // printf("|%8u| |%8X| |%8X| |%8X|\n",b.bits[0], res.bits[1], res.bits[2], res.bits[3]);
    
}