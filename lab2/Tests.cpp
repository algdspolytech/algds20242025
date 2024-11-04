#include "pch.h"
#include "../Sasha_LabC/LabC.cpp"
#include "../Sasha_LabC/Stack.cpp"


// Тест добавления элемента в стек
TEST(LabC_Stack_Tests, push_stack_test_1) {
	Stack* stack = init_stack();

	push_stack(stack, 6);

	EXPECT_EQ(stack->head->value, 6);
}

// Тест получаения элемента из стека
TEST(LabC_Stack_Tests, pop_stack_test_2) {
	Stack* stack = init_stack();

	push_stack(stack, 12);
	int a = pop_stack(stack);

	EXPECT_EQ(a, 12);
}

// Тест получаения элемента из стека если стек пустой
TEST(LabC_Stack_Tests, pop_stack_EmptyStack_test_3) {
	Stack* stack = init_stack();

	push_stack(stack, 12);
	int b = pop_stack(stack);
	int a = pop_stack(stack);

	EXPECT_EQ(a, 0);
}

// Тест добавления вершины в граф
TEST(LabC_Graph_Tests, add_vertex_test_4) {
	Graph* graph = init_graph();

	char a[] = "123";
	add_vertex(graph, a);

	EXPECT_EQ(a, graph->names[0]);
}


// Тест добавления связи в граф
TEST(LabC_Graph_Tests, add_edge_test_5) {
	Graph* graph = init_graph();

	char a[] = "123";
	add_vertex(graph, a);
	char b[] = "abc";
	add_vertex(graph, b);

	add_edge(graph, a, b);

	EXPECT_EQ(1, graph->adjacency[0][0]);
}

// Тест получения индекса узла по его имени
TEST(LabC_Graph_Tests, get_vertex_index_test_6) {
	Graph* graph = init_graph();

	char a[] = "123";
	add_vertex(graph, a);
	char b[] = "abc";
	add_vertex(graph, b);


	EXPECT_EQ(1, get_vertex_index(graph, b));
}

// Тест получения имени узла по его индексу
TEST(LabC_Graph_Tests, get_vertex_name_test_7) {
	Graph* graph = init_graph();

	char a[] = "123";
	add_vertex(graph, a);
	char b[] = "abc";
	add_vertex(graph, b);

	EXPECT_EQ(b, get_vertex_name(graph, 1));
}

// Тест функции проверки графа на ацикличность в случае если граф цикличен
TEST(LabC_Graph_Tests, acycle_check_CycleGraph_8) {
	Graph* graph = init_graph();

	add_vertex(graph, "a");
	add_vertex(graph, "b");
	add_vertex(graph, "c");
	add_vertex(graph, "d");

	add_edge(graph, "a", "b");
	add_edge(graph, "b", "c");
	add_edge(graph, "c", "a");

	int cycle = acycle_check(graph);

	EXPECT_EQ(cycle, 0);
}

// Тест функции проверки графа на ацикличность в случае если граф ацикличен
TEST(LabC_Graph_Tests, acycle_check_AcycleGraph_9) {
	Graph* graph = init_graph();

	add_vertex(graph, "a");
	add_vertex(graph, "b");
	add_vertex(graph, "c");
	add_vertex(graph, "d");

	add_edge(graph, "a", "b");
	add_edge(graph, "b", "c");
	add_edge(graph, "c", "d");

	int cycle = acycle_check(graph);

	EXPECT_EQ(cycle, 1);
}

// Тест функции топологической сортировки
TEST(LabC_Graph_Tests, topological_sort_10) {
	Graph* graph = init_graph();

	add_vertex(graph, "a");
	add_vertex(graph, "b");
	add_vertex(graph, "c");
	add_vertex(graph, "d");

	add_edge(graph, "a", "b");
	add_edge(graph, "b", "c");
	add_edge(graph, "c", "d");

	Stack* stack = init_stack();
	int* visited = (int*)malloc(sizeof(int) * graph->v);
	for (int i = 0; i < graph->v; i++)
		visited[i] = 0;
	
	for (int v=0;v<graph->v;v++)
		topological_sort(graph, stack, v, visited);

	int equal[4] = {3, 2, 1, 0};

	for (int i=0;i<4;i++)
		EXPECT_EQ(equal[i], pop_stack(stack));
}