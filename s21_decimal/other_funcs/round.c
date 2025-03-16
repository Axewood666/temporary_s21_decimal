#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    if (!result) {
        return 1;
    }
    int status = 0;

    int sign = get_sign(value);

    s21_decimal frac;
    s21_decimal val_uns_trun;
    s21_decimal val_uns = s21_decimal_abs(value);
    s21_truncate(val_uns, &val_uns_trun);
    s21_sub(val_uns, val_uns_trun, &frac);
    val_uns_trun = s21_round_bank(val_uns_trun, frac);
    
    *result = val_uns_trun;
    set_sign(result, sign);
    return status;
}