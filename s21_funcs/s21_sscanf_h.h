#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

struct Prototip {
  int zvezda;
  int width;
  char len;
};

int parse_d(const char **p, void *val, struct Prototip proto);
int parse_c(const char **p, void *val, struct Prototip proto);
int parse_i(const char **p, void *val, struct Prototip proto);
int parse_feEgG(const char **p, void *val, struct Prototip proto);
int parse_u(const char **p, void *val, struct Prototip proto);
int parse_o(const char **p, void *val, struct Prototip proto);
int parse_x(const char **p, void *val, struct Prototip proto);
int parse_s(const char **p, void *val, struct Prototip proto);
int parse_p(const char **p, void *val, struct Prototip proto);
int parse_n(const char *start, const char *p, void *val);
int s21_sscanf(const char *str, const char *fmt, ...);

#endif