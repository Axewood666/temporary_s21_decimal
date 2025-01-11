#include "main.h"

int s21_is_equal(s21_decimal first, s21_decimal second){
    int result = TRUE;
    int scale_first = (first.bits[3] & SCALE_MASK);
    int scale_second = (second.bits[3] & SCALE_MASK);
    if (scale_first!= scale_second){
        result = FALSE;
    }else{
        int sign_first = (first.bits[3] & SIGN_MASK);
        int sign_second = (second.bits[3] & SIGN_MASK);
        result = (sign_first == sign_second) ? TRUE : FALSE; 
        for(int i = 0;i<3 && result;i++){
            result = (first.bits[i] != second.bits[i]) ? FALSE : TRUE;
        }
    }
    return result;
}

int s21_is_not_equal(s21_decimal first, s21_decimal second){
    return !s21_is_equal(first,second);
}


void multiply_by_10(s21_decimal *value) {
    s21_decimal temp = *value;
    s21_decimal result = {{0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_mul(temp,ten,&result);
    *value = result;
}


int s21_is_greater(s21_decimal first, s21_decimal second){
    int result = FALSE;
    int sign_first = first.bits[3] & SIGN_MASK;
    int sign_b = second.bits[3] & SIGN_MASK;
    if (sign_first != sign_b) {
        result = sign_b != 0; 
    }

    
   int scale_first = (first.bits[3] & SCALE_MASK) >> 16;
   int scale_second = (second.bits[3] & SCALE_MASK) >> 16;

    s21_decimal aligned_first = first;
    s21_decimal aligned_second = second;
    // восстановить как будет умножение!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while (scale_first < scale_second) {
        multiply_by_10(&aligned_first);
        scale_first++;
    }

    while (scale_second < scale_first) {
        multiply_by_10(&aligned_second);
        scale_second++;
    }
    int flag_break = 0;
    for (int i = 2; i >= 0 && !flag_break; i--) { 
        if (aligned_first.bits[i] > aligned_second.bits[i]) {
            result = sign_first == 0;
            flag_break++;
        } else if (aligned_first.bits[i] < aligned_second.bits[i]) {
            result = sign_first != 0;
            flag_break++; 
        }
    }

    return result;
}

int s21_is_less(s21_decimal first, s21_decimal second){
    int result = FALSE;
    int sign_first = first.bits[3] & SIGN_MASK;
    int sign_b = second.bits[3] & SIGN_MASK;
    if (sign_first != sign_b) {
        result = sign_b != 0; 
    }

    
   int scale_first = (first.bits[3] & SCALE_MASK) >> 16;
   int scale_second = (second.bits[3] & SCALE_MASK) >> 16;

    s21_decimal aligned_first = first;
    s21_decimal aligned_second = second;
    // восстановить как будет умножение!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while (scale_first < scale_second) {
        multiply_by_10(&aligned_first);
        scale_first++;
    }

    while (scale_second < scale_first) {
        multiply_by_10(&aligned_second);
        scale_second++;
    }
    int flag_break = 0;
    for (int i = 2; i >= 0 && !flag_break; i--) { 
        if (aligned_first.bits[i] < aligned_second.bits[i]) {
            result = sign_first == 0;
            flag_break++;
        } else if (aligned_first.bits[i] > aligned_second.bits[i]) {
            result = sign_first != 0;
            flag_break++; 
        }
    }

    return result;
}

int s21_is_less_or_equal(s21_decimal first, s21_decimal second){
    return !s21_is_greater(first,second);
}

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second){
    return !s21_is_less(first, second);

}