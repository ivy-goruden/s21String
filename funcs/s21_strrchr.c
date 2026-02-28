#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  int len = s21_strlen(str);
  if (c == '\0') {
    result = (char *)(len == 0 ? str : str + len);
  }
  int ind = -1;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      ind = i;
    }
  }
  if (ind != -1) {
    result = (char *)(str + ind);
  }
  return result;
}
