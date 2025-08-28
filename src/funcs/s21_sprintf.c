#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "s21_format_lib.h"

int s21_sprintf(char *str, const char *format, ...) {
  str[0] = '\0';
  char *chanks[MAX_CHANKS] = {0};
  char *subs[MAX_CHANKS] = {0};

  explode((char *)format, chanks, subs);

  va_list args;
  va_start(args, format);
  for (int i = 0; i < MAX_CHANKS; i++) {
    if (subs[i]) {
      FormatVal fval;
      FormatVal *pfval = &fval;
      parse_format(subs[i], pfval);
      Variant value;
      value.type = get_argument_type(pfval);
      switch (value.type) {
        case char_val:
          value.data.c = va_arg(args, int);
          break;
        case int_val:
          value.data.i = va_arg(args, int);
          break;
        case short_val:
          value.data.si = va_arg(args, int);
          break;
        case long_val:
          value.data.li = va_arg(args, long);
          break;
        case unsigned_val:
          value.data.u = va_arg(args, unsigned);
          break;
        case unsigned_short_val:
          value.data.su = va_arg(args, unsigned);
          break;
        case unsigned_long_val:
          value.data.lu = va_arg(args, unsigned long);
          break;
        case double_val:
          value.data.d = va_arg(args, double);
          break;
        case long_double_val:
          value.data.ld = va_arg(args, long double);
          break;
        case str_val:
          value.data.pc = va_arg(args, char *);
          break;
        case ptr_val:
        case addr_val:
          value.data.pv = va_arg(args, void *);
          break;
        default:
          break;
      };
      if (value.type != undefined_val && value.type != addr_val) {
        int size = value.type == str_val ? 2048 : 50;
        subs[i] = enlarge_string(subs[i], size);
        format_value(subs[i], pfval, value);
      }
      if (value.type == addr_val) {
        int len = calc_len(chanks, subs, i);
        *((int *)value.data.pv) = len;
        subs[i][0] = 0;
      }
      if (pfval->specifier == '%') {
        subs[i][0] = '%';
        subs[i][1] = 0;
      }
    }
  }
  va_end(args);

  int len = implode(str, chanks, subs);

  for (int i = 0; i < MAX_CHANKS; i++) {
    if (chanks[i]) free(chanks[i]);
    if (subs[i]) free(subs[i]);
  }

  return len;
}
