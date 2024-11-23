#include "bfs.h"
#include "graph.h"
#include "stack.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>
#include <stdlib.h>

void setUp() {}

void tearDown() {}

void test_add_element_to_empty_stack_n1();
void test_add_element_to_filled_stack_n2();
void test_pop_last_element_n3();
void test_pop_first_element_n4();
void test_pop_element_n5();
void test_pop_from_empty_stack_n6();
void test_add_vertex_to_empty_graph_n7();
void test_add_vertex_to_filled_graph_n8();
void test_bfs_in_fild_graph_n9();
void test_bfs_in_empty_graph_n10();

int main() {

  UNITY_BEGIN();

  RUN_TEST(test_add_element_to_empty_stack_n1);
  RUN_TEST(test_add_element_to_filled_stack_n2);
  RUN_TEST(test_pop_last_element_n3);
  RUN_TEST(test_pop_first_element_n4);
  RUN_TEST(test_pop_element_n5);
  RUN_TEST(test_pop_from_empty_stack_n6);
  RUN_TEST(test_add_vertex_to_empty_graph_n7);
  RUN_TEST(test_add_vertex_to_filled_graph_n8);
  RUN_TEST(test_bfs_in_fild_graph_n9);
  RUN_TEST(test_bfs_in_empty_graph_n10);

  return UNITY_END();
}

void test_add_element_to_empty_stack_n1() {
  Stack *stack = init();
  push(stack, 1);
  TEST_ASSERT_EQUAL(1, pop(stack, -1));
  destroy(stack);
}

void test_add_element_to_filled_stack_n2() {
  Stack *stack = init();
  push(stack, 1);
  push(stack, 2);
  TEST_ASSERT_EQUAL(2, pop(stack, -1));
  destroy(stack);
}

void test_pop_last_element_n3() {
  Stack *stack = init();
  push(stack, 1);
  push(stack, 2);
  push(stack, 3);
  TEST_ASSERT_EQUAL(3, pop(stack, -1));
  destroy(stack);
}

void test_pop_first_element_n4() {
  Stack *stack = init();
  push(stack, 1);
  push(stack, 2);
  push(stack, 3);
  TEST_ASSERT_EQUAL(1, pop(stack, 0));
  destroy(stack);
}

void test_pop_element_n5() {
  Stack *stack = init();
  push(stack, 1);
  push(stack, 2);
  push(stack, 3);
  TEST_ASSERT_EQUAL(2, pop(stack, 1));
  destroy(stack);
}

void test_pop_from_empty_stack_n6() {
  Stack *stack = init();
  TEST_ASSERT_EQUAL(EOF, pop(stack, 0));
  destroy(stack);
}

void test_add_vertex_to_empty_graph_n7() {
  Graph *graph = make_graph(4);
  add_vertex(graph, 1, 3);
  TEST_ASSERT_EQUAL(3, graph->adjLists[1]->v);
  destroy_graph(graph);
}

void test_add_vertex_to_filled_graph_n8() {
  Graph *graph = make_graph(4);
  add_vertex(graph, 1, 2);
  add_vertex(graph, 1, 3);
  TEST_ASSERT_EQUAL(3, graph->adjLists[1]->v);
  destroy_graph(graph);
}

void test_bfs_in_fild_graph_n9() {
  Graph *graph = make_graph(7);
  add_vertex(graph, 0, 2);
  add_vertex(graph, 0, 1);
  add_vertex(graph, 2, 1);
  add_vertex(graph, 2, 3);
  add_vertex(graph, 1, 3);
  add_vertex(graph, 3, 4);
  add_vertex(graph, 4, 5);
  add_vertex(graph, 5, 6);
  TEST_ASSERT_EQUAL(4, bfs(graph, 2, 6));
  destroy_graph(graph);
}

void test_bfs_in_empty_graph_n10() {
  Graph *graph = make_graph(7);
  TEST_ASSERT_EQUAL(1000000, bfs(graph, 2, 6));
  destroy_graph(graph);
}