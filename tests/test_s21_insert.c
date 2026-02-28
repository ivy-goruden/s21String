#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1
START_TEST(test_insert_1) {
  char data[2000] = "000";
  const char *str = "hello";
  int pos = 0;
  char *expected = "hello000";
  char *result = s21_insert(data, str, pos);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 2
START_TEST(test_insert_2) {
  char data[2000] = "000000";
  const char *str = "hello";
  int pos = 3;
  char *expected = "000hello000";
  char *result = s21_insert(data, str, pos);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 3
START_TEST(test_insert_3) {
  char data[2000] = "";
  const char *str = "hello";
  int pos = 5;
  char *expected = "hello";
  char *result = s21_insert(data, str, pos);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест 4
START_TEST(test_null) {
  char *result = s21_insert(S21_NULL, S21_NULL, 0);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

// Создание тестового набора
Suite *insert_suite(void) {
  Suite *s = suite_create("insert_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_insert_1);
  tcase_add_test(tc_core, test_insert_2);
  tcase_add_test(tc_core, test_insert_3);
  tcase_add_test(tc_core, test_null);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_insert(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = insert_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}