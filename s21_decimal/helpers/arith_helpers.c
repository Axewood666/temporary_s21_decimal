#include "helpers.h"

void align_scales(s21_decimal value_1, s21_decimal value_2,double_decimal *value_1d,double_decimal *value_2d){
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);

    null_tech_bits(&value_1);
    null_tech_bits(&value_2);
    
    if(scale_1 > scale_2){
        *value_1d = create_double_decimal_from_decimal(value_1);
        *value_2d = decimal_binay_mul(value_2,get_ten_pow(scale_1-scale_2));
    }else if(scale_1 < scale_2){
        *value_1d = decimal_binay_mul(value_1,get_ten_pow(scale_2-scale_1));
        *value_2d = create_double_decimal_from_decimal(value_2);
    }else{
        
        *value_1d = create_double_decimal_from_decimal(value_1);
        *value_2d = create_double_decimal_from_decimal(value_2);
    }
}

double_decimal binary_mul_big(double_decimal value_1,s21_decimal value_2){
    double_decimal result = create_double_decimal_from_decimal(create_zero_decimal());
    double_decimal temp = value_1;

    int first_bit_index = find_first_bit(value_2);

    for(int i = 0;i<=first_bit_index;i++){
        if(get_bit(value_2,i)){
            result = double_decimal_add(result,temp);
        }
        shift_left_big(&temp,1);
    }

    return result;
}

double_decimal double_decimal_add(double_decimal value_1,double_decimal value_2){
    int carry = 0;  // перенос
    double_decimal result = create_double_decimal_from_decimal(create_zero_decimal());
    for(int i = 0;i<256;i++){
        int bit_1 = get_bit_big(value_1, i);
        int bit_2 = get_bit_big(value_2, i);
        int sum = bit_1 + bit_2 + carry;
        set_bit_big(&result, i, sum % 2);
        carry = sum / 2;
        // printf("%d -> %d ->|%.x||%.x||%.x||%.x||%.x||%.x||%.x||%.x|\n",i,sum,result.decimal[1].bits[3],
        //     result.decimal[1].bits[2],
        //     result.decimal[1].bits[1],
        //     result.decimal[1].bits[0],
        //     result.decimal[0].bits[3],
        //     result.decimal[0].bits[2],
        //     result.decimal[0].bits[1],
        //     result.decimal[0].bits[0]
        // );
    }
    
    return result;
}

s21_decimal s21_decimal_add(s21_decimal value_1,s21_decimal value_2){
    int carry = 0;  // перенос
    s21_decimal result = create_zero_decimal(); 
    for(int i = 0;i<128;i++){
        int bit_1 = get_bit(value_1, i);
        int bit_2 = get_bit(value_2, i);
        int sum = bit_1 + bit_2 + carry;
        set_bit(&result, i, sum % 2);
        carry = sum / 2;
    }
    return result;

}

int get_shift_to_decimal(double_decimal value){
    
    int pow = 0;
    if(!(s21_decimal_binary_equal_zero(value.decimal[0]) && s21_decimal_binary_equal_zero(value.decimal[1]))){
        double_decimal max_number = create_double_decimal_from_decimal(s21_decimal_get_max());
        double_decimal quotient = double_decimal_binary_division(value,max_number,NULL);
        
        while(1){
            int compare = s21_decimal_binary_compare(quotient.decimal[0],get_ten_pow(pow));
            if(compare == -1 || compare == 0){
                break;
            }
            pow++;
            
        }
        double_decimal temp = double_decimal_binary_division(value,create_double_decimal_from_decimal(get_ten_pow(pow)),NULL);
        
        if(!s21_decimal_binary_equal_zero(temp.decimal[1]) || temp.decimal[0].bits[3]!=0){
            pow++;
        }

    }

    return pow;
}


double_decimal double_decimal_binary_division(double_decimal value_1,double_decimal value_2,double_decimal *remainder){
    double_decimal result;
    double_decimal partial_remainder = create_double_decimal_from_decimal(create_zero_decimal());
    double_decimal quotient = create_double_decimal_from_decimal(create_zero_decimal());
    if(s21_decimal_binary_equal_zero(value_1.decimal[0]) && s21_decimal_binary_equal_zero(value_1.decimal[1])){
        //когда делимое равно 0
    } else if(double_decimal_binary_compare(value_1,value_2)==-1){
        //когда делимое меньше делителя
        partial_remainder = value_1;
    }else{
        int left_bit_index_1 = find_first_bit(value_1.decimal[1]);
        if(left_bit_index_1==-1){
            left_bit_index_1 = find_first_bit(value_1.decimal[0]);
        }else{
            left_bit_index_1 += 128;
        }
        int left_bit_index_2 = find_first_bit(value_2.decimal[1]);
        if(left_bit_index_2==-1){
            left_bit_index_2 = find_first_bit(value_2.decimal[0]);
        }else{
            left_bit_index_2 += 128;
        }
        
        int shift = left_bit_index_1 - left_bit_index_2;
        shift_left_big(&value_2,shift);
        double_decimal divindend = value_1;
        int need_sub = 1;
        
        while(shift>=0){
            if(need_sub){
                partial_remainder = big_binary_sub(divindend,value_2);
            }else{
                partial_remainder = double_decimal_add(divindend,value_2);
            }
            shift_left_big(&quotient,1);
            if(get_bit(partial_remainder.decimal[1],127)==0){
                set_bit(&quotient.decimal[0],0,1);
            }
            divindend = partial_remainder;
            shift_left_big(&divindend,1);
            if(get_bit(partial_remainder.decimal[1],127)==0){
                need_sub = 1;
            }else{
                need_sub = 0;
            }
            shift--; 
            
        }
        if(get_bit(partial_remainder.decimal[1],127)){
            partial_remainder = double_decimal_add(partial_remainder,value_2);
        }
        shift_right_big(&partial_remainder,left_bit_index_1-left_bit_index_2);
    }
    result = quotient;
    if(remainder!=NULL){
        *remainder = partial_remainder;
    }
    
    return result;

}

double_decimal big_binary_sub(double_decimal value_1,double_decimal value_2){
    double_decimal result;
    value_2.decimal[0] = decimal_binary_not(value_2.decimal[0]);
    value_2.decimal[1] = decimal_binary_not(value_2.decimal[1]);
    double_decimal one = create_double_decimal_from_decimal(s21_decimal_get_one());

    value_2 = double_decimal_add(value_2,one);

    result = double_decimal_add(value_1,value_2);
    return result;
}

s21_decimal s21_round_bank(s21_decimal integer, s21_decimal fractional){
    s21_decimal zero_dot_five = {{0x5, 0x0, 0x0, 0x10000}};
    s21_decimal result;

    if(s21_is_equal(fractional,zero_dot_five)){
        if(s21_decimal_even(integer)){
            result = integer;
        }else{
            
            result = s21_decimal_add(integer,s21_decimal_get_one());
        }
    }else if(s21_is_greater(fractional,zero_dot_five)){
        result = s21_decimal_add(integer,s21_decimal_get_one());
    }else{
        result = integer;
    }
    return result;
}

double_decimal decimal_binay_mul(s21_decimal value_1,s21_decimal value_2){
    
    double_decimal result = create_double_decimal_from_decimal(create_zero_decimal());
    double_decimal temp = create_double_decimal_from_decimal(value_1);
    int first_bit = find_first_bit(value_2);

    for(int i = 0;i<=first_bit;i++){
        if(get_bit(value_2,i)==1){
            result = double_decimal_add(result,temp);
        }
        shift_left_big(&temp,1);
    }
    return result;
}