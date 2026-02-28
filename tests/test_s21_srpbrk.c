#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Поиск одного из существующих символа
START_TEST(test_find_one_of_existing_char) {
  char data[] = "Hello, world!";
  char data2[] = "eel";

  char *result = s21_strpbrk(data, data2);
  char *expected = strpbrk(data, data2);

  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 2: Поиск конца строки
START_TEST(test_find_line_end) {
  char data[] = "Hello, world!";
  char data2[] = "\0";

  char *result = s21_strpbrk(data, data2);
  char *expected = strpbrk(data, data2);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Тест 3: Поиск несуществующих символов
START_TEST(test_find_unexisting_chars) {
  char data[] = "Hello, world!";
  char data2[] = "cat";

  char *result = s21_strpbrk(data, data2);
  char *expected = strpbrk(data, data2);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *strpbrk_suite(void) {
  Suite *s = suite_create("strpbrk_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_find_one_of_existing_char);
  tcase_add_test(tc_core, test_find_line_end);
  tcase_add_test(tc_core, test_find_unexisting_chars);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strpbrk(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strpbrk_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}