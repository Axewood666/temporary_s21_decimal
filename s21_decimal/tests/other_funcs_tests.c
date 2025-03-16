#include "helpers_test.h"

START_TEST(test_truncate_1) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal need_decimal = {{0x000004D2, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_truncate(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal need_decimal = {{0x000004D2, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_truncate(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_truncate_3) {
  s21_decimal number_decimal = {
      {0x4D6C8050, 0x0003F28F, 0x00000000, 0x000b0000}};
  s21_decimal need_decimal = {{0x00002B67, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_truncate(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_negate_1) {
  s21_decimal decimal = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal need_decimal = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_negate(decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_negate_2) {
  s21_decimal decimal = {{0x00000020, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal need_decimal = {{0x00000020, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_negate(decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_floor_1) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal need_decimal = {{0x000004D2, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_floor_2) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal need_decimal = {{0x000004D3, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_floor_3) {
  s21_decimal number_decimal = {
      {0x4D6C8050, 0x0003F28F, 0x00000000, 0x000b0000}};
  s21_decimal need_decimal = {{0x00002B67, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_floor(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_round_1) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x00020000}};
  s21_decimal need_decimal = {{0x000004D3, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_round(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_round_2) {
  s21_decimal number_decimal = {
      {0x0001E240, 0x00000000, 0x00000000, 0x80040000}};
  s21_decimal need_decimal = {{0x0000000C, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_round(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

START_TEST(test_round_3) {
  s21_decimal number_decimal = {
      {0x4D6C8050, 0x0003F28F, 0x00000000, 0x000b0000}};
  s21_decimal need_decimal = {{0x00002B67, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result_decimal = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_round(number_decimal, &result_decimal), 0);
  comparison(need_decimal, result_decimal);
}
END_TEST

Suite *test_other_funcs(void) {
  Suite *s = suite_create("Other funcs test");
  TCase *tc = tcase_create("Tests");

  tcase_add_test(tc, test_truncate_1);
  tcase_add_test(tc, test_truncate_2);
  tcase_add_test(tc, test_truncate_3);

  tcase_add_test(tc, test_negate_1);
  tcase_add_test(tc, test_negate_2);

  tcase_add_test(tc, test_floor_1);
  tcase_add_test(tc, test_floor_2);
  tcase_add_test(tc, test_floor_3);

  tcase_add_test(tc, test_round_1);
  tcase_add_test(tc, test_round_2);
  tcase_add_test(tc, test_round_3);

  suite_add_tcase(s, tc);
  return s;
}