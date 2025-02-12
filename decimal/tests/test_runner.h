#include <check.h>
#include <stdio.h>

Suite *test_arithmetic(void);
Suite *test_comparison(void);
Suite *test_conversion(void);
Suite *test_other_funcs(void);

#define TEST_FUNCS test_conversion(), test_arithmetic(), test_other_funcs(), test_comparison()