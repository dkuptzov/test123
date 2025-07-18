#include "s21_string.h"

int s21_isdelim(char ch, const char *delim);

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = s21_NULL;
  char *token_start = s21_NULL;
  int found = 0;

  if (str != s21_NULL) {
    next_token = str;
  }

  if (next_token != s21_NULL && *next_token != '\0') {
    while (*next_token != '\0' && s21_isdelim(*next_token, delim)) {
      next_token++;
    }

    if (*next_token != '\0') {
      token_start = next_token;

      found = 1;
      while (*next_token != '\0' && !s21_isdelim(*next_token, delim)) {
        next_token++;
      }

      if (*next_token != '\0') {
        *next_token = '\0';
        next_token++;
      } else {
        next_token = s21_NULL;
      }
    }
  }
  return found ? token_start : s21_NULL;
}

int s21_isdelim(char ch, const char *delim) {
  int result = 0;

  while (*delim != '\0' && result != 1) {
    if (ch == *delim) {
      result = 1;
    } else {
      delim++;
    }
  }
  return result;
}