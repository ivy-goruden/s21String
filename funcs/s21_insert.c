#include <stdlib.h>

#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  start_index = start_index > src_len ? src_len : start_index;
  char *result = malloc(src_len + str_len + 1);

  result[src_len + str_len] = '\0';
  for (s21_size_t i = 0; i < start_index; result[i] = src[i], i++)
    ;
  for (s21_size_t i = start_index; i < (start_index + str_len);
       result[i] = str[i - start_index], i++)
    ;
  for (s21_size_t i = (start_index + str_len); i < (src_len + str_len);
       result[i] = src[i - str_len], i++)
    ;
  return result;
}
