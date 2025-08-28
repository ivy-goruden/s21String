#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1: Замена части слова
START_TEST(test_replace_word_part) {
  char string[] = "Hello";
  int value = 'o';
  s21_size_t n = 4;

  void *result = s21_memset(string, value, n);
  void *expected = memset(string, value, n);

  ck_assert_ptr_eq(result, expected);
  ck_assert_str_eq(result, expected);
}
END_TEST

// Тест 2: Замена несуществующих символов
// START_TEST(test_replace_empty_symbols) {
//   char string[] = "Hi";
//   int value = 'o';
//   s21_size_t n = 4;

//   void *result = s21_memset(string, value, n);
//   void *expected = memset(string, value, n);

//   ck_assert_ptr_eq(result, expected);
// }
// END_TEST

// Тест 3: Замена нуля символов
START_TEST(test_replace_no_symbols) {
  char string[] = "Hello";
  int value = 'o';
  s21_size_t n = 0;

  void *result = s21_memset(string, value, n);
  void *expected = memset(string, value, n);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

Suite *memset_suite(void) {
  Suite *s = suite_create("memset_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_replace_word_part);
  // tcase_add_test(tc_core, test_replace_empty_symbols);
  tcase_add_test(tc_core, test_replace_no_symbols);

  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_memset(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = memset_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}