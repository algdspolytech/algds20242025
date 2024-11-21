#include "funcs.h"
#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

int edge_exists(Node *graph, int u, int v) {
  for (int i = 0; i < graph[u].count; i++) {
    if (graph[u].neighbors[i] == v)
      return 1;
  }
  return 0;
}

TEST(_dfs, PathExists) { /*all return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3, s = 1, t = 3, K = 2;
  create_graph(graph, &V);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 3);
  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length =
      dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  EXPECT_GT(path_length, 0);
  EXPECT_EQ(path[path_length - 1], t);
  EXPECT_GE(path_length - 1, K);
}

TEST(_dfs, NoPathForLargeK) { /*return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3, s = 1, t = 3, K = 3;
  create_graph(graph, &V);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 3);
  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length =
      dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  EXPECT_EQ(path_length, 0);
}

TEST(_dfs, NoPathExists) { /*return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3, s = 1, t = 3, K = 1;
  create_graph(graph, &V);
  add_edge(graph, 1, 2);
  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length =
      dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  EXPECT_EQ(path_length, 0);
}

TEST(_dfs, CycleInGraphNoValidPath) { /*return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3, s = 1, t = 3, K = 4;
  create_graph(graph, &V);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 3);
  add_edge(graph, 3, 1);

  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length =
      dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  EXPECT_EQ(path_length, 0);
}

TEST(_dfs, SingleNodeGraph) { /*all return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 1, s = 1, t = 1, K = 0;
  create_graph(graph, &V);

  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length =
      dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  EXPECT_GT(path_length, 0);
  EXPECT_EQ(path[path_length - 1], t);
}

TEST(_dfs, EmptyGraph) { /*return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3, s = 1, t = 3, K = 1;
  create_graph(graph, &V);
  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length =
      dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  EXPECT_EQ(path_length, 0);
}

TEST(_add_edge, SingleEdge) { /*all return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3;
  create_graph(graph, &V);

  add_edge(graph, 1, 2);

  EXPECT_TRUE(edge_exists(graph, 1, 2));
  EXPECT_TRUE(edge_exists(graph, 2, 1));
  EXPECT_EQ(graph[1].count, 1);
  EXPECT_EQ(graph[2].count, 1);
}

TEST(_add_edge, TwoEdges) { /*all return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3;
  create_graph(graph, &V);

  add_edge(graph, 1, 2);
  add_edge(graph, 2, 3);

  EXPECT_TRUE(edge_exists(graph, 1, 2));
  EXPECT_TRUE(edge_exists(graph, 2, 1));
  EXPECT_TRUE(edge_exists(graph, 2, 3));
  EXPECT_TRUE(edge_exists(graph, 3, 2));

  EXPECT_EQ(graph[1].count, 1);
  EXPECT_EQ(graph[2].count, 2);
  EXPECT_EQ(graph[3].count, 1);
}

TEST(_add_edge, SelfLoop) { /*all return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3;
  create_graph(graph, &V);

  add_edge(graph, 1, 1);

  EXPECT_TRUE(edge_exists(graph, 1, 1));
  EXPECT_EQ(graph[1].count, 1);
}

TEST(_add_edge, DisconnectedGraph) { /*all return True*/
  Node graph[MAX_VERTICES + 1];
  int V = 3;
  create_graph(graph, &V);

  add_edge(graph, 1, 2);

  EXPECT_TRUE(edge_exists(graph, 1, 2));
  EXPECT_TRUE(edge_exists(graph, 2, 1));
  EXPECT_EQ(graph[1].count, 1);
  EXPECT_EQ(graph[2].count, 1);
  EXPECT_EQ(graph[3].count, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}