#include <check.h>
#include <stdio.h>

Suite *test_arithmetic(void);
Suite *test_comparison(void);
Suite *test_conversion(void);
Suite *test_other_funcs(void);

#define TEST_FUNCS  test_comparison(),test_arithmetic(),test_conversion(), test_other_funcs()