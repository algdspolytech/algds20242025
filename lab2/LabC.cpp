#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"


typedef struct Graph {
	int v; // Кол-во вершин

	int** adjacency; // Список смежности графа
	char** names; // Имя каждой вершины
} Graph;

// Создание графа
Graph* init_graph() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->v = 0;
	graph->adjacency = (int**)malloc(sizeof(int*));
	graph->names = (char**)malloc(sizeof(char*));

	return graph;
}

// Добавляем вершину
void add_vertex(Graph* graph, char* vertex) {
	graph->v++;
	graph->names = (char**)realloc(graph->names, sizeof(char*)*graph->v);
	graph->names[graph->v-1] = vertex;

	graph->adjacency = (int**)realloc(graph->adjacency, sizeof(int*)*graph->v);
	graph->adjacency[graph->v - 1] = (int*)malloc(sizeof(int));
	graph->adjacency[graph->v - 1][0] = -1;

}

// Функция срванения строк
static int compare_stings(char* a, char* b) {
	int i = 0;
	while (a[i] != '\0' || b[i] != '\0')
		if (a[i] != b[i++]) return 0;

	return 1;
}

// Функция для получения индекса вершины по ее названию
 int get_vertex_index(Graph* graph, char* vertex) {
	int index = 0;
	for (index = 0;index < graph->v;index++)
		if (compare_stings(graph->names[index], vertex) == 1) return index;
	return -1;
}

// Функция для получения имени вершины по индексу
 char* get_vertex_name(Graph* graph, int index) {
	return graph->names[index];
}

// Добавляем грань из v1 в v2
 void add_edge(Graph* graph, char* v1, char* v2) {
	int n1 = get_vertex_index(graph, v1);
	int n2 = get_vertex_index(graph, v2);

	int length = 0;
	while (graph->adjacency[n1][length] != -1) length++;
	graph->adjacency[n1] = (int*)realloc(graph->adjacency[n1], sizeof(int) * (length + 2));
	graph->adjacency[n1][length] = n2;
	graph->adjacency[n1][length + 1] = -1;
}

// Функция для чтения одного слова из файла
static char* read_name(FILE* file) {
	int size = 0;
	char* name = (char*)malloc(sizeof(char));

	char sym;
	do {
		sym = fgetc(file);

		size++;
		name = (char*)realloc(name, sizeof(char) * size);
		name[size - 1] = sym;

		if (sym == ' ' || sym == '\n' || sym == EOF) {
			name = (char*)realloc(name, sizeof(char) * (size + 1));
			name[size] = '\0';

			return name;
		}
	} while (sym != '\n' && sym != EOF);
}

// Функция для получения длинны строки 
static int str_len(char* str) {
	int len = 0;
	while (str[len] != '\0') len++;

	return len;
}

// Получаем из файла граф список вершин
 Graph* load_graph(FILE* file) {
	// Создаем граф
	Graph* graph = init_graph();

	// Загружаем список вершин

	int flag = 1;
	do {
		char* name = read_name(file);
		int len = str_len(name);

		if (name[len - 1] == '\n') flag = 0;
		name[len - 1] = '\0';

		add_vertex(graph, name);
	} while (flag);


	// Загружаем грани
	flag = 1;
	do {
		char* name1 = read_name(file);
		int len1 = str_len(name1);
		char* name2 = read_name(file);
		int len2 = str_len(name2);

		if (name2[len2 - 1] == EOF) flag = 0;
		name1[len1 - 1] = '\0';
		name2[len2 - 1] = '\0';

		add_edge(graph, name1, name2);
	} while (flag);

	return graph;
}

 // Функция топологической сортировки
 void topological_sort(Graph* graph, Stack* stack, int v, int* visited) {
	 visited[v] = 1;

	 int j = 0;
	 while (graph->adjacency[v][j] != -1) {
		if (visited[graph->adjacency[v][j]] == 0)
			topological_sort(graph, stack, graph->adjacency[v][j], visited);
		j++;
	 }

	 push_stack(stack, v);
 }

 // Рекурсивная часть функции проверки графа на ацикличность
 static int rec_acycle_check(Graph* graph, int* visited, int v) {
	 int j = 0;
	 visited[v] = 1;
	 while (graph->adjacency[v][j] != -1) {
		 if (visited[graph->adjacency[v][j]] == 1)
			 return 0;
		 else {
			 int r = rec_acycle_check(graph, visited, graph->adjacency[v][j]);
			 visited[v] = 0;
			 return r;
		 }
	 }
	 visited[v] = 0;
	 return 1;
 }

 // Функция проверки графа на ацикличность
 int acycle_check(Graph* graph) {
	 int* visited = (int*)malloc(sizeof(int) * graph->v);
	 for (int i = 0; i < graph->v; i++)
		 visited[i] = 0;

	 for (int v = 0;v < graph->v;v++)
		 if (rec_acycle_check(graph, visited, v) == 0)
			 return 0;

	 return 1;

 }