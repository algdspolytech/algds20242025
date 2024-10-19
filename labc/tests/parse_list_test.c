#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h" // IWYU pragma: keep
#include "../include/graph.h"

Test(parse_list, 1, .description = "Создание матрицы со списком смежности") {
  graph_list res = parse_list("res/l.txt");
  cr_assert(all(
      res.adj_list[0][1] == 2, res.adj_list[0][2] == 5, res.adj_list[1][1] == 1,
      res.adj_list[1][2] == 3, res.adj_list[1][3] == 5, res.adj_list[2][1] == 2,
      res.adj_list[2][2] == 4, res.adj_list[2][3] == 5, res.adj_list[3][1] == 3,
      res.adj_list[3][2] == 5, res.adj_list[4][1] == 1, res.adj_list[4][2] == 2,
      res.adj_list[4][3] == 3, res.adj_list[4][4] == 4));
  del_l(&res);
}
