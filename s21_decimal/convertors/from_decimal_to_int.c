#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int res = 1;
    
    if(dst){
        s21_decimal src_int_part = create_zero_decimal();
        s21_truncate(src,&src_int_part);
        if(src_int_part.bits[0] == 0 && src_int_part.bits[1] == 0){
            *dst = src_int_part.bits[0];
            if (get_sign(src)) {
                *dst *= -1;
            }
            res = 0;
        }
    }
    return res;
  }