#include <stdio.h>
#include <assert.h>
//#include "graph.h"  // Заголовочный файл с функциями is_path_exists и dfs

#define MAX_NODES 100  // Максимальное количество вершин

// Функция DFS для проверки пути между вершинами
void dfs(int graph[MAX_NODES][MAX_NODES], int visited[], int n, int node) {
    //printf("%d \n", node);
    visited[node] = 1;  // Помечаем вершину как посещенную
    for (int i = 0; i < n; i++) {
        if (graph[node][i] == 1 && !visited[i]) {
            //for (int i = 0; i < 5; i++) printf("%d ", visited[i]);
            //printf("\n");
            dfs(graph, visited, n, i);
        }
    }
    //printf("%d ", 555);
}

// Функция для проверки существования пути между двумя вершинами
int is_path_exists(int graph[MAX_NODES][MAX_NODES], int size, int start, int end) {
    int visited[MAX_NODES] = { 0 };
    //for (int i = 0; i < size; i++) printf("%d ", visited[i]);
    //printf("\n");
    //printf("Запуск DFS из вершины %d в %d\n", start, end);
    //printf("%d ", visited[0]);
    dfs(graph, visited, size, start);
    printf("Финальный visited: ");
    for (int i = 0; i < size; i++) printf("%d ", visited[i]);
    printf("\n");
    return visited[end];
}

void test_graph() {
    int graph1[5][5] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };

    int graph2[4][4] = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    };

    int graph3[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    int graph4[2][2] = {
        {0, 1},
        {1, 0}
    };

    //for (int i = 0; i < 5; i++) {
    //    for (int j = 0; j < 5; j++) {
    //        printf("%d ", graph1[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");

    // Test_no1: Path exists (simple connectivity)
    assert(is_path_exists(graph1, 5, 0, 3) == 1);

    // Test_no2: There is no path (disconnected graph)
    assert(is_path_exists(graph3, 3, 0, 2) == 0);

    // Test_no3: The path to oneself (always exists)
    assert(is_path_exists(graph1, 5, 2, 2) == 1);

    // Test_no4: Path in a small graph
    assert(is_path_exists(graph4, 2, 0, 1) == 1);

    // Test_no5: Broken components (isolated vertices)
    assert(is_path_exists(graph2, 4, 0, 3) == 0);

    // Test_no6: Path along one edge
    assert(is_path_exists(graph1, 5, 0, 1) == 1);

    // Test_no7: A long way through several peaks
    assert(is_path_exists(graph1, 5, 0, 3) == 1);

    // Test_no8: Cycle (graph with loops)
    assert(is_path_exists(graph1, 5, 3, 3) == 1);

    // Test_no9: Graph with one node
    int graph5[1][1] = { {0} };
    assert(is_path_exists(graph5, 1, 0, 0) == 1);

    // Test_no10: Large connected graph (10 vertices)
    int graph6[10][10] = { 0 };
    for (int i = 0; i < 9; i++) {
        graph6[i][i + 2] = 1;
        graph6[i + 1][i] = 1;
    }
    assert(is_path_exists(graph6, 10, 0, 5) == 1);

    printf("Все тесты успешно пройдены!\n");
}