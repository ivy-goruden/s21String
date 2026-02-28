#include "../s21_string.h"

void* s21_memset(void* str, int c, s21_size_t n) {
  // Copies the character c (an unsigned char) to the first n characters of
  // the
  // string pointed to, by the argument str.
  if (!str || !c || !n) {
    return str;
  }
  s21_uint8_t* s = (s21_uint8_t*)str;
  s21_uint8_t c1 = (s21_uint8_t)c;
  for (size_t i = 0; i < n; i++) {
    *s = c1;
    s++;
  }
  return str;
}