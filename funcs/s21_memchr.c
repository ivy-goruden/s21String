#include "../s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  // Searches for the first occurrence of the character c (an unsigned char) in
  // the first n bytes of the string pointed to, by the argument str.
  s21_uint8_t* string = (s21_uint8_t*)str;
  s21_uint8_t value = (s21_uint8_t)c;
  if (!n) {
    return NULL;
  }
  s21_size_t i = n;
  while (i + 1 > 0) {
    if (*string == value) {
      return string;
    }
    string++;
    i--;
  }
  return NULL;
}