#include "s21_decimal.h"


int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    for(int i = 0;i<4;i++)result->bits[i] = 0;
    s21_decimal Q = {{0}};
    int first_bit_pos_1 = find_first_one(&value_1);
    int first_bit_pos_2 = find_first_one(&value_2);
    normalization_bit(&value_2,first_bit_pos_2,first_bit_pos_1);

    for(int i = 0;i<first_bit_pos_1-first_bit_pos_2+1;i++){
        if(s21_is_less(value_1,value_2)){
            thrust(&Q,0);
        }else{
            s21_sub(value_1,value_2,&value_1);
            thrust(&Q,1);
        }
        shift_right(&value_2);
    }
    *result = Q;
    return 1;
}