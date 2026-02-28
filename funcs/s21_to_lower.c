#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  if (!str) {
    return S21_NULL;
  }

  int len = s21_strlen(str);
  char *new_line = malloc(len * sizeof(char) + 1);
  int i = 0;
  while (str[i]) {
    new_line[i] = str[i] >= 'A' && str[i] <= 'Z' ? str[i] + 32 : str[i];
    i++;
  }
  new_line[i] = 0;
  return new_line;
}
