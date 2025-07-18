#include "../s21_funcs/s21_string.h"
#include "s21_tests.h"

START_TEST(memcpy_1) {
  const char src[1024] = "Decrease the line";
  char dest[1024] = {'\0'};
  ck_assert_ptr_eq(s21_memcpy(dest, src, 6), memcpy(dest, src, 6));
  dest[6] = '\0';
  ck_assert_str_eq(dest, "Decrea");
}
END_TEST

START_TEST(memcpy_2) {
  char src[1024] = "Decrease the";
  char dest[1024];
  ck_assert_ptr_eq(s21_memcpy(dest, src, sizeof(src)),
                   memcpy(dest, src, sizeof(src)));
  ck_assert_str_eq(dest, "Decrease the");
}
END_TEST

START_TEST(memcpy_3) {
  char str1[] = "Decrease!";
  char str2[] = "";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(memcpy_4) {
  char src[] = "Source";
  char dest[] = "Destination";
  char *res1 = s21_memcpy(dest, src, 0);
  char *res2 = memcpy(dest, src, 0);
  ck_assert_ptr_eq(res1, res2);
  ck_assert_str_eq(dest, "Destination");
}
END_TEST

START_TEST(memcpy_5) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_ptr_eq(s21_memcpy(str2, str1, strlen(str2)),
                   memcpy(str2, str1, strlen(str2)));
}
END_TEST

START_TEST(memcpy_6) {
  char str[20] = "Overlap test";
  ck_assert_ptr_eq(s21_memcpy(str + 5, str, 7), memcpy(str + 5, str, 7));
}
END_TEST

Suite *suite_memcpy() {
  Suite *suite = suite_create("test_memcpy");
  TCase *tcase_core = tcase_create("memcpy_tc");

  tcase_add_test(tcase_core, memcpy_1);
  tcase_add_test(tcase_core, memcpy_2);
  tcase_add_test(tcase_core, memcpy_3);
  tcase_add_test(tcase_core, memcpy_4);
  tcase_add_test(tcase_core, memcpy_5);
  tcase_add_test(tcase_core, memcpy_6);

  suite_add_tcase(suite, tcase_core);
  return suite;
}