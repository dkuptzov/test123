#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;

  if (str1 && str2) {
    for (const char *current_pos = str1; *current_pos != '\0' && !result;
         current_pos++) {
      for (const char *search_char = str2; *search_char != '\0' && !result;
           search_char++) {
        if (*current_pos == *search_char) {
          result = (char *)current_pos;
        }
      }
    }
  }
  return result;
}