#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: 0
START_TEST(test_0) {
  int number = 0;

  char *result = s21_strerror(number);
  char *expected = strerror(number);

  //   ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 2: 1
START_TEST(test_1) {
  int number = 1;

  char *result = s21_strerror(number);
  char *expected = strerror(number);

  //   ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 3: 2
START_TEST(test_2) {
  int number = 2;

  char *result = s21_strerror(number);
  char *expected = strerror(number);

  //   ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 4: 134
START_TEST(test_134) {
  int number = 134;

  char *result = s21_strerror(number);
  char *expected = strerror(number);

  //   ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST  // Тест 4: 134

// Тест 5: 41
START_TEST(test_41) {
  int number = 41;

  char *result = s21_strerror(number);
  char *expected = strerror(number);

  //   ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST  // Тест 5: 41

// Тест 6: -4
START_TEST(test_n1) {
  int number = -1;

  char *result = s21_strerror(number);
  char *expected = strerror(number);

  //   ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST  // Тест 6: -1

    // Создание тестового набора
    Suite *
    strerror_suite(void) {
  Suite *s = suite_create("strerror_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_0);
  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_134);
  tcase_add_test(tc_core, test_41);
  tcase_add_test(tc_core, test_n1);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strerror(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strerror_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}