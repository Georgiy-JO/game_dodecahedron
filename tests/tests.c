#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include ".."

// elevator    begining

void test_block_1(SRunner *sr) {
  Suite *s = suite_create("Test block #1");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, ...);
  
  srunner_add_suite(sr, s);
}
void test_block_2(SRunner *sr) {
  Suite *s = suite_create("Test block #2");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, ...);
  
  srunner_add_suite(sr, s);
}
void test_block_3(SRunner *sr) {
  Suite *s = suite_create("Test block #3");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, ...);
  
  srunner_add_suite(sr, s);
}
// elevator     end
int main(void) {
  int number_failed;
  Suite *s = suite_create("My tests");
  SRunner *sr = srunner_create(s);

  test_block_1(sr);
  test_block_2(sr);
  test_block_3(sr);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
