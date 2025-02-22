#include "../s21_decimal.h"


int s21_is_equal(s21_decimal first, s21_decimal second) {
    int result = TRUE;
    int scale_first = (first.bits[3] & SCALE_MASK);
    int scale_second = (second.bits[3] & SCALE_MASK);
    if (scale_first != scale_second) {
      result = FALSE;
    } else {
      int sign_first = (first.bits[3] & SIGN_MASK);
      int sign_second = (second.bits[3] & SIGN_MASK);
      result = (sign_first == sign_second) ? TRUE : FALSE;
      for (int i = 0; i < 3 && result; i++) {
        result = (first.bits[i] != second.bits[i]) ? FALSE : TRUE;
      }
    }
    return result;
}

