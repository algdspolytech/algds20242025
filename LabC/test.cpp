#include "labC.h"
#include "stack.h"
#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

// Тест добавления элемента в стек
TEST(Graph_Stack_Tests, push_to_stack_test_1) {
    Stack* stack = initialize_stack();

    push_to_stack(stack, 6);

    EXPECT_EQ(stack->head->value, 6);
}

// Тест получения элемента из стека
TEST(Graph_Stack_Tests, pop_from_stack_test_2) {
    Stack* stack = initialize_stack();

    push_to_stack(stack, 12);
    int result = pop_from_stack(stack);

    EXPECT_EQ(result, 12);
}

// Тест получения элемента из стека если стек пустой
TEST(Graph_Stack_Tests, pop_from_empty_stack_test_3) {
    Stack* stack = initialize_stack();

    push_to_stack(stack, 12);
    int secondPop = pop_from_stack(stack);
    int firstPop = pop_from_stack(stack);

    EXPECT_EQ(firstPop, 0);
}

// Тест добавления вершины в граф
TEST(Graph_Graph_Tests, insert_vertex_test_4) {
    GraphStructure* graph = create_graph();

    char vertexName[] = "123";
    insert_vertex(graph, vertexName);

    EXPECT_EQ(vertexName, graph->vertexNames[0]);
}

// Тест добавления связи в граф
TEST(Graph_Graph_Tests, insert_edge_test_5) {
    GraphStructure* graph = create_graph();

    char vertexName1[] = "123";
    insert_vertex(graph, vertexName1);
    char vertexName2[] = "abc";
    insert_vertex(graph, vertexName2);

    insert_edge(graph, vertexName1, vertexName2);

    EXPECT_EQ(1, graph->adjacencyList[0][0]);
}

// Тест получения индекса узла по его имени
TEST(Graph_Graph_Tests, find_vertex_index_test_6) {
    GraphStructure* graph = create_graph();

    char vertexName1[] = "123";
    insert_vertex(graph, vertexName1);
    char vertexName2[] = "abc";
    insert_vertex(graph, vertexName2);

    EXPECT_EQ(1, find_vertex_index(graph, vertexName2));
}

// Тест получения имени узла по его индексу
TEST(Graph_Graph_Tests, fetch_vertex_name_test_7) {
    GraphStructure* graph = create_graph();

    char vertexName1[] = "123";
    insert_vertex(graph, vertexName1);
    char vertexName2[] = "abc";
    insert_vertex(graph, vertexName2);

    EXPECT_EQ(vertexName2, fetch_vertex_name(graph, 1));
}

// Тест функции проверки графа на ацикличность в случае если граф цикличен
TEST(Graph_Graph_Tests, verify_acylclic_cycle_graph_8) {
    GraphStructure* graph = create_graph();

    insert_vertex(graph, "a");
    insert_vertex(graph, "b");
    insert_vertex(graph, "c");
    insert_vertex(graph, "d");

    insert_edge(graph, "a", "b");
    insert_edge(graph, "b", "c");
    insert_edge(graph, "c", "a");

    int cycle = verify_acylclic(graph);

    EXPECT_EQ(cycle, 0);
}

// Тест функции проверки графа на ацикличность в случае если граф ацикличен
TEST(Graph_Graph_Tests, verify_acylclic_acylclic_graph_9) {
    GraphStructure* graph = create_graph();

    insert_vertex(graph, "a");
    insert_vertex(graph, "b");
    insert_vertex(graph, "c");
    insert_vertex(graph, "d");

    insert_edge(graph, "a", "b");
    insert_edge(graph, "b", "c");
    insert_edge(graph, "c", "d");

    int cycle = verify_acylclic(graph);

    EXPECT_EQ(cycle, 1);
}

// Тест функции топологической сортировки
TEST(Graph_Graph_Tests, perform_topological_sort_10) {
    GraphStructure* graph = create_graph();

    insert_vertex(graph, "a");
    insert_vertex(graph, "b");
    insert_vertex(graph, "c");
    insert_vertex(graph, "d");

    insert_edge(graph, "a", "b");
    insert_edge(graph, "b", "c");
    insert_edge(graph, "c", "d");

    Stack* stack = initialize_stack();
    int* visited = (int*)malloc(sizeof(int) * graph->vertexCount);
    for (int i = 0; i < graph->vertexCount; i++)
        visited[i] = 0;

    for (int vertex = 0; vertex < graph->vertexCount; vertex++)
        perform_topological_sort(graph, stack, vertex, visited);

    int expectedOrder[4] = { 3, 2, 1, 0 };

    for (int i = 0; i < 4; i++)
        EXPECT_EQ(expectedOrder[i], pop_from_stack(stack));
}
