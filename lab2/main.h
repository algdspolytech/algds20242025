#ifndef MAIN_H
#define MAIN_H
#define MAX_VERTICES 100

#ifdef __cplusplus
extern "C" {
#endif

	// Функция для чтения графа из файла с представлением в виде списка смежности
	void readAdjacencyList(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertex_count);

	// Функция для чтения графа из файла с представлением в виде матрицы смежности
	void readAdjacencyMatrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertex_count);

	// Функция для сравнения двух графов на совпадение
	int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertex_count);

#ifdef __cplusplus
}
#endif

#endif 



