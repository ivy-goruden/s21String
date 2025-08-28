#include <check.h>
#include <string.h>

#include "main_test.h"

// Тест 1
START_TEST(test_1) {
  char buffer[50];
  int age = 30;
  float height = 1.75;
  char name[] = "John";

  int bytes_written =
      sprintf(buffer, "Name: %s, Age: %d, Height: %.2f", name, age, height);

  char buffer1[50];
  int age1 = 30;
  float height1 = 1.75;
  char name1[] = "John";

  int bytes_written1 = s21_sprintf(buffer1, "Name: %s, Age: %d, Height: %.2f",
                                   name1, age1, height1);
  ck_assert_int_eq(bytes_written, bytes_written1);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест 2
START_TEST(test_2) {
  char buffer[50];
  int a = 10, b = 20, c;
  c = a + b;
  sprintf(buffer, "Sum of %d and %d is %d", a, b, c);
  char buffer1[50];
  int a1 = 10, b1 = 20, c1;
  c1 = a1 + b1;
  s21_sprintf(buffer1, "Sum of %d and %d is %d", a1, b1, c1);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест 3
START_TEST(test_3) {
  char buffer[100];
  float pi = 3.14159;
  sprintf(buffer, "The value of pi is %.2f.", pi);
  char buffer1[100];
  s21_sprintf(buffer1, "The value of pi is %.2f.", pi);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест %
START_TEST(test_perc) {
  char buffer[100];
  sprintf(buffer, "perc symbol %%");
  char buffer1[100];
  s21_sprintf(buffer1, "perc symbol %%");
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест char
START_TEST(test_char) {
  char ch = 'U';
  char buffer[100];
  sprintf(buffer, "char symbol %c.", ch);
  char buffer1[100];
  s21_sprintf(buffer1, "char symbol %c.", ch);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест long double
START_TEST(test_ld) {
  long double pi = 3.14159L;
  char buffer[100];
  sprintf(buffer, "The value of pi is %.2Lf.", pi);
  char buffer1[100];
  s21_sprintf(buffer1, "The value of pi is %.2Lf.", pi);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест int
START_TEST(test_int) {
  char buffer[150];
  int a = 10;
  short b = 20;
  long c = a + b;
  unsigned e = 10;
  unsigned short f = 20;
  unsigned long g = e + f;
  sprintf(buffer, "Sum of %d and %hd is %ld. Sum of %u and %hu is %lu", a, b, c,
          e, f, g);
  char buffer1[150];
  int a1 = 10;
  short b1 = 20;
  long c1 = a1 + b1;
  unsigned e1 = 10;
  unsigned short f1 = 20;
  unsigned long g1 = e1 + f1;
  s21_sprintf(buffer1, "Sum of %d and %hd is %ld. Sum of %u and %hu is %lu", a1,
              b1, c1, e1, f1, g1);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест float formats
START_TEST(test_float_formats) {
  double f1 = 3.14159, f2 = 0.999999, f3 = -3.14159, f4 = 0, f5 = 654.8999;
  char buffer[100];
  sprintf(buffer, "Values %-+.5f %-+10.5f %-+.f % -.5f %15f.", f1, f2, f3, f4,
          f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-+.5f %-+10.5f %-+.f % -.5f %15f.", f1, f2, f3,
              f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест float sharp option
START_TEST(test_float_sharp) {
  double f1 = 654.9999;
  char buffer[100];
  sprintf(buffer, "Values %-+#.5f %-+#10.5f %-+#.f % -#.8f %#15f", f1, f1, f1,
          f1, f1);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-+#.5f %-+#10.5f %-+#.f % -#.8f %#15f", f1, f1,
              f1, f1, f1);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест int formats
START_TEST(test_int_formats) {
  int f1 = 10, f2 = 999999, f3 = -3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-+.5d %-+10.5d %-+.d % -.8d %15d.", f1, f2, f3, f4,
          f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-+.5d %-+10.5d %-+.d % -.8d %15d.", f1, f2, f3,
              f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест pointer
START_TEST(test_pointer_formats) {
  int int1 = 10;
  void *p1 = &int1;
  char buffer[150];
  sprintf(buffer, "Values %p, %20p, %-20p, %5p, %21p.", p1, p1, p1, p1, NULL);
  char buffer1[150];
  s21_sprintf(buffer1, "Values %p, %20p, %-20p, %5p, %21p.", p1, p1, p1, p1,
              NULL);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест x option
START_TEST(test_x) {
  int f1 = 10, f2 = 999999, f3 = 3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-.5x %-10.5x %-.x %-.8x %15x.", f1, f2, f3, f4, f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-.5x %-10.5x %-.x %-.8x %15x.", f1, f2, f3, f4,
              f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест x option, long
START_TEST(test_x_long) {
  unsigned long f1 = 10, f2 = 999999, f3 = 3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-.5lx %-10.5lx %-.lx %-.8lx %15lx.", f1, f2, f3, f4,
          f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-.5lx %-10.5lx %-.lx %-.8lx %15lx.", f1, f2, f3,
              f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест x option, short
START_TEST(test_x_short) {
  unsigned short f1 = 10, f2 = 99, f3 = 3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-.5hx %-10.5hx %-.hx %-.8hx %15hx.", f1, f2, f3, f4,
          f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-.5hx %-10.5hx %-.hx %-.8hx %15hx.", f1, f2, f3,
              f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест o option
START_TEST(test_o) {
  int f1 = 10, f2 = 999999, f3 = 3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-.5o %-10.5o %-.o %-.8o %15o.", f1, f2, f3, f4, f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-.5o %-10.5o %-.o %-.8o %15o.", f1, f2, f3, f4,
              f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест o option, long
START_TEST(test_o_long) {
  unsigned long f1 = 10, f2 = 999999, f3 = 3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-.5lo %-10.5lo %-.lo %-.8lo %15lo.", f1, f2, f3, f4,
          f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-.5lo %-10.5lo %-.lo %-.8lo %15lo.", f1, f2, f3,
              f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест o option, short
START_TEST(test_o_short) {
  unsigned short f1 = 10, f2 = 99, f3 = 3, f4 = 0, f5 = 654;
  char buffer[100];
  sprintf(buffer, "Values %-.5ho %-10.5ho %-.ho %-.8ho %15ho.", f1, f2, f3, f4,
          f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-.5ho %-10.5ho %-.ho %-.8ho %15ho.", f1, f2, f3,
              f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест e option
START_TEST(test_e) {
  double f1 = 3.14159, f2 = 0.999999, f3 = -3.14159, f4 = 0, f5 = 654.8999,
         f6 = 65400;
  char buffer[100];
  sprintf(buffer, "Values %-+.5e %-+10.10e %-+.e % -.8E %15E %-+10.2e.", f1, f2,
          f3, f4, f5, f6);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-+.5e %-+10.10e %-+.e % -.8E %15E %-+10.2e.",
              f1, f2, f3, f4, f5, f6);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест e option, long
START_TEST(test_e_long) {
  long double f1 = 3.14159, f2 = 0.999999, f3 = -3.14159, f4 = 0, f5 = 654.8999;
  char buffer[100];
  sprintf(buffer, "Values %-+.5Le %-+10.10Le %-+.Le % -.8LE %15LE.", f1, f2, f3,
          f4, f5);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-+.5Le %-+10.10Le %-+.Le % -.8LE %15LE.", f1,
              f2, f3, f4, f5);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест g option
START_TEST(test_g) {
  double f1 = 3.14159, f2 = 0.999999, f3 = -3.14159, f4 = 0, f5 = 654.8999,
         f6 = 65400;
  char buffer[100];
  sprintf(buffer, "Values %-+.5g %-+10.10g %-+.g % -.8G %15G %-+10.2g.", f1, f2,
          f3, f4, f5, f6);
  char buffer1[100];
  s21_sprintf(buffer1, "Values %-+.5g %-+10.10g %-+.g % -.8G %15G %-+10.2g.",
              f1, f2, f3, f4, f5, f6);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест g option, long
START_TEST(test_g_long) {
  long double f1 = 3.14159, f2 = 0.999999, f3 = -3.14159, f4 = 0, f5 = 654.8999,
              f6 = 65400;
  char buffer[100];
  sprintf(buffer, "Values %-+.5Lg %-+10.10Lg %-+.Lg % -.8LG %15LG %-+10.2Lg.",
          f1, f2, f3, f4, f5, f6);
  char buffer1[100];
  s21_sprintf(buffer1,
              "Values %-+.5Lg %-+10.10Lg %-+.Lg % -.8LG %15LG %-+10.2Lg.", f1,
              f2, f3, f4, f5, f6);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест n option
START_TEST(test_n) {
  int c1, c2;
  char buffer1[100];
  char buffer2[100];
  sprintf(buffer1, "123456789%n0", &c1);
  s21_sprintf(buffer2, "123456789%n0", &c2);
  ck_assert_int_eq(c1, c2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест string
START_TEST(test_string) {
  char buffer[50];
  char buffer1[50];
  const char name[] = "John";
  int bytes_written = sprintf(buffer, "Name: %s", name);
  int bytes_written1 = s21_sprintf(buffer1, "Name: %s", name);

  ck_assert_int_eq(bytes_written, bytes_written1);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Тест null string
START_TEST(test_null_string) {
  char buffer[50];
  char buffer1[50];
  const char *name = S21_NULL;
  int bytes_written1 = s21_sprintf(buffer1, "Name: %s", name);
  int bytes_written = sprintf(buffer, "Name: %s", name);

  ck_assert_int_eq(bytes_written, bytes_written1);
  ck_assert_str_eq(buffer, buffer1);
}
END_TEST

// Создание тестового набора
Suite *sprintf_suite(void) {
  Suite *s = suite_create("sprintf_tests");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_perc);
  tcase_add_test(tc_core, test_char);
  tcase_add_test(tc_core, test_ld);
  tcase_add_test(tc_core, test_int);
  tcase_add_test(tc_core, test_float_formats);
  tcase_add_test(tc_core, test_float_sharp);
  tcase_add_test(tc_core, test_int_formats);
  tcase_add_test(tc_core, test_pointer_formats);
  tcase_add_test(tc_core, test_x);
  tcase_add_test(tc_core, test_x_long);
  tcase_add_test(tc_core, test_x_short);
  tcase_add_test(tc_core, test_o);
  tcase_add_test(tc_core, test_o_long);
  tcase_add_test(tc_core, test_o_short);
  tcase_add_test(tc_core, test_e);
  tcase_add_test(tc_core, test_e_long);
  tcase_add_test(tc_core, test_g);
  tcase_add_test(tc_core, test_g_long);
  tcase_add_test(tc_core, test_n);
  tcase_add_test(tc_core, test_string);
  tcase_add_test(tc_core, test_null_string);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_sprintf(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = sprintf_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}