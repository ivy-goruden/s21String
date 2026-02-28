#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *begin;
  if (str) {
    begin = str;
  }
  if (!begin) {
    return S21_NULL;
  }

  int i = 0;
  char *result = S21_NULL;
  for (; begin[i] && s21_strchr(delim, begin[i]); i++)
    ;
  if (begin[i]) {
    result = begin + i;
  }

  for (; begin[i] && !s21_strchr(delim, begin[i]); i++)
    ;
  if (begin[i]) {
    begin[i] = '\0';
    begin = begin + i + 1;
  } else {
    begin = S21_NULL;
  }

  return result;
}
