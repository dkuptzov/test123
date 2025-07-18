#include "s21_sscanf_h.h"

int parse_d(const char **p, void *val, struct Prototip proto) {
  if (proto.zvezda) {
    while (isdigit(**p)) (*p)++;
    return 1;
  }
  if (proto.len == 'h') {
    *(short int *)val = 0;
  } else if (proto.len == 'l') {
    *(long int *)val = 0;
  } else {
    *(int *)val = 0;
  }
  int sign = 1;
  int max = proto.width;
  while (isspace(**p)) (*p)++;
  if (**p == '-') {
    if (max > 0) max -= 1;
    sign = -1;
    (*p)++;
  } else if (**p == '+') {
    if (max > 0) max -= 1;
    (*p)++;
  }
  if (!(isdigit(**p))) return 0;
  int count = 0;
  if (!isdigit(**p) || (max != 0 && count >= max))
    return (*p)[0] == '\0' ? -1 : 0;
  while (isdigit(**p) && (max == 0 || count < max)) {  // max = proto.width
    if (proto.len == 'h') {
      if (*(short int *)val > (SHRT_MAX - (**p - '0')) / 10) {
        return 1;
      }
      *(short int *)val = *(short int *)val * 10 + (**p - '0');
    } else if (proto.len == 'l') {
      if (*(long int *)val > (LONG_MAX - (**p - '0')) / 10) {
        return 1;
      }
      *(long int *)val = *(long int *)val * 10 + (**p - '0');
    } else {
      if (*(int *)val > (INT_MAX - (**p - '0')) / 10) {
        return 1;
      }
      *(int *)val = *(int *)val * 10 + (**p - '0');
    }
    (*p)++;
    count++;
  }
  if (proto.len == 'h') {
    *(short int *)val *= sign;
  } else if (proto.len == 'l') {
    *(long int *)val *= sign;
  } else {
    *(int *)val *= sign;
  }
  return 1;
}

int parse_c(const char **p, void *val, struct Prototip proto) {
  int count = proto.width ? proto.width : 1;
  if (proto.zvezda) {
    for (int i = 0; i < count && **p; ++i, ++(*p)) {
    }
    return 1;
  }
  char *out = (char *)val;
  for (int i = 0; i < count && **p; ++i, ++(*p)) {
    out[i] = **p;
  }
  return 1;
}

int parse_i(const char **p, void *val, struct Prototip proto) {
  const char *s = *p;
  int sign = 1;
  int base = 10;
  int width = proto.width;
  int count = 0;
  while (isspace(*s)) s++;
  if ((*s == '+' || *s == '-') && (!width || count < width)) {
    if (*s == '-') sign = -1;
    s++;
    count++;
  }
  const char *start_digits = s;

  if (*s == '0' && (!width || count < width)) {
    s++;
    count++;
    if ((*s == 'x' || *s == 'X') && (!width || count < width)) {
      s++;
      count++;
      base = 16;
    } else {
      base = 8;
      s = start_digits + 1;
      count = (int)(s - *p);
    }
  } else {
    base = 10;
  }
  long result = 0;
  int digit_found = 0;
  while (*s && (!width || count < width)) {
    int digit;
    if (*s >= '0' && *s <= '9') {
      digit = *s - '0';
    } else if (*s >= 'a' && *s <= 'f') {
      digit = *s - 'a' + 10;
    } else if (*s >= 'A' && *s <= 'F') {
      digit = *s - 'A' + 10;
    } else {
      break;
    }
    if (digit >= base) break;
    result = result * base + digit;
    digit_found = 1;
    s++;
    count++;
  }
  if (!digit_found) return 0;
  result *= sign;
  if (proto.zvezda) {
    *p = s;
    return 1;
  }
  if (proto.len == 'h') {
    *(short *)val = (short)result;
  } else if (proto.len == 'l') {
    *(long *)val = result;
  } else {
    *(int *)val = (int)result;
  }
  *p = s;
  return 1;
}

int parse_feEgG(const char **p, void *val, struct Prototip proto) {
  while (isspace(**p)) (*p)++;
  const char *s = *p;
  int width = proto.width;
  int read = 0;
  int sign = 1;
  if ((*s == '+' || *s == '-') && (!width || read < width)) {
    if (*s == '-') sign = -1;
    s++;
    read++;
  }
  const char *start_digits = s;
  double int_part = 0.0;
  while (isdigit(*s) && (!width || read < width)) {
    int_part = int_part * 10 + (*s - '0');
    s++;
    read++;
  }
  double frac_part = 0.0;
  double frac_div = 1.0;
  if (*s == '.' && (!width || read < width)) {
    s++;
    read++;
    while (isdigit(*s) && (!width || read < width)) {
      frac_part = frac_part * 10 + (*s - '0');
      frac_div *= 10.0;
      s++;
      read++;
    }
  }
  if (s == start_digits) return 0;
  double number = int_part + frac_part / frac_div;
  int exp_sign = 1;
  int exponent = 0;
  if ((*s == 'e' || *s == 'E') && (!width || read < width)) {
    s++;
    read++;
    if ((*s == '+' || *s == '-') && (!width || read < width)) {
      if (*s == '-') exp_sign = -1;
      s++;
      read++;
    }
    while (isdigit(*s) && (!width || read < width)) {
      exponent = exponent * 10 + (*s - '0');
      s++;
      read++;
    }
    int total_exp = exp_sign * exponent;
    if (total_exp > 0) {
      while (total_exp--) number *= 10.0;
    } else {
      while (total_exp++) number /= 10.0;
    }
  }
  number *= sign;
  if (read == 0) return 0;
  if (proto.zvezda) {
    *p = s;
    return 1;
  }
  if (proto.len == 'l') {
    *(double *)val = number;
  } else if (proto.len == 'L') {
    *(long double *)val = (long double)number;
  } else {
    *(float *)val = (float)number;
  }
  *p = s;
  return 1;
}

int parse_u(const char **p, void *val, struct Prototip proto) {
  while (isspace(**p)) (*p)++;
  if (proto.zvezda) {
    int count = 0;
    while (isdigit(**p) && (proto.width == 0 || count < proto.width)) {
      (*p)++;
      count++;
    }
    return 1;
  }
  unsigned long num = 0;
  int count = 0;
  while (isdigit(**p) && (proto.width == 0 || count < proto.width)) {
    int digit = **p - '0';
    if (num > (ULONG_MAX - digit) / 10) {
      break;
    }
    num = num * 10 + digit;
    (*p)++;
    count++;
  }
  if (count == 0) return 0;
  if (proto.len == 'h') {
    *(unsigned short *)val = (unsigned short)num;
  } else if (proto.len == 'l') {
    *(unsigned long *)val = num;
  } else {
    *(unsigned int *)val = (unsigned int)num;
  }
  return 1;
}

int parse_o(const char **p, void *val, struct Prototip proto) {
  const char *s = *p;
  int width = proto.width;
  while (isspace(*s)) s++;
  unsigned long result = 0;
  int read = 0;
  int valid = 0;
  while (*s >= '0' && *s <= '7' && (!width || read < width)) {
    result = result * 8 + (*s - '0');
    s++;
    read++;
    valid = 1;
  }
  if (!valid) return 0;
  if (!proto.zvezda && val) {
    if (proto.len == 'h') {
      *(unsigned short *)val = (unsigned short)result;
    } else if (proto.len == 'l') {
      *(unsigned long *)val = result;
    } else {
      *(unsigned int *)val = (unsigned int)result;
    }
  }
  *p = s;
  return 1;
}

int parse_x(const char **p, void *val, struct Prototip proto) {
  const char *s = *p;
  int width = proto.width;
  while (isspace(*s)) s++;
  if (*s == '0' && (s[1] == 'x' || s[1] == 'X') && (!width || width >= 2)) {
    s += 2;
    if (width) width -= 2;
  }
  unsigned long result = 0;
  int read = 0;
  int valid = 0;
  while (isxdigit(*s) && (!width || read < width)) {
    char ch = *s;
    int digit = 0;
    if (ch >= '0' && ch <= '9')
      digit = ch - '0';
    else if (ch >= 'a' && ch <= 'f')
      digit = 10 + (ch - 'a');
    else if (ch >= 'A' && ch <= 'F')
      digit = 10 + (ch - 'A');
    result = result * 16 + digit;
    s++;
    read++;
    valid = 1;
  }
  if (!valid) return 0;
  if (!proto.zvezda && val) {
    if (proto.len == 'h') {
      *(unsigned short *)val = (unsigned short)result;
    } else if (proto.len == 'l') {
      *(unsigned long *)val = result;
    } else {
      *(unsigned int *)val = (unsigned int)result;
    }
  }
  *p = s;
  return 1;
}

int parse_s(const char **p, void *val, struct Prototip proto) {
  const char *s = *p;
  char *out = (char *)val;
  while (isspace(*s)) s++;
  if (!proto.zvezda && out == (void *)0) return 0;
  int i = 0;
  while (*s && !isspace(*s)) {
    if (proto.width && i >= proto.width) break;
    if (!proto.zvezda) out[i] = *s;
    i++;
    s++;
  }
  if (i == 0) return 0;
  if (!proto.zvezda) out[i] = '\0';
  *p = s;
  return 1;
}

int parse_p(const char **p, void *val, struct Prototip proto) {
  const char *s = *p;
  while (isspace(*s)) s++;
  if (s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) {
    return 0;
  }
  s += 2;
  int width = proto.width;
  int read = 0;
  int valid = 0;
  uintptr_t result = 0;
  while (isxdigit(*s) && (!width || read < width)) {
    char ch = *s;
    int digit = 0;
    if (ch >= '0' && ch <= '9')
      digit = ch - '0';
    else if (ch >= 'a' && ch <= 'f')
      digit = 10 + (ch - 'a');
    else if (ch >= 'A' && ch <= 'F')
      digit = 10 + (ch - 'A');
    result = result * 16 + digit;
    s++;
    read++;
    valid = 1;
  }
  if (!valid) return 0;
  if (!proto.zvezda && val) {
    void **out = (void **)val;
    *out = (void *)(uintptr_t)result;
  }
  *p = s;
  return 1;
}

int parse_n(const char *start, const char *p, void *val) {
  if (!val) return 1;
  int len = p - start;
  *(int *)val = len;
  return 1;
}

int s21_sscanf(const char *str, const char *fmt, ...) {
  if (str == NULL || *str == '\0') return EOF;
  va_list args;
  va_start(args, fmt);
  const char *start = str;
  const char *p = str;
  int count = 0;
  while (*fmt) {
    while (isspace(*fmt)) fmt++;
    if (!(fmt[0] == '%' && fmt[1] == 'c')) {
      while (isspace(*p)) p++;
    }
    if (*fmt == '%') {
      fmt++;
      struct Prototip proto = {0};
      if (*fmt == '*') {
        proto.zvezda = 1;
        fmt++;
      }
      while (isdigit(*fmt)) {
        proto.width = proto.width * 10 + (*fmt - '0');
        fmt++;
      }
      if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
        proto.len = *fmt;
        fmt++;
      }
      if (*fmt == 'd') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          if (proto.len == 'h') {
            ptr = va_arg(args, short *);
          } else if (proto.len == 'l') {
            ptr = va_arg(args, long *);
          } else {
            ptr = va_arg(args, int *);
          }
        }
        int parse_result = parse_d(&p, ptr, proto);
        if (parse_result <= 0) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'i') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          if (proto.len == 'h') {
            ptr = va_arg(args, short *);
          } else if (proto.len == 'l') {
            ptr = va_arg(args, long *);
          } else {
            ptr = va_arg(args, int *);
          }
        }
        if (!parse_i(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'f' || *fmt == 'e' || *fmt == 'g' || *fmt == 'E' ||
                 *fmt == 'G') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          if (proto.len == 'L')
            ptr = va_arg(args, long double *);
          else if (proto.len == 'l')
            ptr = va_arg(args, double *);
          else
            ptr = va_arg(args, float *);
        }
        if (!parse_feEgG(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'u') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          if (proto.len == 'h') {
            ptr = va_arg(args, unsigned short *);
          } else if (proto.len == 'l') {
            ptr = va_arg(args, unsigned long *);
          } else {
            ptr = va_arg(args, unsigned int *);
          }
        }
        if (!parse_u(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'o') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          if (proto.len == 'h') {
            ptr = va_arg(args, unsigned short *);
          } else if (proto.len == 'l') {
            ptr = va_arg(args, unsigned long *);
          } else {
            ptr = va_arg(args, unsigned int *);
          }
        }
        if (!parse_o(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'x' || *fmt == 'X') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          if (proto.len == 'h') {
            ptr = va_arg(args, unsigned short *);
          } else if (proto.len == 'l') {
            ptr = va_arg(args, unsigned long *);
          } else {
            ptr = va_arg(args, unsigned int *);
          }
        }
        if (!parse_x(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 's') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          ptr = va_arg(args, char *);
        }
        if (!parse_s(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'c') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          ptr = va_arg(args, char *);
        }
        if (!parse_c(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'p') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          ptr = va_arg(args, void **);
        }
        if (!parse_p(&p, ptr, proto)) {
          va_end(args);
          return count;
        }
        if (!proto.zvezda) count++;
        fmt++;
      } else if (*fmt == 'n') {
        void *ptr = (void *)0;
        if (!proto.zvezda) {
          ptr = va_arg(args, int *);
        }
        if (!parse_n(start, p, ptr)) {
          va_end(args);
          return count;
        }
        fmt++;
      } else if (*fmt == '%') {
        if (*p != '%') {
          va_end(args);
          return count;
        }
        fmt++;
        p++;
      } else {
        break;
      }
    } else {
      if (*fmt != *p) break;
      fmt++;
      p++;
    }
  }
  va_end(args);
  return count;
}