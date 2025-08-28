#include "s21_format_lib.h"

#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "convert.h"

// %[флаги][ширина][.точность][длина]спецификатор
// %[flags][width][.precision][length]specifier

// % — обязательный символ начала спецификатора
// [flags] — опциональные флаги: -, +, (пробел), #, 0
// [width] — опциональная ширина поля (число или *)
// [.precision] — опциональная точность, начинается с точки и затем число или *
// [length] — опциональный модификатор длины: hh, h, l, ll, j, z, t, L
// specifier — обязательный символ спецификатора: d, i, u, f, F, e, E, g, G, x,
// X, o, s, c, p, n, %

// %                           # Начало спецификатора
// [-+#0 ]*                    # Опциональные флаги (0 или более)
// ([0-9]+|\*)?                # Опциональная ширина (число или *)
// (\.([0-9]+|\*))?            # Опциональная точность (точка + число или *)
// (hh|h|ll|l|j|z|t|L)?        # Опциональный модификатор длины
// [diufFeEgGxXoscpn%]         # Обязательный спецификатор

// наиболее полный шаблон
// %[-+#0 ]*([0-9]+|\*)?(\.([0-9]+|\*))?(hh|h|ll|l|j|z|t|L)?[diufFeEgGxXoscpn%]
// прототип формата достаточный для проекта
// %[-+#0 ]*([0-9]+|\*)?(\.([0-9]+|\*))?(h|l|L)?[cdieEfgGosuxXpn%]

int max(int a, int b) { return a > b ? a : b; }

int min(int a, int b) { return a < b ? a : b; }

long long power10(int n) {
  long long result = 1;
  for (int i = 0; i < n; i++) {
    result *= 10;
  }
  return result;
}

void parse_format(char *format, FormatVal *fval) {
  s21_size_t len = s21_strlen(format);
  fval->specifier = format[len - 1];
  fval->length = 0;
  fval->p_ast = 0;
  fval->precision = -1;
  fval->w_ast = 0;
  fval->width = -1;
  fval->plus = 0;
  fval->minus = 0;
  fval->sharp = 0;
  fval->zero = 0;
  fval->space = 0;
  *(fval->flags) = 0;
  *(fval->tail) = 0;
  char *plen = s21_strpbrk(format, "hlL");
  if (plen) {
    fval->length = *plen;
  }
  char *pdot = s21_strrchr(format, '.');
  if (pdot) {
    if (*(pdot + 1) == '*') {
      fval->p_ast = 1;
    } else {
      int i = 0;
      char *p = fval->length ? plen - 1 : format + len - 2;
      fval->precision = 0;
      while (p > pdot) {
        fval->precision += (*p - '0') * power10(i);
        i++;
        p--;
      }
    }
  }
  char *pwid = s21_strpbrk(format, "123456789*");
  if (pwid && (!pdot || pdot > pwid)) {
    if (*pwid == '*') {
      fval->w_ast = 1;
    } else {
      int i = 0;
      char *p = pwid;
      fval->width = 0;
      for (; *p >= '0' && *p <= '9'; p++)
        ;
      p--;
      while (p >= pwid) {
        fval->width += (*p - '0') * power10(i);
        i++;
        p--;
      }
    }
  } else {
    pwid = S21_NULL;
  }
  char *pflags = format + 1;
  int flen = s21_strcspn(pflags, ".123456789*hlLcdieEfgGosuxXpn%");
  if (flen) {
    fval->flags[flen] = 0;
    for (int i = 0; i < flen; i++) {
      fval->flags[i] = pflags[i];
    }
  } else {
    pflags = S21_NULL;
  }

  fval->minus = s21_strchr(fval->flags, '-') ? 1 : 0;
  fval->plus = s21_strchr(fval->flags, '+') ? 1 : 0;
  fval->sharp = s21_strchr(fval->flags, '#') ? 1 : 0;
  fval->zero = s21_strchr(fval->flags, '0') ? 1 : 0;
  fval->space = s21_strchr(fval->flags, 32) ? 1 : 0;
}

// return: regex error
int seek_substring(char *format, int *start, int *end) {
  int error;
  int reg_flags = REG_EXTENDED;
  const char *pattern = REGEX;

  regex_t regex;
  error = regcomp(&regex, pattern, reg_flags);
  if (error == 0) {
    regmatch_t match;
    error = regexec(&regex, format, 1, &match, 0);
    if (error == 0) {
      *start = match.rm_so;
      *end = match.rm_eo;
    }
  }
  regfree(&regex);

  return error;
}

char *enlarge_string(char *str, s21_size_t new_size) {
  if (s21_strlen(str) < new_size) {
    char *tmp = realloc(str, new_size * sizeof(char));
    if (!tmp) {
      printf("Ошибка выделения памяти: %s\n", "enlarge_string");
      return S21_NULL;
    }
    return tmp;
  }
  return str;
}

void extract(char *src, int len, char **strings, int *index) {
  if (len > 0) {
    char *p = malloc(sizeof(char) * len + 1);
    s21_strncpy(p, src, len);
    p[len] = 0;
    strings[*index] = p;
    (*index)++;
  }
}

int implode(char *dest, char **chanks, char **subs) {
  int j = 0;
  int len = 0;
  for (int i = 0; i < MAX_CHANKS; i++) {
    if (chanks[i]) {
      len = s21_strlen(chanks[i]);
      s21_strncpy(dest + j, chanks[i], len);
      j += len;
    }
    if (subs[i]) {
      len = s21_strlen(subs[i]);
      s21_strncpy(dest + j, subs[i], len);
      j += len;
    }
  }
  dest[j] = 0;
  return j;
}

int calc_len(char **chanks, char **subs, int stop) {
  int j = 0;
  for (int i = 0; i < stop; i++) {
    if (chanks[i]) {
      j += s21_strlen(chanks[i]);
    }
    if (subs[i]) {
      j += s21_strlen(subs[i]);
    }
  }
  return j;
}

void explode(char *format, char **chanks, char **subs) {
  int start = 0;
  int end = 0;
  int length = 0;
  char *substring = S21_NULL;
  char *p = (char *)format;
  int index = 0;
  while (1) {
    int error = seek_substring(p, &start, &end);
    if (error != 0) {
      break;
    }
    length = end - start;
    if (length == 0) {
      break;
    }
    substring = p + start;
    if (p != substring) {
      extract(p, substring - p, chanks, &index);
      extract(substring, length, subs, &index);
    } else {
      extract(substring, length, subs, &index);
    }
    p += end;
  }
  int format_len = s21_strlen(format);
  extract(p, format + format_len - p, chanks, &index);
}

ArgumentType get_argument_type(FormatVal *pfval) {
  switch (pfval->specifier) {
    case 'n':
      return addr_val;
    case 'c':
      return char_val;
    case 'i':
    case 'd':
      return pfval->length == 'l'
                 ? long_val
                 : (pfval->length == 'h' ? short_val : int_val);
    case 'o':
    case 'x':
    case 'X':
    case 'u':
      return pfval->length == 'l'
                 ? unsigned_long_val
                 : (pfval->length == 'h' ? unsigned_short_val : unsigned_val);
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'f':
      return pfval->length == 'L' ? long_double_val : double_val;
    case 's':
      return str_val;
    case 'p':
      return ptr_val;
  }
  return undefined_val;
}

void format_value(char *dest, FormatVal *pfval, Variant value) {
  if (pfval->specifier == 'c') {
    format_c(dest, pfval, value.data.c);
  } else if (s21_strchr("di", pfval->specifier) && pfval->length == 'h') {
    format_i(dest, pfval, value.data.si);
  } else if (s21_strchr("di", pfval->specifier) && pfval->length == 'l') {
    format_i(dest, pfval, value.data.li);
  } else if (s21_strchr("di", pfval->specifier)) {
    format_i(dest, pfval, value.data.i);
  } else if (pfval->specifier == 'f' && pfval->length == 'L') {
    format_d(dest, pfval, value.data.ld, 1);
  } else if (pfval->specifier == 'f') {
    format_d(dest, pfval, value.data.d, 1);
  } else if (s21_strchr("eE", pfval->specifier) && pfval->length == 'L') {
    format_e(dest, pfval, value.data.ld);
  } else if (s21_strchr("eE", pfval->specifier)) {
    format_e(dest, pfval, value.data.d);
  } else if (s21_strchr("gG", pfval->specifier) && pfval->length == 'L') {
    format_g(dest, pfval, value.data.ld);
  } else if (s21_strchr("gG", pfval->specifier)) {
    format_g(dest, pfval, value.data.d);
  } else if (pfval->specifier == 's') {
    format_s(dest, pfval, value.data.pc);
  } else if (pfval->specifier == 'p') {
    format_p(dest, pfval, value.data.pv);
  } else if (pfval->specifier == 'u' && pfval->length == 'h') {
    format_u(dest, pfval, value.data.su);
  } else if (pfval->specifier == 'u' && pfval->length == 'l') {
    format_u(dest, pfval, value.data.lu);
  } else if (pfval->specifier == 'u') {
    format_u(dest, pfval, value.data.u);
  } else if (s21_strchr("xX", pfval->specifier) && pfval->length == 'h') {
    format_x(dest, pfval, value.data.su, pfval->specifier == 'X' ? 1 : 0);
  } else if (s21_strchr("xX", pfval->specifier) && pfval->length == 'l') {
    format_x(dest, pfval, value.data.lu, pfval->specifier == 'X' ? 1 : 0);
  } else if (s21_strchr("xX", pfval->specifier)) {
    format_x(dest, pfval, value.data.u, pfval->specifier == 'X' ? 1 : 0);
  } else if (pfval->specifier == 'o' && pfval->length == 'h') {
    format_o(dest, pfval, value.data.su);
  } else if (pfval->specifier == 'o' && pfval->length == 'l') {
    format_o(dest, pfval, value.data.lu);
  } else if (pfval->specifier == 'o') {
    format_o(dest, pfval, value.data.u);
  }

  return;
}

void format_c(char *dest, FormatVal *pfval, char value) {
  if (pfval->specifier) {
    dest[0] = value;
    dest[1] = 0;
  }
}

void norm_float(int prec, long double value, long double *frac, int *exp) {
  // поиск степени 10
  char n = 0;
  int neg = value < 0 ? 1 : 0;
  long double v = neg ? -value : value;
  long vi = (long)v;
  if (vi == 0 && v != 0.0) {
    while (vi == 0) {
      v *= 10.0;
      n--;
      vi = (long)v;
    }
  } else if (vi >= 10) {
    while (vi >= 10) {
      v /= 10.0;
      n++;
      vi = (long)v;
    }
  }
  // проверка возможного переноса при конвертации числа v
  long double t = v;
  long dig = (long)t;
  int dc = (dig == 9 ? 1 : 0);
  for (int i = 0; i < prec; i++) {
    t = (t - dig) * 10.0;
    dig = (long)t;
    if (dig != 9) {
      dc = 0;
      break;
    }
  }
  if (dc) {
    v /= 10;
    n++;
  }
  *exp = n;
  *frac = v;
}

int digits10(long n) {
  if (n == 0) return 1;
  int count = 0;
  if (n < 0) n = -n;
  while (n > 0) {
    n /= 10;
    count++;
  }
  return count;
}

void format_g(char *dest, FormatVal *pfval, long double value) {
  int n;
  long double v;
  int prec = pfval->precision < 0 ? 6 : pfval->precision;
  norm_float(prec, value, &v, &n);

  if (v != 0.0 && n > 0 && (n < -4 || n >= prec)) {
    char str[5] = {0};
    str[0] = pfval->specifier == 'g' ? 'e' : 'E';
    s21_sprintf(str + 1, "%0+.2d", n);
    s21_strncpy(pfval->tail, str, s21_strlen(str) + 1);

    long int_part = (long)v;
    int digs = digits10(int_part);
    pfval->precision = prec > digs ? prec - digs : 0;
    format_d(dest, pfval, value < 0 ? -v : v, 0);
  } else {
    long int_part = (long)value;
    int digs = digits10(int_part);
    prec = pfval->precision < 0 ? 6 : pfval->precision;
    pfval->precision = prec > digs ? prec - digs : 0;
    format_d(dest, pfval, value, 0);
  }
}

void format_e(char *dest, FormatVal *pfval, long double value) {
  int n;
  long double v;
  int prec = pfval->precision < 0 ? 6 : pfval->precision;
  norm_float(prec, value, &v, &n);

  // хвост
  char str[5] = {0};
  str[0] = pfval->specifier;
  s21_sprintf(str + 1, "%0+.2d", n);
  s21_strncpy(pfval->tail, str, s21_strlen(str) + 1);
  format_d(dest, pfval, value < 0 ? -v : v, 1);
}

void format_d(char *dest, FormatVal *pfval, long double value, int keepzeros) {
  pfval->precision = pfval->precision < 0 ? 6 : pfval->precision;
  pfval->width = pfval->width < 0 ? 0 : pfval->width;

  // i_part_s - все число
  char i_part_s[50] = {0};
  // проверяем знак
  int neg = value < 0 ? 1 : 0;
  // число без знака
  value = neg ? -value : value;
  // целая часть
  long int_part = (long)value;

  // дробная часть
  long double float_part = value - (long double)int_part;
  char digs[50];
  for (int i = 0; i < pfval->precision; i++) {
    float_part = float_part * 10;
    digs[i] = (char)float_part;
    float_part = float_part - (char)float_part;
  }
  float_part += 0.5;
  int over = 0;
  if ((char)float_part == 1) {
    over = 1;
    for (int i = pfval->precision - 1; i >= 0; i--) {
      digs[i] += over;
      if (digs[i] == 10) {
        digs[i] = 0;
        over = 1;
      } else {
        over = 0;
        break;
      }
    }
  }
  int_part += over;

  // конвертируем целую часть
  int_to_str(int_part, i_part_s);
  int len_i = s21_strlen(i_part_s);

  // соединим целую и дробную часть
  if (pfval->precision != 0) {
    int k = len_i;
    i_part_s[k++] = '.';
    for (int i = 0; i < pfval->precision; i++) {
      i_part_s[k++] = digs[i] + '0';
    }
    // удалить конечные нули, для спецификатора gG
    if (!pfval->sharp && !keepzeros) {
      int len = s21_strlen(i_part_s);
      for (int i = len - 1; i_part_s[i] == '0' && i > len_i; i--) {
        i_part_s[i] = 0;
      }
      len = s21_strlen(i_part_s);
      i_part_s[len - 1] = i_part_s[len - 1] != '.' ? i_part_s[len - 1] : 0;
    }
  } else {
    if (pfval->sharp) {
      i_part_s[len_i] = '.';
    }
  }

  // добавим хвост
  s21_strncat(i_part_s, pfval->tail, s21_strlen(pfval->tail));

  // лидирующий символ, заполнение и выравнивание
  int i = 0;
  char *float_s = i_part_s;
  int len = s21_strlen(float_s);
  char l_ch = neg ? '-' : (pfval->plus ? '+' : (pfval->space ? 32 : 0));
  char fil_ch = pfval->minus ? 32 : (pfval->zero ? '0' : 32);
  int min_w = len + (l_ch ? 1 : 0);
  int fil_w = pfval->width - min_w;
  if (!pfval->minus) {
    if (!pfval->zero) {
      for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
        ;
      if (l_ch) dest[i++] = l_ch;
    } else {
      if (l_ch) dest[i++] = l_ch;
      for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
        ;
    }
    s21_strncpy(dest + i, float_s, len);
    i += len;
  } else {
    if (l_ch) dest[i++] = l_ch;
    s21_strncpy(dest + i, float_s, len);
    i += len;
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
  }
  dest[i] = 0;
}

void format_s(char *dest, FormatVal *pfval, char *value) {
  char *src = value;
  char null_text[] = "(null)";
  if (!value) {
    src = null_text;
  }
  int len = s21_strlen(src);
  int real_len = pfval->precision >= 0 ? min(pfval->precision, len) : len;
  int h = max(real_len, pfval->width);
  int w_fil = pfval->width > real_len ? pfval->width - real_len : 0;
  int i = 0;
  if (!pfval->minus) {
    for (int j = 0; j < w_fil; dest[i++] = 32, j++)
      ;
    for (int j = 0; j < h - w_fil; dest[i++] = src[j], j++)
      ;
  } else {
    for (int j = 0; j < h - w_fil; dest[i++] = src[j], j++)
      ;
    for (int j = 0; j < w_fil; dest[i++] = 32, j++)
      ;
  }
  dest[i] = 0;
}

void format_i(char *dest, FormatVal *pfval, long value) {
  // buffer - число
  char buffer[50] = {0};

  // проверяем знак
  int neg = value < 0 ? 1 : 0;

  // число без знака
  value = neg ? -value : value;

  // конвертируем
  int_to_str(value, buffer);

  // если точность ноль и число = 0 то делаем строку buffer пустой
  if (value == 0 && pfval->precision == 0) {
    buffer[0] = 0;
  }

  // лидирующий символ, заполнение и выравнивание
  int i = 0;
  int len = s21_strlen(buffer);
  char l_ch = neg ? '-' : (pfval->plus ? '+' : (pfval->space ? 32 : 0));
  char fil_ch = 32;
  int zero_w = pfval->precision > len ? pfval->precision - len : 0;
  if (pfval->precision < 0 && !pfval->minus && pfval->zero) {
    zero_w = pfval->width - len - (l_ch ? 1 : 0);
  }
  int real_len = zero_w + len;
  int min_w = real_len + (l_ch ? 1 : 0);
  int fil_w = pfval->width - min_w;

  if (!pfval->minus) {
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
    if (l_ch) dest[i++] = l_ch;
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, buffer, len);
    i += len;
  } else {
    if (l_ch) dest[i++] = l_ch;
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, buffer, len);
    i += len;
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
  }
  dest[i] = 0;
}

void format_u(char *dest, FormatVal *pfval, unsigned long value) {
  char buffer[20] = {0};
  to_dec(value, buffer);

  // если точность ноль и число = 0 то делаем строку buffer пустой
  if (value == 0 && pfval->precision == 0) {
    buffer[0] = 0;
  }

  // лидирующий символ, заполнение и выравнивание
  int i = 0;
  int len = s21_strlen(buffer);
  char fil_ch = 32;
  int zero_w = pfval->precision > len ? pfval->precision - len : 0;
  if (pfval->precision < 0 && !pfval->minus && pfval->zero) {
    zero_w = pfval->width - len;
  }
  int real_len = zero_w + len;
  int min_w = real_len;
  int fil_w = pfval->width - min_w;

  if (!pfval->minus) {
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, buffer, len);
    i += len;
  } else {
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, buffer, len);
    i += len;
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
  }
  dest[i] = 0;
}

void format_p(char *dest, FormatVal *pfval, void *value) {
  char str[20] = {0};
  if (!value) {
    s21_strncpy(str, "(nil)", 5);
    pfval->precision = -1;
    format_s(dest, pfval, str);
    return;
  } else {
    to_hex(str, (unsigned long long)value, 0);
  }

  int i = 0;
  int len = s21_strlen(str);
  char l_ch = (pfval->plus ? '+' : (pfval->space ? 32 : 0));
  char fil_ch = 32;
  int zero_w = pfval->precision > len ? pfval->precision - len : 0;
  if (pfval->precision < 0 && !pfval->minus && pfval->zero) {
    zero_w = pfval->width - len - (l_ch ? 1 : 0) - 2;
  }
  int real_len = zero_w + len;
  int min_w = real_len + (l_ch ? 1 : 0) + 2;
  int fil_w = pfval->width - min_w;

  if (!pfval->minus) {
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
    if (l_ch) dest[i++] = l_ch;
    dest[i++] = '0';
    dest[i++] = 'x';
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, str, len);
    i += len;
  } else {
    if (l_ch) dest[i++] = l_ch;
    dest[i++] = '0';
    dest[i++] = 'x';
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, str, len);
    i += len;
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
  }
  dest[i] = 0;
}

void format_x(char *dest, FormatVal *pfval, unsigned long value,
              unsigned char upper) {
  char str[20] = {0};
  to_hex(str, value, upper);

  int i = 0;
  int len = s21_strlen(str);
  char fil_ch = 32;
  int zero_w = pfval->precision > len ? pfval->precision - len : 0;
  if (pfval->precision < 0 && !pfval->minus && pfval->zero) {
    zero_w = pfval->width - len;
  }
  int real_len = zero_w + len;
  int fil_w = pfval->width - real_len;

  if (!pfval->minus) {
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, str, len);
    i += len;
  } else {
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, str, len);
    i += len;
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
  }
  dest[i] = 0;
}

void format_o(char *dest, FormatVal *pfval, unsigned long value) {
  char str[20] = {0};
  to_oct(value, str);

  int i = 0;
  int len = s21_strlen(str);
  char fil_ch = 32;
  int zero_w = pfval->precision > len ? pfval->precision - len : 0;
  if (pfval->precision < 0 && !pfval->minus && pfval->zero) {
    zero_w = pfval->width - len;
  }
  int real_len = zero_w + len;
  int fil_w = pfval->width - real_len;

  if (!pfval->minus) {
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, str, len);
    i += len;
  } else {
    for (int j = 0; j < zero_w; dest[i++] = '0', j++)
      ;
    s21_strncpy(dest + i, str, len);
    i += len;
    for (int j = 0; j < fil_w; dest[i++] = fil_ch, j++)
      ;
  }
  dest[i] = 0;
}
