#include "../s21_string.h"

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  // Compares the first n bytes of str1 and str2.
  if (!str1 || !str2 || !n) {
    return 0;
  }
  s21_uint8_t* one = (s21_uint8_t*)str1;
  s21_uint8_t* two = (s21_uint8_t*)str2;
  while (n > 0) {
    if ((!two) || *one > *two || (!one) || *one < *two) {
      return ((*one) ? *one : 0) - ((*two) ? *two : 0);
    }

    one++;
    two++;
    n--;
  }
  return 0;
}
