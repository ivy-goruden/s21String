#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: обрезает предложение
START_TEST(test_to_smaller_sentense) {
  char data[] = "Hello, World!";
  const char *trim_char = " !";
  char *result = s21_trim(data, trim_char);
  char *expected = "Hello, World";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 2: обрезает предложение
START_TEST(test_to_smaller_empty_string) {
  char data[] = "Hello, World!";
  const char *trim_char = "";
  char *result = s21_trim(data, trim_char);
  char *expected = "Hello, World!";

  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 3: обрезает предложение
START_TEST(test_to_smaller_line_end) {
  char data[] = "Hello, World!";
  const char *trim_char = "Hello";
  char *result = s21_trim(data, trim_char);
  char *expected = ", World!";

  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 4
START_TEST(test_null) {
  const char *trim_char = "Hello";
  char *result = s21_trim(S21_NULL, trim_char);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

// Создание тестового набора
Suite *trim_suite(void) {
  Suite *s = suite_create("trim_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_to_smaller_sentense);
  tcase_add_test(tc_core, test_to_smaller_empty_string);
  tcase_add_test(tc_core, test_to_smaller_line_end);
  tcase_add_test(tc_core, test_null);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_trim(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = trim_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}