#include "main.h"

// Вспомогательная функция для извлечения знака
int get_sign(s21_decimal value) {
    return (value.bits[3] & SIGN_MASK) != 0;
}

// Вспомогательная функция для извлечения масштаба
int get_scale(s21_decimal value) {
    return (value.bits[3] & SCALE_MASK) >> 16;
}

// Установить знак результата
void set_sign(s21_decimal *value, int sign) {
    if (sign) {
        value->bits[3] |= SIGN_MASK;
    } else {
        value->bits[3] &= ~SIGN_MASK;
    }
}

// Установить масштаб результата
void set_scale(s21_decimal *value, int scale) {
    value->bits[3] &= ~SCALE_MASK; // Очистить текущий масштаб
    value->bits[3] |= (scale << 16); // Установить новый масштаб
}

// хз че делает двойное отрицание если честно)
int get_bit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

void set_bit(s21_decimal* value, int position, int sum){
    if(position / 32 < 4 && sum){
        value->bits[position / 32] |= (1u << (position % 32));
    } else if(position / 32 < 4 && !sum){
        value->bits[position / 32] &= ~(1u << (position % 32));
    }
}

void multiply_by_10(s21_decimal *value) {
    s21_decimal temp = *value;
    s21_decimal result = {{0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_mul(temp,ten,&result);
    *value = result;
}

void align_scales(int scale_first, int scale_second,s21_decimal *aligned_first, s21_decimal *aligned_second){
    while (scale_first < scale_second) {
        multiply_by_10(aligned_first);
        scale_first++;
    }

    while (scale_second < scale_first) {
        multiply_by_10(aligned_second);
        scale_second++;
    }
    
}


void invert(s21_decimal *value){
    s21_decimal result = {{0,0,0,0}};
    s21_decimal add_one = {{1,0,0,0}};
    for(int i = 0;i<3;i++){
        value->bits[i] = ~value->bits[i];
        
    }
    s21_add(*value,add_one,&result);
    for(int i = 0;i<3;i++){
        value->bits[i] = result.bits[i];
    }
}