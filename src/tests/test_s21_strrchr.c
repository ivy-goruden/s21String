#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Находит последнее вхождение символа в строке
START_TEST(test_find_first_occurence_of_existing_char) {
  char data[] = "Hello, world!";
  int ch = 'w';

  char *result = s21_strrchr(data, ch);
  char *expected = strrchr(data, ch);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Тест 2: Находит последнее вхождение конца строки
START_TEST(test_find_first_occurence_of_line_end) {
  char data[] = "Hello, world!";
  int ch = '\0';

  char *result = s21_strrchr(data, ch);
  char *expected = strrchr(data, ch);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Тест 3: Находит последнее вхождение несуществующего символа
START_TEST(test_find_first_occurence_of_unexisting_char) {
  char data[] = "Hello, world!";
  int ch = 'c';

  char *result = s21_strrchr(data, ch);
  char *expected = strrchr(data, ch);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *strrchr_suite(void) {
  Suite *s = suite_create("strrchr_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_find_first_occurence_of_existing_char);
  tcase_add_test(tc_core, test_find_first_occurence_of_line_end);
  tcase_add_test(tc_core, test_find_first_occurence_of_unexisting_char);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_strrchr(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = strrchr_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}