#include "../s21_string.h"

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  if (!dest || !src || !n) {
    return dest;
  }
  s21_uint8_t* d = (s21_uint8_t*)dest;
  const s21_uint8_t* s = (const s21_uint8_t*)src;
  while (n > 8) {
    *(s21_uint64_t*)d = *(s21_uint64_t*)s;
    d += 8;
    s += 8;
    n -= 8;
  }
  while (n > 4) {
    *(s21_uint32_t*)d = *(s21_uint32_t*)s;
    d += 4;
    s += 4;
    n -= 4;
  }
  while (n > 0) {
    *d = *s;
    d += 1;
    s += 1;
    n--;
  }
  return dest;
}