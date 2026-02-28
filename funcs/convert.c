#include "convert.h"

#include <stdio.h>

void reverse(char *str, int len) {
  int i = 0, j = len - 1;
  while (i < j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++;
    j--;
  }
}

void unsigned_to_str(unsigned long long num, char *str, unsigned char basis) {
  int i = 0;
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }
  while (num > 0) {
    str[i++] = (num % basis) + '0';
    num /= basis;
  }
  reverse(str, i);
  str[i] = '\0';
}

void to_dec(unsigned long long num, char *str) {
  unsigned_to_str(num, str, 10);
}

void to_oct(unsigned long long num, char *str) { unsigned_to_str(num, str, 8); }

void int_to_str(long long num, char *str) {
  int neg = 0;
  if (num < 0) {
    num = -num;
    neg = 1;
  }
  if (neg && num != 0) {
    str[0] = '-';
    str++;
  }
  to_dec(num, str);
}

void to_hex(char *dest, unsigned long long value, unsigned short upper) {
  int j = 0, p = 0;
  unsigned char *pp = (unsigned char *)&value;
  for (unsigned i = 0; i < sizeof(unsigned long long); i++) {
    int n = sizeof(unsigned long long) - i - 1;
    unsigned char b = *(pp + n);
    if (b > 0 || p > 0) {
      unsigned char d1 = b / 16;
      unsigned char d2 = b % 16;
      int a = upper ? 55 : 87;
      char c1 = d1 > 9 ? a + d1 : '0' + d1;
      char c2 = d2 > 9 ? a + d2 : '0' + d2;
      if (d1 || p > 0) {
        dest[j++] = c1;
      }
      dest[j++] = c2;
      p++;
    }
  }
}
