#include "labC.h"

int main() {
    // Загружаем граф из файла
    FILE* file = fopen("input.txt", "r");
    GraphStructure* graph = read_graph(file);
    fclose(file);

    // Проверяем граф на ацикличность в случае если он цикличен выводим ошибку
    if (verify_acylclic(graph) == 0) {
        file = fopen("output.txt", "w");
        fprintf(file, "[Error]");

        return 0;
    }

    // Производим топологическую сортировку
    int* visited = (int*)malloc(sizeof(int) * graph->vertexCount);
    for (int i = 0; i < graph->vertexCount; i++)
        visited[i] = 0;

    Stack* stack = initialize_stack();

    for (int i = 0; i < graph->vertexCount; i++)
        if (visited[i] == 0)
            perform_topological_sort(graph, stack, i, visited);

    // Выводим в файл результат топологической сортировки
    file = fopen("output.txt", "w");

    int stackSize = stack->size;
    for (int i = 0; i < stackSize; i++)
        fprintf(file, "%s ", fetch_vertex_name(graph, pop_from_stack(stack)));

    fclose(file);
}
