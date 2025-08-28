#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Сравнение двух строк
START_TEST(test_compare_1) {
  char dest[1000] = "abc";
  char dest2[1000] = "abc";
  char two[] = "def";
  s21_size_t n = 3;

  s21_strncat(dest, two, n);
  strncat(dest2, two, n);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

// Тест 2: Сравнение двух строк(не полностью)
START_TEST(test_compare_2) {
  char dest[1000] = "abc";
  char dest2[1000] = "abc";
  char two[] = "def";
  s21_size_t n = 1;

  s21_strncat(dest, two, n);
  strncat(dest2, two, n);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

// Тест 3: Сравнение двух строк разной длины
START_TEST(test_compare_3) {
  char dest[1000] = "a";
  char dest2[1000] = "a";
  char two[] = "def";
  s21_size_t n = 3;

  s21_strncat(dest, two, n);
  strncat(dest2, two, n);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

// Тест 4: Сравнение спец символов
START_TEST(test_compare_4) {
  char dest[1000] = "Hello\nworld";
  char dest2[1000] = "Hello\nworld";
  char two[] = "Hello world";
  s21_size_t n = 10;

  s21_strncat(dest, two, n);
  strncat(dest2, two, n);

  ck_assert_str_eq(dest, dest2);
}
END_TEST

Suite *strncat_suite(void) {
  Suite *s = suite_create("strncat_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_compare_1);
  tcase_add_test(tc_core, test_compare_2);
  tcase_add_test(tc_core, test_compare_3);
  tcase_add_test(tc_core, test_compare_4);

  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strncat(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strncat_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
