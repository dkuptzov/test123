#include "../s21_funcs/s21_string.h"
#include "s21_tests.h"

START_TEST(simple_insertion) {
  const char src[1024] = "Hello to my group!";
  const char str[1024] = "Test passed!";
  char *result = s21_insert(src, str, s21_strlen(src));
  ck_assert_str_eq(result, "Hello to my group!Test passed!");
  free(result);
}
END_TEST

START_TEST(simple_insert_with_space) {
  const char src[1024] = "Hello to my group!";
  const char str[1024] = " Test passed!";
  char *result = s21_insert(src, str, s21_strlen(src));
  ck_assert_str_eq(result, "Hello to my group! Test passed!");
  free(result);
}
END_TEST

START_TEST(simple_insert_start) {
  const char src[1024] = "Hello to my group!";
  const char str[1024] = " Test passed!";
  char *result = s21_insert(src, str, 0);
  ck_assert_str_eq(result, " Test passed!Hello to my group!");
  free(result);
}
END_TEST

START_TEST(null_insert) {
  char *src = NULL;
  char *str = NULL;
  s21_size_t index = 55;
  char *expected = NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_insert() {
  Suite *suite = suite_create("insert_suite");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, simple_insertion);
  tcase_add_test(tcase_core, simple_insert_with_space);
  tcase_add_test(tcase_core, simple_insert_start);
  tcase_add_test(tcase_core, null_insert);

  suite_add_tcase(suite, tcase_core);
  return suite;
}