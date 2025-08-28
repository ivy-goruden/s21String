#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: измерение длины строки
START_TEST(test_string_measure) {
  char string[] = "Hello";

  s21_size_t result = s21_strlen(string);
  size_t expected = strlen(string);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 2: измерение длины пустой строки
START_TEST(test_empty_string_measure) {
  char string[] = "";

  s21_size_t result = s21_strlen(string);
  size_t expected = strlen(string);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест 3: измерение длины конца строки
START_TEST(test_string_end_measure) {
  char string[] = "\0Hello";

  s21_size_t result = s21_strlen(string);
  size_t expected = strlen(string);

  ck_assert_int_eq(result, expected);
}
END_TEST

Suite *strlen_suite(void) {
  Suite *s = suite_create("strlen_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_string_measure);
  tcase_add_test(tc_core, test_empty_string_measure);
  tcase_add_test(tc_core, test_string_end_measure);

  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strlen(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strlen_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}