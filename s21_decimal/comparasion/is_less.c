#include "../s21_decimal.h"

int s21_is_less_auxiliary_addition(s21_decimal first, s21_decimal second){
    int status = FALSE;
    double_decimal temp_1;
    double_decimal temp_2;
    align_scales(first,second,&temp_1,&temp_2);
    int compare = double_decimal_binary_compare(temp_1,temp_2);
    if(compare == -1){
        status = TRUE;
    }else{
        status = FALSE;
    }
    return status;

}


int s21_is_less(s21_decimal first, s21_decimal second) {
    int result = FALSE;

    int sign_1 = get_sign(first);
    int sign_2 = get_sign(second);

    if(sign_1 == 1 && sign_2 == 0){
        result = TRUE;
    }else if(sign_1 == 0 && sign_2 == 1){
        result = FALSE;
    }else if(sign_1 == 1 && sign_2 == 1){
        result = s21_is_less_auxiliary_addition(s21_decimal_abs(second),s21_decimal_abs(first));
    }else{
        result = s21_is_less_auxiliary_addition(first,second);
    }

    return result;
}


