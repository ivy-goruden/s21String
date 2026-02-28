#include "../s21_string.h"

char *s21_strncpy(char *destination, const char *sourse, s21_size_t n) {
  s21_size_t i;

  for (i = 0; i < n && sourse[i] != '\0'; i++) destination[i] = sourse[i];
  for (; i < n; i++) destination[i] = '\0';
  return destination;
}