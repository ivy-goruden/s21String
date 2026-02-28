#include "s21_strerror.h"

#include "../s21_string.h"
#include "convert.h"

#if defined __APPLE__ && defined __MACH__
ERROR_MESSAGES_MAC
#elif defined __linux__
ERROR_MESSAGES_LINUX
#else
#error "Unsupported OS"
#endif

static char errortext[200] = "";

char *s21_strerror(int errnum) {
  int size = sizeof(s21_errors) / sizeof(s21_errors[0]);
  if (errnum >= 0 && errnum <= size) {
    s21_strncpy(errortext, s21_errors[errnum], s21_strlen(s21_errors[errnum]));
  } else {
    char buffer[20];
    int_to_str(errnum, buffer);
    s21_strncpy(errortext, unknown, s21_strlen(unknown));
    s21_strncat(errortext, buffer, s21_strlen(buffer));
  }
  return errortext;
}
