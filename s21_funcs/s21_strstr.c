#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  s21_size_t needle_len = s21_strlen(needle);
  s21_size_t haystack_len = s21_strlen(haystack);

  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    if (haystack_len >= needle_len) {
      haystack = s21_strchr(haystack, *needle);
      while (haystack != s21_NULL) {
        if (s21_strncmp(haystack, needle, needle_len) == 0) {
          result = (char *)haystack;
          break;
        }
        haystack = s21_strchr(haystack + 1, *needle);
      }
    }
  }
  return result;
}