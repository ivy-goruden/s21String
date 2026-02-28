#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int s21_sscanf(const char* str, const char* format, ...);

int main() {
  const char* data = "1782dabc";
  const char* format = "%o%*d";  // Your original format

  // Variables to store parsed data:
  int num = 0;         // for %d
  char ch = '\0';      // for %c
  char str[20] = {0};  // for %s (with buffer size 20)

  // Parse the input string
  int a = sscanf(data, format, &num, &num);

  // Output each variable one by one
  printf("1. Parsed integer (%%o): %d\n", a);

  printf("2. Parsed character (%%c): %c\n", ch);
  printf("3. Parsed string (%%s): %s\n", str);

  return 0;
}

char* delete_null(const char* str) {
  while (*str == ' ') {
    str++;
  }
  return str;
}

int s21_sscanf(const char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);  // Инициализация работы с аргументами

  int refactored_vals = 0;

  // char** tokens = char_to_list(format);

  const char* str_ptr = str;  //  pointer to the current ocation in the string
  int skip = 0;
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      skip = 0;
      if (*format == '*') {
        format++;
        skip = 1;
      }
      switch (*format) {
        case 'd':
          str_ptr = delete_null(str_ptr);

          char* end_ptr;
          int num = strtol(str_ptr, &end_ptr, 10);

          if (end_ptr == str_ptr) {
            va_end(args);
            return refactored_vals;
          }

          if (skip == 0) {
            refactored_vals++;
            int* arg = va_arg(args, int*);  // Получаем указатель на int
            *arg = (int)num;                // Записываем значение
          }
          str_ptr = end_ptr;
          break;

        case 's':
          str_ptr = delete_null(str_ptr);
          if (*str_ptr == '\0') {
            va_end(args);
            break;
          }
          if (skip == 0) {
            refactored_vals++;
            char* arg = va_arg(args, char*);
            while (*str_ptr != '\0' && *str_ptr != ' ') {
              *arg = *str_ptr;
              arg++;
              str_ptr++;
            }
            *arg = '\0';
          } else {
            while (*str_ptr != '\0' && *str_ptr != ' ') {
              str_ptr++;
            }
          }
          break;

        case 'c':
          if (*str_ptr == '\0') {
            va_end(args);
            return refactored_vals;
          }
          if (skip == 0) {
            refactored_vals++;
            char* arg = va_arg(args, char*);
            arg[0] = *str_ptr;
          }
          str_ptr++;
          break;

        case '%':
          if ('%' != *str_ptr) {
            va_end(args);
            return refactored_vals;
          }

        case 'o':
          str_ptr = delete_null(str_ptr);

          char* end_ptro;
          int numo = strtol(str_ptr, &end_ptro, 8);

          if (end_ptr == str_ptr) {
            va_end(args);
            return refactored_vals;
          }

          if (skip == 0) {
            refactored_vals++;
            int* arg = va_arg(args, int*);
            *arg = (int)num;
          }
          str_ptr = end_ptr;
          break;

        case 'p':
          str_ptr = delete_null(str_ptr);
          if (str_ptr[0] != '0' || (str_ptr[1] != 'x' || str_ptr[1] != 'X')) {
            va_end(args);
            return refactored_vals;
          }
          char* end_ptrp;
          int nump = strtol(str_ptr, &end_ptrp, 8);

          if (end_ptr == str_ptr) {
            va_end(args);
            return refactored_vals;
          }

          if (skip == 0) {
            refactored_vals++;
            int* arg = va_arg(args, int*);  // Получаем указатель на int
            *arg = (int)num;                // Записываем значение
          }
          str_ptr = end_ptr;
          break;
      }

    } else {
      if (*format != *str_ptr) {
        va_end(args);
        return refactored_vals;
      }
    }
    format++;
  }
  va_end(args);
  return refactored_vals;
}