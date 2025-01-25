
#include "s21_decimal.h"



int s21_from_int_to_decimal(int src, s21_decimal *dst){
    int res = 1;
    if(dst){
        for(int i = 0;i<4;i++){
            dst->bits[i] = 0;
        }
        if(src<0){
            set_sign(dst,1);
            src*=-1;
        }
        dst->bits[0] = src;
        res = 0;
    }
    return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst){
    int res = 1;

    if(src.bits[1]==0 && src.bits[2]==0){
        *dist = (int)src.bits[0];
        if(get_sign(*src)){
            *dist*=-1;
        }
        *dst /= (int)pow(10,get_scale(src));
        res = 0;
    }

    return res;

}
