#include <stdio.h>
#include <stdlib.h>

#ifndef s21_string_h
#define s21_string_h

#include "funcs/s21_strerror.h"

typedef unsigned int s21_size_t;
typedef unsigned char s21_uint8_t;
typedef unsigned int s21_uint32_t;
typedef unsigned long long s21_uint64_t;
#define S21_NULL (void*)0

void* s21_memchr(const void* str, int c, s21_size_t n);
int s21_memcmp(const void* str1, const void* str2, s21_size_t n);
void* s21_memcpy(void* dest, const void* src, s21_size_t n);
void* s21_memset(void* str, int c, s21_size_t n);
s21_size_t s21_strlen(const char* str);
char* s21_strncpy(char* destination, const char* sourse, s21_size_t n);
int s21_strncmp(const char* str1, const char* str2, s21_size_t n);
char* s21_strncat(char* dest, const char* src, s21_size_t n);
int s21_sprintf(char *str, const char *format, ...);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
char *s21_strchr(const char *str, int c);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);

#endif  // s21_string_h
