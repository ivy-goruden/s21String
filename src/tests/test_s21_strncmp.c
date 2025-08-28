#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 0: Сравнение пустых строк
START_TEST(test_compare_two_empties) {
  char one[] = "";
  char two[] = "";
  s21_size_t n = 1;

  int result = s21_strncmp(one, two, n);
  int expected = strncmp(one, two, n);
  expected = expected > 0 ? 1 : (expected < 0 ? -1 : 0);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 1: Сравнение двух строк
START_TEST(test_compare_two_strings) {
  char one[] = "abc";
  char two[] = "abz";
  s21_size_t n = 3;

  int result = s21_strncmp(one, two, n);
  int expected = strncmp(one, two, n);
  expected = expected > 0 ? 1 : (expected < 0 ? -1 : 0);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 2: Сравнение двух строк(не полностью)
START_TEST(test_compare_two_strings_partialy) {
  char one[] = "abc";
  char two[] = "abz";
  s21_size_t n = 1;

  int result = s21_strncmp(one, two, n);
  int expected = strncmp(one, two, n);
  expected = expected > 0 ? 1 : (expected < 0 ? -1 : 0);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 3: Сравнение двух строк разной длины
START_TEST(test_compare_two_strings_different) {
  char one[] = "a";
  char two[] = "abb";
  s21_size_t n = 3;

  int result = s21_strncmp(one, two, n);
  int expected = strncmp(one, two, n);
  expected = expected > 0 ? 1 : (expected < 0 ? -1 : 0);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 4: Сравнение двух строк разной длины 2
START_TEST(test_compare_two_strings_different_2) {
  char one[] = "abc";
  char two[] = "a";
  s21_size_t n = 3;

  int result = s21_strncmp(one, two, n);
  int expected = strncmp(one, two, n);
  expected = expected > 0 ? 1 : (expected < 0 ? -1 : 0);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 5: Сравнение спец символов
START_TEST(test_compare_special_string) {
  char one[] = "Hello\nworld";
  char two[] = "Hello world";
  s21_size_t n = 7;

  int result = s21_strncmp(one, two, n);
  int expected = strncmp(one, two, n);
  expected = expected > 0 ? 1 : (expected < 0 ? -1 : 0);

  ck_assert_int_eq(result, expected);
}
END_TEST

Suite *strncmp_suite(void) {
  Suite *s = suite_create("strncmp_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_compare_two_empties);
  tcase_add_test(tc_core, test_compare_two_strings);
  tcase_add_test(tc_core, test_compare_two_strings_partialy);
  tcase_add_test(tc_core, test_compare_two_strings_different);
  tcase_add_test(tc_core, test_compare_two_strings_different_2);
  tcase_add_test(tc_core, test_compare_special_string);

  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strncmp(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strncmp_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
