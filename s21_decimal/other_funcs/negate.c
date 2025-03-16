#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    if (!result) {
        return 1;
    }
    int status = 0;

    *result = value;
    result->bits[3] ^= SIGN_MASK;
    return status;
}