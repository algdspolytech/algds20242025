#include "LabC.h"


int main() {
	// Загружаем граф из файла
	FILE* file = fopen("input.txt", "r");
	Graph* graph = load_graph(file);
	fclose(file);

	// Проверяем граф на ацикличность в случае если он цикличен выводим ошибку
	if (acycle_check(graph) == 0) {
		file = fopen("output.txt", "w");
		fprintf(file, "[Error]");

		return 0;
	}

	// Производим топологическую сортировку
	int* visited = (int*)malloc(sizeof(int) * graph->v);
	for (int i = 0; i < graph->v; i++)
		visited[i] = 0;

	Stack* stack = init_stack();

	for (int i = 0; i < graph->v; i++)
		if (visited[i] == 0)
			topological_sort(graph, stack, i, visited);

	// Выводим в файл результат топологической сортировки
	file = fopen("output.txt", "w");

	int size = stack->size;
	for (int i = 0;i < size;i++)
		fprintf(file, "%s ", get_vertex_name(graph, pop_stack(stack)));

	fclose(file);
}