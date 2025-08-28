#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Деление на пробелы
START_TEST(test_cut_in_spaces) {
  char data[] = "Hello, world!";
  char *ch = " ";

  char *result = s21_strtok(data, ch);
  char *expected = strtok(data, ch);

  ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 2: Деление на запятые
START_TEST(test_cut_in_commas) {
  char data[] = "Hello, world!, ,";
  char *ch = ",";

  char *result = s21_strtok(data, ch);
  char *expected = strtok(data, ch);

  ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 3: деление на ..
START_TEST(test_cut_in_dots) {
  char data[] = "Hello, world!";
  char *ch = "cat";

  char *result = s21_strtok(data, ch);
  char *expected = strtok(data, ch);

  ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *strtok_suite(void) {
  Suite *s = suite_create("strtok_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_cut_in_spaces);
  tcase_add_test(tc_core, test_cut_in_commas);
  tcase_add_test(tc_core, test_cut_in_dots);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strtok(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strtok_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}