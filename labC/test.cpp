#include "funcs.h"
#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

int vertex_in_adj_list(Node *adj_list, int vertex) {

  Node *p = adj_list;

  while (p) {
    if (p->vertex == vertex) {
      return 1;
    }
    p = p->next;
  }
  return 0;
}

TEST(_add_edge, CheckStructure) { /*all return True*/

  Graph *graph = create_graph(5);

  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 3, 4);

  EXPECT_EQ(graph->adj_lists[0]->vertex, 2);
  EXPECT_EQ(graph->adj_lists[0]->next->vertex, 1);

  EXPECT_EQ(graph->adj_lists[3]->vertex, 4);
  EXPECT_EQ(graph->adj_lists[3]->next->vertex, 1);

  free(graph);
}

TEST(_DFS, ExistentPath) { /*all return True*/

  Graph *graph = create_graph(5);

  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 3, 4);

  EXPECT_TRUE(DFS(graph, 0, 4));

  for (int i = 0; i < graph->n_vertices; i++) {
    graph->visited[i] = 0;
  }

  EXPECT_TRUE(DFS(graph, 2, 3));

  free(graph);
}

TEST(_DFS, NonExistentPath) { /*return False*/

  Graph *graph = create_graph(5);

  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 3, 4);

  EXPECT_FALSE(DFS(graph, 0, 4));
}

TEST(_DFS, NoEdges) { /*return False*/

  Graph *isolated_graph = create_graph(1);

  EXPECT_FALSE(DFS(isolated_graph, 0, 1));

  free(isolated_graph);
}

TEST(_DFS, DFSVisitedArrayNoReset) { /*return True*/

  Graph *graph = create_graph(3);

  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);

  DFS(graph, 0, 2);

  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(graph->visited[i], 1);
  }

  free(graph);
}

TEST(_parse_line, ValidInput) { /*all return True*/

  char line[] = "3 5";
  int src = -1, dest = -1;
  int edges[MAX_VERTICES][2];
  int max_vertex = -1;
  int edge_count = 0;

  parse_line(line, &src, &dest, edges, &max_vertex, &edge_count);

  EXPECT_EQ(src, 3);
  EXPECT_EQ(dest, 5);
  EXPECT_EQ(edges[0][0], 3);
  EXPECT_EQ(edges[0][1], 5);
  EXPECT_EQ(max_vertex, 5);
  EXPECT_EQ(edge_count, 1);
}

TEST(_parse_line, InvalidInput) { /*return True*/

  char line[] = "invalid";
  int src = -1, dest = -1;
  int edges[MAX_VERTICES][2];
  int max_vertex = -1;
  int edge_count = 0;

  parse_line(line, &src, &dest, edges, &max_vertex, &edge_count);

  EXPECT_EQ(edge_count, 0);
}

TEST(_parse_line, NoInput) { /*return True*/

  char line[] = "";
  int src = -1, dest = -1;
  int edges[MAX_VERTICES][2];
  int max_vertex = -1;
  int edge_count = 0;

  parse_line(line, &src, &dest, edges, &max_vertex, &edge_count);

  EXPECT_EQ(edge_count, 0);
}

TEST(GraphTest, ReadFileSuccess) { /*all return True*/

  char filename[30];
  strcpy(filename, "test_graph.txt");

  FILE *file = fopen(filename, "w");

  fprintf(file, "0 1\n1 2\n2 3\n");
  fclose(file);

  Graph *graph = read_file(filename);

  ASSERT_NE(graph, nullptr);
  EXPECT_EQ(graph->n_vertices, 4);

  free(graph);
  remove(filename);
}

TEST(_read_file, InvalidFile) { /*return True*/

  char filename[30];
  strcpy(filename, "nonexistent_file.txt");

  Graph *graph = read_file(filename);

  EXPECT_EQ(graph, nullptr);

  free(graph);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}