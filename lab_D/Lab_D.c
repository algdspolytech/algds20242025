#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int vertex;
    int depth;
} StackNode;

typedef struct {
    int V, s, t, K;
    int** adj;    // Списки смежности
    int* visited; // Массив посещенных вершин
    int* path; // Массив для хранения текущего пути
    int path_length; // Длина текущего пути
} Graph;

// Функция считывания строки в файле
char* Read_line(FILE* file) {
    char* line = malloc(sizeof(char));
    if (line == NULL) {
        free(line);
        printf("Ошибка выделения памяти");
        return NULL;
    }
    char c;
    int i = 1;
    while (fscanf(file, "%c", &c) != EOF) {
        if (c == '\n' || c == '\0') {
            break;
        }
        line[i - 1] = c;
        i++;
        line = realloc(line, i * sizeof(char));
        if (line == NULL) {
            free(line);
            printf("Ошибка выделения памяти");
            return NULL;
        }
    }
    line[i - 1] = '\0';
    return line;
}

// Функция для освобождения памяти, выделенной под матрицу
void Free_Matrix_adj(int** Matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(Matrix[i]);
        Matrix[i] = NULL;
    }
    free(Matrix);
    Matrix = NULL;
}

// Функция считывания параметров задачи (графа)
Graph* Parse_parameters(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d %d %d %d", &graph->V, &graph->s, &graph->t, &graph->K);
    graph->s--; // Преобразуем к нулевой индексации
    graph->t--;
    graph->path_length = 0;
    fclose(file);
    return graph;
}

// Функция для создания матрицы смежности и инициализации её нулями
int** Create_Matrix_adj(int vertices) {
    int** Matrix_adj = (int**)malloc(vertices * sizeof(int*));
    if (Matrix_adj == NULL) {
        free(Matrix_adj);
        return NULL;
    }
    int flag = 0;
    for (int i = 0; i < vertices; i++) {
        Matrix_adj[i] = (int*)malloc(vertices * sizeof(int));
        if (Matrix_adj[i] == NULL) {
            flag = 1;
        }
        if (flag == 0) {
            for (int j = 0; j < vertices; j++) {
                Matrix_adj[i][j] = 0; // Инициализируем нулями
            }
        }
    }
    if (flag == 1) {
        Free_Matrix_adj(Matrix_adj, vertices);
        return NULL;
    }
    return Matrix_adj;
}

// Функция создания графа
Graph* Create_graph(char* filename) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph = Parse_parameters(filename, graph);
    graph->adj = Create_Matrix_adj(graph->V);
    graph->visited = calloc(graph->V, sizeof(int));
    graph->path = malloc(graph->V * sizeof(int));
    return graph;
}

// Функция для инициализации графа и чтения данных
int Parse_Graph(Graph* graph, const char* filename) {
    FILE* input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "Ошибка открытия файла %s.\n", filename);
        return 0;
    }
    char* line = Read_line(input);
    for (int j = 0; j < graph->V; j++) {
        line = Read_line(input);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        char* token;

        // Получаем список смежных вершин (разделённых пробелами)
        token = strtok(line, " ");

        while (token != NULL) {
            int i = atoi(token) - 1; // Преобразуем строку в число
            graph->adj[j][i] = 1;
            graph->adj[i][j] = 1;
            token = strtok(NULL, " "); // Переходим к следующему токену
        }
    }

    fclose(input);
    return 1;
}

// Итеративная функция DFS для поиска пути длиной >= K
int Find_path(Graph* graph) {
    // Создаем стек для хранения состояния поиска
    StackNode* stack = malloc(graph->V * sizeof(StackNode));
    int top = -1; // Указатель на вершину стека

    // Инициализируем стек начальной вершиной
    stack[++top] = (StackNode){.vertex = graph->s, .depth = 0};
    graph->visited[graph->s] = 1;

    // Массив для отслеживания пути
    int path_index = 0;

    while (top >= 0) {
        StackNode node = stack[top--];
        int v = node.vertex;
        int depth = node.depth;

        // Добавляем текущую вершину в путь
        graph->path[path_index++] = v;

        // Проверяем, достигли ли мы вершины t с нужной глубиной
        if (v == graph->t && depth >= graph->K) {
            graph->path_length = path_index;
            printf("\n");
            free(stack);
            return 1;
        }

        int has_unvisited_neighbor = 0; // Флаг наличия непосещенных соседей

        // Проходим по всем вершинам, проверяя смежность с текущей вершиной `v`
        for (int u = 0; u < graph->V; u++) {
            if (graph->adj[v][u] == 1 &&
                !graph->visited[u]) { // Проверяем, смежность и посещение
                stack[++top] = (StackNode){
                    .vertex = u, .depth = depth + 1}; // Добавляем в стек
                graph->visited[u] = 1; // Отмечаем вершину как посещенную
                has_unvisited_neighbor = 1;
            }
        }

        // Если у текущей вершины нет непосещенных соседей, удаляем ее из пути
        if (!has_unvisited_neighbor) {
            path_index--; // Удаляем текущую вершину из пути
            graph->visited[v] = 0; // Сбрасываем отметку посещения
        }
    }

    // Путь не найден
    free(stack);
    return 0;
}
// Функция для записи результата в файл
void Write_result(Graph* graph, const char* output_filename) {
    FILE* output = fopen(output_filename, "w");
    if (!output) {
        fprintf(stderr, "Ошибка открытия файла %s.\n", output_filename);
        return;
    }

    if (Find_path(graph)) {
        for (int i = 0; i < graph->path_length; i++) {
            fprintf(output, "%d ", graph->path[i] + 1);
        }
        fprintf(output, "\n");
    } else {
        fprintf(output, "0\n");
    }

    fclose(output);
}

// Функция для освобождения выделенной памяти
void Free_memory(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph->visited);
    free(graph->path);
    free(graph);
}

/*
int main() {
    char* input = "input.txt";

    Graph* graph = Create_graph(input);

    if (!Parse_Graph(graph, input)) {
        return 1;
    }

    Write_result(graph, "output.txt");

    Free_memory(graph);
    return 0;
}
*/