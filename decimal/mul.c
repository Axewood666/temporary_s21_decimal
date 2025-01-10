#include "main.h"
#include <stdint.h>



// Умножение длинных чисел
int multiply_96bit(const unsigned int *a, const unsigned int *b, unsigned int  *result) {
    int res = 0;
    uint64_t temp = 0;
    uint64_t carry = 0;
    uint64_t rounding_part = 0;
    int intermediate[6] = {0}; // Для временного хранения 192-битного результата

    // Умножение "в столбик"
    for (int i = 0; i < 3; i++) {
        carry = 0;
        for (int j = 0; j < 3; j++) {
            temp = (uint64_t)a[i] * (uint64_t)b[j] + intermediate[i + j] + carry;
            intermediate[i + j] = temp & 0xFFFFFFFF; // Нижние 32 бита
            carry = temp >> 32; // Верхние 32 бита
        }
        intermediate[i + 3] = carry;
    }

    // Проверка переполнения (если есть значимые данные за пределами 96 бит)
    if (intermediate[3] != 0 || intermediate[4] != 0 || intermediate[5] != 0) {
        // Округляем результат
        rounding_part = (uint64_t)intermediate[2] >> 31; // Берем бит для округления
        intermediate[2] &= 0x7FFFFFFF;                  // Обрезаем лишний бит
        if(rounding_part && ++intermediate[2]==0  && ++intermediate[1]==0 && ++intermediate[0]==0){
            res = -1;
        }
    }

    // Записать результат в output
    for (int i = 0; i < 3; i++) {
        result[i] = intermediate[i];
    }

    return res; // Успех
}

// Основная функция умножения
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {
    // 1. Извлечь знаки и масштаб
    int sign_a = get_sign(a); 
    int sign_b = get_sign(b); 
    int scale_a = get_scale(a); 
    int scale_b = get_scale(b); 

    // Знак результата
    int result_sign = sign_a ^ sign_b;

    // Новый масштаб
    int result_scale = scale_a + scale_b;
    if (result_scale > 28) {
        return -1; // Ошибка: масштаб выходит за пределы
    }

    // 2. Умножить мантиссы
    unsigned int res_bits[3] = {0};
    if (multiply_96bit(a.bits, b.bits, res_bits) != 0) {
        return -1; // Ошибка переполнения
    }


    // 3. Установить масштаб и знак результата
    result->bits[3] = 0;
    result->bits[0] = res_bits[0];
    result->bits[1] = res_bits[1];
    result->bits[2] = res_bits[2];
    set_sign(result, result_sign);
    set_scale(result, result_scale);

    return 0; // Успех
}



