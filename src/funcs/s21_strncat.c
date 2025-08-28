#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *orig_dest = dest;

  while (*dest) {
    dest++;
  }
  while (*src && n--) {
    *dest++ = *src++;
  }
  *dest = '\0';
  return orig_dest;
}