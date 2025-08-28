#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) {
    return S21_NULL;
  }

  int len = s21_strlen(src);
  char *result = malloc(len * sizeof(char) + 1);
  for (int i = 0; i <= len; i++) {
    result[i] = 0;
  }

  int i = 0;
  for (; src[i] && s21_strchr(trim_chars, src[i]); i++)
    ;
  if (src[i]) {
    int j = len - 1;
    for (; j > i && s21_strchr(trim_chars, src[j]); j--)
      ;
    for (int p = i; p <= j; p++) {
      result[p - i] = src[p];
    }
  }

  return result;
}
