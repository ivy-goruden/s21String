#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Поиск существующего символа
START_TEST(test_find_existing_char) {
  char data[] = "Hello, world!";
  int ch = 'w';

  char *result = s21_strchr(data, ch);
  char *expected = strchr(data, ch);

  ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 2: Поиск символа конца строки
START_TEST(test_find_line_end) {
  char data[] = "Hello, world!";
  int ch = '\0';

  char *result = s21_strchr(data, ch);
  char *expected = strchr(data, ch);

  ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 3: Поиск существующего символа
START_TEST(test_find_unexisting_char) {
  char data[] = "Hello, world!";
  int ch = 'f';

  char *result = s21_strchr(data, ch);
  char *expected = strchr(data, ch);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *strchr_suite(void) {
  Suite *s = suite_create("strchr_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_find_existing_char);
  tcase_add_test(tc_core, test_find_line_end);
  tcase_add_test(tc_core, test_find_unexisting_char);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strchr(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strchr_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}