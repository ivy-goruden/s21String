#ifndef s21_format_lib_h
#define s21_format_lib_h

#include "../s21_string.h"

#define MAX_CHANKS 100
#define REGEX \
  "%[-+#0 ]*([0-9]+|\\*)?(\\.([0-9]+|\\*)?)?(h|l|L)?[cdieEfgGosuxXpn%]"

typedef struct {
  char tail[10];
  char flags[255];
  int plus;
  int minus;
  int sharp;
  int zero;
  int space;
  int w_ast;
  int width;
  int p_ast;
  int precision;
  char length;
  char specifier;
} FormatVal;

typedef enum {
  char_val,
  int_val,
  long_val,
  short_val,
  unsigned_val,
  unsigned_long_val,
  unsigned_short_val,
  float_val,
  double_val,
  long_double_val,
  str_val,
  ptr_val,
  addr_val,
  undefined_val
} ArgumentType;

typedef struct {
  ArgumentType type;
  union {
    char c;
    int i;
    long li;
    short si;
    unsigned u;
    unsigned long lu;
    unsigned short su;
    float f;
    double d;
    double ld;
    char *pc;
    void *pv;
  } data;

} Variant;

int max(int a, int b);
int min(int a, int b);
char *enlarge_string(char *str, s21_size_t new_size);
void extract(char *src, int len, char **chanks, int *index);
int implode(char *dest, char **chanks, char **subs);
void explode(char *format, char **chanks, char **subs);
ArgumentType get_argument_type(FormatVal *pfval);
int seek_substring(char *format, int *start, int *end);
void parse_format(char *format, FormatVal *fval);
void format_value(char *dest, FormatVal *pfval, Variant value);
void format_c(char *dest, FormatVal *pfval, char value);
void format_i(char *dest, FormatVal *pfval, long value);
void format_s(char *dest, FormatVal *pfval, char *value);
void format_g(char *dest, FormatVal *pfval, long double value);
void format_e(char *dest, FormatVal *pfval, long double value);
void format_d(char *dest, FormatVal *pfval, long double value, int keepzeros);
void format_p(char *dest, FormatVal *pfval, void *value);
void format_u(char *dest, FormatVal *pfval, unsigned long value);
void format_x(char *dest, FormatVal *pfval, unsigned long value,
              unsigned char upper);
void format_o(char *dest, FormatVal *pfval, unsigned long value);
int calc_len(char **chanks, char **subs, int stop);

#endif  // s21_format_lib_h
