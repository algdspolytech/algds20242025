#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#pragma warning(disable:4996)

#define NOT_FOUND (0x7FFFFFFF)
#define MAX_VERTICES 200

// Функция для поиска кратчайшего пути с помощью BFS
int bfs(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NOT_FOUND;

    int n, start, stop;
    if (fscanf(file, "%d", &n) != 1 || n <= 0) {
        fclose(file);
        return NOT_FOUND;
    }

    int* data = (int*)malloc(n * n * sizeof(int));
    if (!data) {
        fclose(file);
        return NOT_FOUND; // Проверка на успешное выделение памяти
    }

    // Чтение матрицы смежности
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (fscanf(file, "%d", &data[y * n + x]) != 1) {
                free(data);
                fclose(file);
                return NOT_FOUND;
            }
            if (y > x && data[y * n + x] != data[x * n + y]) {
                // Матрица не симметрична
                free(data);
                fclose(file);
                return NOT_FOUND;
            }
        }
    }

    // Чтение стартовой и конечной вершин
    if (fscanf(file, "%d %d", &start, &stop) != 2 || start < 0 || start >= n || stop < 0 || stop >= n) {
        free(data);
        fclose(file);
        return NOT_FOUND;
    }

    fclose(file);

    // Инициализация переменных для BFS
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int visited[MAX_VERTICES] = { 0 };
    int distances[MAX_VERTICES] = { 0 };

    // Построение графа
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            graph[y][x] = data[y * n + x];
        }
    }

    free(data); // Освобождение памяти, когда данные больше не нужны

    // Начальная установка
    queue[rear++] = start;
    visited[start] = 1;
    distances[start] = 0;

    // Основной цикл BFS
    while (front < rear) {
        int current = queue[front++];

        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (graph[current][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
                distances[neighbor] = distances[current] + 1;

                if (neighbor == stop) {
                    return distances[neighbor];
                }
            }
        }
    }

    return NOT_FOUND; // Если путь не найден
}

void bfs_invalid_filename() {
    const char* invalid_filename = "C:\\askjdnkaskld\\askdalksdkl\\text.txt";
    assert(bfs(invalid_filename) == NOT_FOUND);
}

void bfs_file_not_graph() {
    const char* not_graph = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\not_graph.txt";
    assert(bfs(not_graph) == NOT_FOUND);
}

void bfs_fscanf_no_one_n() {
    const char* no_one_n = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\no_one_n.txt";
    assert(bfs(no_one_n), NOT_FOUND);
}

void bfs_no_one_matrix() {
    const char* no_one_matrix = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\no_one_matrix.txt";
    assert(bfs(no_one_matrix) == NOT_FOUND);
}
 
void bfc_small_matrix_for_vertices() {
    const char* small_matrix = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\small_matrix.txt";
    assert(bfs(small_matrix) == NOT_FOUND);
}

void bfs_not_vertices() {
    const char* not_vertices = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\not_vertices.txt";
    assert(bfs(not_vertices) == NOT_FOUND);
}

void bfs_long_path_graph() {
    const char* long_path_graph = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\long_path_graph.txt";
    assert(bfs(long_path_graph) == 9);
}

void bfs_bad_start() {
    const char* bad_start = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\bad_start.txt";
    assert(bfs(bad_start) == NOT_FOUND);
}

void bfs_bad_end() {
    const char* bad_end = "C:\\учеба\\алгосы\\Algorithms2\\Algorithms2\\bad_end.txt";
    assert(bfs(bad_end) == NOT_FOUND);
}

void run_all_tests() {
    bfs_invalid_filename();
    bfs_file_not_graph();
    bfs_fscanf_no_one_n();
    bfs_no_one_matrix();
    bfc_small_matrix_for_vertices();
    bfs_not_vertices();
    bfs_long_path_graph();
    bfs_bad_start();
    bfs_bad_end();
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");

    run_all_tests();

    int result = bfs("long_path_graph.txt");
    if (result == NOT_FOUND) {
        fprintf(stderr, "The path was not found or an error occurred\n");
    }
    else {
        printf("Minimum length: %d\n", result);
    }
    return 0;
}
