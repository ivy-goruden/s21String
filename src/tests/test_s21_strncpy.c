#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Перенос строки
START_TEST(test_move_string) {
  char src[] = "Hello";
  s21_size_t n = 5;
  char dest1[1000] = {0};
  char dest2[1000] = {0};

  char *result = s21_strncpy(dest1, src, n);
  char *expected = strncpy(dest2, src, n);

  // ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 2: Перенос строки с лишними символами
START_TEST(test_move_string_extra) {
  char src[] = "Hello";
  s21_size_t n = 7;
  char dest1[1000] = {0};
  char dest2[1000] = {0};

  char *result = s21_strncpy(dest1, src, n);
  char *expected = strncpy(dest2, src, n);

  // ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

Suite *strncpy_suite(void) {
  Suite *s = suite_create("strncpy_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_move_string);
  tcase_add_test(tc_core, test_move_string_extra);

  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strncpy(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strncpy_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}