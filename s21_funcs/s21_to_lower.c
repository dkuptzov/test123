#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *copy = s21_NULL;

  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);

    copy = (char *)malloc(sizeof(char) * (len + 1));

    if (copy) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] >= 65 && str[i] <= 90) {
          copy[i] = str[i] + 32;
        } else {
          copy[i] = str[i];
        }
      }
      copy[len] = '\0';
    }
  }
  return (void *)copy;
}
