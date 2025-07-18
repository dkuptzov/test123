#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src && trim_chars) {
    int start = 0;
    int end = s21_strlen(src);

    while (src[start] && s21_strchr(trim_chars, src[start])) {
      start++;
    }

    while (end > start && s21_strchr(trim_chars, src[end - 1])) {
      end--;
    }

    result = (char *)malloc(end - start + 1);

    if (result) {
      int length_result = end - start;
      s21_strncpy(result, src + start, length_result);
      result[length_result] = '\0';
    }
  }
  return (void *)result;
}