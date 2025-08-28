#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int i = 0;
  char *result = S21_NULL;
  for (; str1[i] && !s21_strchr(str2, str1[i]); i++)
    ;
  if (str1[i]) {
    result = (char *)(str1 + i);
  }
  return result;
}
