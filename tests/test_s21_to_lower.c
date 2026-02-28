#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Уменьшает предложение
START_TEST(test_to_smaller_sentense) {
  char data[] = "Hello, World!";

  char *result = s21_to_lower(data);
  char *expected = "hello, world!";

  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 2: Уменьшает пустую строку
START_TEST(test_to_smaller_empty_string) {
  char data[] = "";

  char *result = s21_to_lower(data);
  char *expected = "";

  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 3: Уменьшает конец строки
START_TEST(test_to_smaller_line_end) {
  char data[] = "aaaa\0bbbb";

  char *result = s21_to_lower(data);
  char *expected = "aaaa";

  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 4
START_TEST(test_null) {
  char *result = s21_to_lower(S21_NULL);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

// Создание тестового набора
Suite *to_lower_suite(void) {
  Suite *s = suite_create("to_lower_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_to_smaller_sentense);
  tcase_add_test(tc_core, test_to_smaller_empty_string);
  tcase_add_test(tc_core, test_to_smaller_line_end);
  tcase_add_test(tc_core, test_null);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_to_lower(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = to_lower_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}