// #include <check.h>
// #include <string.h>

// #include "../tests.h"

// // Тест 1
// START_TEST(test_1) {
//   char buff[50] = "F, 69, 123.45";
//   char c;
//   int n;
//   double d;
//   sscanf(buff, "%c, %d, %lf", &c, &n, &d);
//   char c1;
//   int n1;
//   double d1;
//   s21_sscanf(buff, "%c, %d, %lf", &c1, &n1, &d1);
//   ck_assert_ptr_eq(&c, &c1);
//   ck_assert_ptr_eq(&n, &n1);
//   ck_assert_ptr_eq(&d, &d1);
// }
// END_TEST

// // Тест 2
// START_TEST(test_2) {
//   char buff[50] = "Tom 23 505.99";
//   char name[10];
//   int age;
//   double salary;
//   sscanf(buff, "%s %d %lf", name, &age, &salary);
//   char name1[10];
//   int age1;
//   double salary1;
//   s21_sscanf(buff, "%s %d %lf", name1, &age1, &salary1);
//   ck_assert_ptr_eq(&name, &name1);
//   ck_assert_ptr_eq(&age, &age);
//   ck_assert_ptr_eq(&salary, &salary1);
// }
// END_TEST

// // Тест 3
// START_TEST(test_3) {
//   char *buff = "Name is Tom and age is 38";
//   char name[10];
//   int age;

//   sscanf(buff, "Name is %s and age is %d", name, &age);
//   char name1[10];
//   int age1;
//   ck_assert_ptr_eq(&name, &name1);
//   ck_assert_ptr_eq(&age, &age1);
// }
// END_TEST

// // Создание тестового набора
// Suite *sscanf_suite(void) {
//   Suite *s = suite_create("sscanf_tests");

//   TCase *tc_core = tcase_create("Core");
//   tcase_add_test(tc_core, test_1);
//   tcase_add_test(tc_core, test_2);
//   tcase_add_test(tc_core, test_3);
//   suite_add_tcase(s, tc_core);
//   return s;
// }

// // Запуск тестов
// int main_sscanf(void) {
//   int number_failed;
//   Suite *s;
//   SRunner *sr;

//   s = sscanf_suite();
//   sr = srunner_create(s);

//   srunner_run_all(sr, CK_VERBOSE);
//   number_failed = srunner_ntests_failed(sr);
//   srunner_free(sr);

//   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
// }