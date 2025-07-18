#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_sscanf_h.h"

START_TEST(test_s21_sscanf_empty) {
  int a = 0, b = 0;
  int res1 = s21_sscanf("", "%d", &a);
  int res2 = sscanf("", "%d", &b);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_parse_d_invalid_alpha) {
  int a = 123;
  int res1 = s21_sscanf("abc", "%d", &a);
  int res2 = sscanf("abc", "%d", &a);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_parse_d_with_asterisk) {
  int r1 = s21_sscanf("123", "%*d");
  int r2 = sscanf("123", "%*d");
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_d_only_sign) {
  int a = 123;
  int res1 = s21_sscanf("-", "%d", &a);
  int res2 = sscanf("-", "%d", &a);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sscanf_d_negative) {
  int a, b;
  int res1 = s21_sscanf("-456", "%d", &a);
  int res2 = sscanf("-456", "%d", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_d_invalid) {
  int a = 123, b = 123;
  int r1 = s21_sscanf("abc", "%d", &a);
  int r2 = sscanf("abc", "%d", &b);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_d_zero) {
  int a = -1, b = -1;
  int r1 = s21_sscanf("0", "%d", &a);
  int r2 = sscanf("0", "%d", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_d_overflow) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("999999999999", "%d", &a);
  int r2 = sscanf("999999999999", "%d", &b);
  ck_assert_int_eq(r1, r2);
  a = 0;
  b = 0;
  r1 = s21_sscanf("21474836470", "%d", &a);
  r2 = sscanf("21474836470", "%d", &b);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sscanf_i_variants) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("0123", "%i", &a);
  int r2 = sscanf("0123", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
  s21_sscanf("0x10", "%i", &a);
  sscanf("0x10", "%i", &b);
  ck_assert_int_eq(a, b);
  s21_sscanf("010", "%i", &a);
  sscanf("010", "%i", &b);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_d_extra_chars) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("123abc", "%d", &a);
  int r2 = sscanf("123abc", "%d", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_d_variants) {
  int a = 0, b = 0;
  s21_sscanf("  42", "%d", &a);
  sscanf("  42", "%d", &b);
  ck_assert_int_eq(a, b);
  s21_sscanf("-213", "%2d", &a);
  sscanf("-213", "%2d", &b);
  ck_assert_int_eq(a, b);
  s21_sscanf("+213", "%2d", &a);
  sscanf("+213", "%2d", &b);
  ck_assert_int_eq(a, b);
  s21_sscanf("213.4", "%4d", &a);
  sscanf("213.4", "%4d", &b);
  ck_assert_int_eq(a, b);
  short sa = 0, sb = 0;
  s21_sscanf("32767", "%hd", &sa);
  sscanf("32767", "%hd", &sb);
  ck_assert_int_eq(sa, sb);
}
END_TEST

START_TEST(test_parse_c_basic) {
  char a = 0, b = 0;
  int r1 = s21_sscanf("X", "%c", &a);
  int r2 = sscanf("X", "%c", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_c_space_char) {
  char a = 0, b = 0;
  int r1 = s21_sscanf(" ", "%c", &a);
  int r2 = sscanf(" ", "%c", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_c_multiple_chars_with_width) {
  char a[4] = {0}, b[4] = {0};
  int r1 = s21_sscanf("abc", "%3c", a);
  int r2 = sscanf("abc", "%3c", b);
  ck_assert_int_eq(r1, r2);
  ck_assert_mem_eq(a, b, 3);
}
END_TEST

START_TEST(test_parse_c_star) {
  int r1 = s21_sscanf("X", "%*c");
  int r2 = sscanf("X", "%*c");
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_c_no_input) {
  char a = 'X';
  int r1 = s21_sscanf("", "%c", &a);
  int r2 = sscanf("", "%c", &a);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_c_with_whitespace_before) {
  char a = 0, b = 0;
  int r1 = s21_sscanf("  Z", "%c", &a);
  int r2 = sscanf("  Z", "%c", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_c) {
  char a = 0, b = 0;
  int res1 = s21_sscanf("Z", "%c", &a);
  int res2 = sscanf("Z", "%c", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_c_variants) {
  char a, b;
  s21_sscanf("x", "%c", &a);
  sscanf("x", "%c", &b);
  ck_assert_int_eq(a, b);
  char str1[4], str2[4];
  s21_sscanf("abcd", "%3c", str1);
  sscanf("abcd", "%3c", str2);
  ck_assert_int_eq(memcmp(str1, str2, 3), 0);
}
END_TEST

START_TEST(test_sscanf_c_normal) {
  char a = '0', b = '0';
  int r1 = s21_sscanf("0", "%c", &a);
  int r2 = sscanf("0", "%c", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_decimal) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("42", "%i", &a);
  int r2 = sscanf("42", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_hex) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("0x1A", "%i", &a);
  int r2 = sscanf("0x1A", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_octal) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("075", "%i", &a);
  int r2 = sscanf("075", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_invalid_input) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("abc", "%i", &a);
  int r2 = sscanf("abc", "%i", &b);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_i_only_sign) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("+", "%i", &a);
  int r2 = sscanf("+", "%i", &b);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_i_negative_hex) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("-0xF", "%i", &a);
  int r2 = sscanf("-0xF", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_with_width) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("123456", "%3i", &a);
  int r2 = sscanf("123456", "%3i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_star) {
  int r1 = s21_sscanf("42", "%*i");
  int r2 = sscanf("42", "%*i");
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_parse_i_short_h_modifier) {
  short a = 0, b = 0;
  int r1 = s21_sscanf("123", "%hi", &a);
  int r2 = sscanf("123", "%hi", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_long_l_modifier) {
  long a = 0, b = 0;
  int r1 = s21_sscanf("123456789", "%li", &a);
  int r2 = sscanf("123456789", "%li", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST
/*
START_TEST(test_parse_i_invalid_prefix_only) {
  int a = 123, b = 123;
  int r1 = s21_sscanf("0x", "%i", &a);
  int r2 = sscanf("0x", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST*/

START_TEST(test_parse_i_leading_spaces_and_sign) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("   -075", "%i", &a);
  int r2 = sscanf("   -075", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_with_width_hex_partial) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("0x12AB", "%3i", &a);
  int r2 = sscanf("0x12AB", "%3i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

/*START_TEST(test_parse_i_zero_with_plus) {
  int a = 1, b = 1;
  int r1 = s21_sscanf("+0", "%i", &a);
  int r2 = sscanf("+0", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST*/

START_TEST(test_parse_i_star_modifier_skip) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("100 200", "%*i %i", &a);
  int r2 = sscanf("100 200", "%*i %i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_parse_i_overflow) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("9999999999", "%i", &a);
  int r2 = sscanf("9999999999", "%i", &b);
  ck_assert_int_eq(r1, r2);
}
END_TEST

/*START_TEST(test_parse_i_octal_invalid_digits) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("089", "%i", &a);
  int r2 = sscanf("089", "%i", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST*/

START_TEST(test_s21_sscanf_u) {
  unsigned int a, b;
  int res1 = s21_sscanf("4294967295", "%u", &a);
  int res2 = sscanf("4294967295", "%u", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_d) {
  int a, b;
  int res1 = s21_sscanf("123", "%d", &a);
  int res2 = sscanf("123", "%d", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_i) {
  int a, b;
  int res1 = s21_sscanf("0x1A", "%i", &a);
  int res2 = sscanf("0x1A", "%i", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_i_octal) {
  int a, b;
  int res1 = s21_sscanf("075", "%i", &a);
  int res2 = sscanf("075", "%i", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_x) {
  unsigned int a, b;
  int res1 = s21_sscanf("0xFF", "%x", &a);
  int res2 = sscanf("0xFF", "%x", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_u_hex_octal) {
  unsigned int a = 0, b = 0;
  int r1 = s21_sscanf("0x1F", "%x", &a);
  int r2 = sscanf("0x1F", "%x", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_f_invalid_input) {
  float a = -1, b = -1;
  int r1 = s21_sscanf("abc", "%f", &a);
  int r2 = sscanf("abc", "%f", &b);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sscanf_f_scientific) {
  float a = 0.0f, b = 0.0f;
  int r1 = s21_sscanf("1.23e2", "%f", &a);
  int r2 = sscanf("1.23e2", "%f", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_float_eq_tol(a, b, 1e-5);
}
END_TEST

START_TEST(test_s21_sscanf_float_exp) {
  float a, b;
  int res1 = s21_sscanf("2.5e2", "%f", &a);
  int res2 = sscanf("2.5e2", "%f", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(test_sscanf_float_variants) {
  float a = 0, b = 0;
  s21_sscanf("3.14", "%f", &a);
  sscanf("3.14", "%f", &b);
  ck_assert_float_eq_tol(a, b, 1e-6);
  double da = 0, db = 0;
  s21_sscanf("1.2e3", "%le", &da);
  sscanf("1.2e3", "%le", &db);
  ck_assert_double_eq_tol(da, db, 1e-6);
}
END_TEST

START_TEST(test_s21_sscanf_f_width) {
  float a, b;
  int res1 = s21_sscanf("3.1415926", "%4f", &a);
  int res2 = sscanf("3.1415926", "%4f", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(test_s21_sscanf_p) {
  void *a = NULL, *b = NULL;
  s21_sscanf("0x7ffee7e3c2f8", "%p", &a);
  sscanf("0x7ffee7e3c2f8", "%p", &b);
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_p) {
  void *a = NULL, *b = NULL;
  int r1 = s21_sscanf("0x1234", "%p", &a);
  int r2 = sscanf("0x1234", "%p", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_s) {
  char str1[20] = {0}, str2[20] = {0};
  int res1 = s21_sscanf("hello world", "%s", str1);
  int res2 = sscanf("hello world", "%s", str2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sscanf_s_width) {
  char a[10] = "", b[10] = "";
  int r1 = s21_sscanf("_x_x_x", "%3s", a);
  int r2 = sscanf("_x_x_x", "%3s", b);
  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_s_variants) {
  char s1[20] = {'\0'}, s2[20] = {'\0'};
  s21_sscanf("hello world", "%s", s1);
  sscanf("hello world", "%s", s2);
  ck_assert_str_eq(s1, s2);
  s21_sscanf("Good morning", "%5s", s1);
  sscanf("Good morning", "%5s", s2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_s21_sscanf_n) {
  int a = 0, b = 0, n1 = 0, n2 = 0;
  const char *str = "12345";
  s21_sscanf(str, "%d%n", &a, &n1);
  sscanf(str, "%d%n", &b, &n2);
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_s21_sscanf_o) {
  unsigned int a, b;
  int res1 = s21_sscanf("77", "%o", &a);
  int res2 = sscanf("77", "%o", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_unsigned_variants) {
  unsigned int a = 0, b = 0;
  s21_sscanf("4294967295", "%u", &a);
  sscanf("4294967295", "%u", &b);
  ck_assert_int_eq(a, b);
  s21_sscanf("0755", "%o", &a);
  sscanf("0755", "%o", &b);
  ck_assert_int_eq(a, b);
  s21_sscanf("0xFF", "%x", &a);
  sscanf("0xFF", "%x", &b);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_s21_sscanf_nString) {
  char a[64] = {'\0'};
  char b[64] = {'\0'};
  int n1 = 0, n2 = 0;
  const char *str = "string's";
  s21_sscanf(str, "%s%n", a, &n1);
  sscanf(str, "%s%n", b, &n2);
  ck_assert_int_eq(*a, *b);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_n_position) {
  int n1 = 0, n2 = 0, a1 = 0, a2 = 0;
  int r1 = s21_sscanf("42abc", "%d%n", &a1, &n1);
  int r2 = sscanf("42abc", "%d%n", &a2, &n2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  void *p1 = NULL, *p2 = NULL;
  s21_sscanf("0x1234ABCD", "%p", &p1);
  sscanf("0x1234ABCD", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(test_sscanf_percent_literal) {
  int r1 = s21_sscanf("%", "%%");
  int r2 = sscanf("%", "%%");
  ck_assert_int_eq(r1, r2);
  int x1 = s21_sscanf("%%", "%%");
  int x2 = sscanf("%%", "%%");
  ck_assert_int_eq(x1, x2);
}
END_TEST

START_TEST(test_s21_sscanf_percent) {
  int res1 = s21_sscanf("%", "%%");
  int res2 = sscanf("%", "%%");
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_ignore_specifier) {
  int a = 0, b = 0;
  int r1 = s21_sscanf("123 456", "%*d %d", &a);
  int r2 = sscanf("123 456", "%*d %d", &b);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a, b);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_sscanf_empty);
  tcase_add_test(tc, test_s21_sscanf_d);
  tcase_add_test(tc, test_s21_sscanf_i);
  tcase_add_test(tc, test_s21_sscanf_f_width);
  tcase_add_test(tc, test_s21_sscanf_s);
  tcase_add_test(tc, test_s21_sscanf_n);
  tcase_add_test(tc, test_s21_sscanf_nString);
  tcase_add_test(tc, test_s21_sscanf_d_negative);
  tcase_add_test(tc, test_s21_sscanf_i_octal);
  tcase_add_test(tc, test_s21_sscanf_float_exp);
  tcase_add_test(tc, test_s21_sscanf_u);
  tcase_add_test(tc, test_s21_sscanf_o);
  tcase_add_test(tc, test_s21_sscanf_x);
  tcase_add_test(tc, test_s21_sscanf_c);
  tcase_add_test(tc, test_s21_sscanf_p);
  tcase_add_test(tc, test_s21_sscanf_percent);
  tcase_add_test(tc, test_sscanf_d_variants);
  tcase_add_test(tc, test_sscanf_i_variants);
  tcase_add_test(tc, test_sscanf_float_variants);
  tcase_add_test(tc, test_sscanf_s_variants);
  tcase_add_test(tc, test_sscanf_c_variants);
  tcase_add_test(tc, test_sscanf_unsigned_variants);
  tcase_add_test(tc, test_sscanf_pointer);
  tcase_add_test(tc, test_sscanf_percent_literal);
  tcase_add_test(tc, test_sscanf_ignore_specifier);
  tcase_add_test(tc, test_sscanf_n_position);
  tcase_add_test(tc, test_sscanf_s_width);
  tcase_add_test(tc, test_sscanf_p);
  tcase_add_test(tc, test_sscanf_c_normal);
  tcase_add_test(tc, test_sscanf_f_scientific);
  tcase_add_test(tc, test_sscanf_f_invalid_input);
  tcase_add_test(tc, test_sscanf_u_hex_octal);
  tcase_add_test(tc, test_sscanf_i_variants);
  tcase_add_test(tc, test_sscanf_d_overflow);
  tcase_add_test(tc, test_sscanf_d_invalid);
  tcase_add_test(tc, test_parse_d_invalid_alpha);
  tcase_add_test(tc, test_parse_d_only_sign);
  tcase_add_test(tc, test_parse_d_extra_chars);
  tcase_add_test(tc, test_parse_d_with_asterisk);
  tcase_add_test(tc, test_parse_d_zero);
  tcase_add_test(tc, test_parse_c_basic);
  tcase_add_test(tc, test_parse_c_space_char);
  tcase_add_test(tc, test_parse_c_multiple_chars_with_width);
  tcase_add_test(tc, test_parse_c_star);
  tcase_add_test(tc, test_parse_c_no_input);
  tcase_add_test(tc, test_parse_c_with_whitespace_before);
  tcase_add_test(tc, test_parse_i_decimal);
  tcase_add_test(tc, test_parse_i_hex);
  tcase_add_test(tc, test_parse_i_octal);
  tcase_add_test(tc, test_parse_i_invalid_input);
  tcase_add_test(tc, test_parse_i_only_sign);
  tcase_add_test(tc, test_parse_i_negative_hex);
  tcase_add_test(tc, test_parse_i_with_width);
  tcase_add_test(tc, test_parse_i_star);
  tcase_add_test(tc, test_parse_i_short_h_modifier);
  tcase_add_test(tc, test_parse_i_long_l_modifier);
  // tcase_add_test(tc, test_parse_i_invalid_prefix_only);
  tcase_add_test(tc, test_parse_i_leading_spaces_and_sign);
  tcase_add_test(tc, test_parse_i_with_width_hex_partial);
  // tcase_add_test(tc, test_parse_i_zero_with_plus);
  tcase_add_test(tc, test_parse_i_star_modifier_skip);
  tcase_add_test(tc, test_parse_i_overflow);
  // tcase_add_test(tc, test_parse_i_octal_invalid_digits);

  suite_add_tcase(s, tc);
  return s;
}
