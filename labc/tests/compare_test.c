#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h" // IWYU pragma: keep
#include "../include/graph.h"

Test(compare_test, 1, .description = "Графы совпадают") {
  graph_list l = parse_list("res/l.txt");
  graph_matrix m = parse_matrix("res/m.txt");
  cr_assert_eq(compare_lm(&l, &m), 1);
  del_l(&l);
  del_m(&m);
}

Test(compare_test, 2, .description = "Графы различны") {
  graph_list l = parse_list("res/l2.txt");
  graph_matrix m = parse_matrix("res/m.txt");
  cr_assert_eq(compare_lm(&l, &m), 0);
  del_l(&l);
  del_m(&m);
}
