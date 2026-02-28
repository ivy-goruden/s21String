#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Поиск существующего символа
START_TEST(test_compare_strings) {
  char *first = "Hello";
  char *second = "eel";

  s21_size_t result = s21_strcspn(first, second);
  s21_size_t expected = strcspn(first, second);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_compare_with_line_end) {
  char *first = "Hello";
  char *second = "\0";

  s21_size_t result = s21_strcspn(first, second);
  s21_size_t expected = strcspn(first, second);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_compare_diferent_strings) {
  char *first = "Hello";
  char *second = "cat";

  s21_size_t result = s21_strcspn(first, second);
  s21_size_t expected = strcspn(first, second);

  ck_assert_int_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *strcspn_suite(void) {
  Suite *s = suite_create("strcspn_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_compare_strings);
  tcase_add_test(tc_core, test_compare_with_line_end);
  tcase_add_test(tc_core, test_compare_diferent_strings);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strcspn(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strcspn_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}