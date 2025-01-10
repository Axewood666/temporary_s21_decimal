#include "main.h"
// todo
// aling
// set_bit
// max
// mb minus no xz




int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result){
    int status = 0;
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);
    
    if(sign_1 == sign_2){
        //align_scales
        for(int i = 0;i<4;i++) result->bits[i] = 0;
        int carry = 0; // перенос
        for(int i = 0;i<96;i++){
            int bit_1 = get_bit(value_1,i);
            int bit_2 = get_bit(value_2,i);
            int sum = bit_1 + bit_2 + carry;
            set_bit();
            carry = sum / 2;
        }

        if(carry){
            status = 1;
        }

        set_sign(result,sign_1);
        set_scale(result,scale_poka_xz);

    }else{
        //функция вычитания status = s21_minus.....
    }

    return status;

}