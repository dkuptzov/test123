#include "s21_string.h"
#include "s21_tests.h"

START_TEST(basic) {
  char str1[] = "word1,word2,word3";
  char str2[] = "word1,word2,word3";
  char *delim = ",";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);
  ck_assert_str_eq(token1, token2);

  while (token1 != s21_NULL) {
    token1 = s21_strtok(s21_NULL, delim);
    token2 = strtok(NULL, delim);
    ck_assert_pstr_eq(token1, token2);
  }
}
END_TEST

START_TEST(few_consecutive_delimiters) {
  char str1[] = "one++two+++three";
  char str2[] = "one++two+++three";
  char *delim = "+";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(NULL, delim);
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(no_delimiters) {
  char str1[] = "nothing";
  char str2[] = "nothing";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(null_after_end) {
  char str1[] = "a";
  s21_strtok(str1, "a");
  char *token1 = s21_strtok(NULL, "a");
  ck_assert_ptr_null(token1);
}
END_TEST

Suite *suite_strtok(void) {
  Suite *s = suite_create("s21_strtok");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, basic);
  tcase_add_test(tc, few_consecutive_delimiters);
  tcase_add_test(tc, no_delimiters);
  tcase_add_test(tc, null_after_end);

  suite_add_tcase(s, tc);
  return s;
}