#include "../s21_string.h"

int compare(const char *str_1, const char *str_2) {
  while (*str_1 && *str_2) {
    if (*str_1 != *str_2) {
      return 0;
    }
    str_1++;
    str_2++;
  }
  return (*str_2 == '\0');
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    while (*haystack != '\0') {
      if ((*haystack == *needle) && compare(haystack, needle)) {
        result = (char *)haystack;
        break;
      }
      haystack++;
    }
  }
  return result;
}
