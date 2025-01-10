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
int getBit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}

void set_bit(s21_decimal* value, int position, int sum){
    if(position / 32 < 4 && sum){
        value->bits[position / 4] |= (1u << (position % 32));
    } else if(position / 32 < 4 && sum){
        value->bits[position / 4] &= ~(1u << (position % 32));
    }
}