#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h" // IWYU pragma: keep
#include "../include/graph.h"

Test(parse_matrix, 1, .description = "Создание матрицы с матрицей смежности") {
  graph_matrix res = parse_matrix("res/m.txt");
  cr_assert_eq(res.size, 5);
  cr_assert_eq(res.adj_matrix[0], 0);
  cr_assert_eq(res.adj_matrix[1], 1);
  cr_assert_eq(res.adj_matrix[2], 0);
  cr_assert_eq(res.adj_matrix[3], 0);
  cr_assert_eq(res.adj_matrix[4], 1);
  cr_assert_eq(res.adj_matrix[5], 1);
  cr_assert_eq(res.adj_matrix[6], 0);
  cr_assert_eq(res.adj_matrix[7], 1);
  cr_assert_eq(res.adj_matrix[8], 0);
  cr_assert_eq(res.adj_matrix[9], 1);
  cr_assert_eq(res.adj_matrix[10], 0);
  cr_assert_eq(res.adj_matrix[11], 1);
  cr_assert_eq(res.adj_matrix[12], 0);
  cr_assert_eq(res.adj_matrix[13], 1);
  cr_assert_eq(res.adj_matrix[14], 1);
  cr_assert_eq(res.adj_matrix[15], 0);
  cr_assert_eq(res.adj_matrix[16], 0);
  cr_assert_eq(res.adj_matrix[17], 1);
  cr_assert_eq(res.adj_matrix[18], 0);
  cr_assert_eq(res.adj_matrix[19], 1);
  cr_assert_eq(res.adj_matrix[20], 1);
  cr_assert_eq(res.adj_matrix[21], 1);
  cr_assert_eq(res.adj_matrix[22], 1);
  cr_assert_eq(res.adj_matrix[23], 1);
  cr_assert_eq(res.adj_matrix[24], 0);
  del_m(&res);
}
