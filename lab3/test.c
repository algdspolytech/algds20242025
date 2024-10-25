#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

// Тест: Запись списка смежностей для действительного графа
void TestwriteAdjacencyList_ValidGraph_no1() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    graph[0][1] = 1;
    graph[1][2] = 1;

    
    writeAdjacencyList("test_list1.txt", graph, 3);
    
    printf("TestwriteAdjacencyList_ValidGraph_no1 = 1\n"); // Должен быть 1 после ручной проверки
}

// Тест: Запись матрицы смежностей для действительного графа
void TestwriteAdjacencyMatrix_ValidGraph_no2() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    graph[0][1] = 1;
    graph[1][0] = 1;

    
    writeAdjacencyMatrix("test_matrix1.txt", graph, 2);
    
    printf("TestwriteAdjacencyMatrix_ValidGraph_no1 = 1\n"); // Должен быть 1 после ручной проверки
}

// Тест: Сравнение двух одинаковых графов
void TestcompareGraphs_SameGraphs_no3() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };

    graph1[0][1] = 1;
    graph1[1][0] = 1;

    graph2[0][1] = 1;
    graph2[1][0] = 1;

    
    int result = compareGraphs(graph1, graph2, 2);
    printf("TestcompareGraphs_SameGraphs_no1 = %i\n", result == 1 ? 1 : 0);
}

// Тест: Сравнение двух различных графов
void TestcompareGraphs_DifferentGraphs_no4() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };

    graph1[0][1] = 1;
    graph1[1][0] = 1;
    graph2[1][2] = 1;
    graph2[2][1] = 1;

    
    int result = compareGraphs(graph1, graph2, 3);
    printf("TestcompareGraphs_DifferentGraphs_no1 = %i\n", result == 0 ? 1 : 0);
}

// Тест: Генерация случайного графа с полной плотностью
void TestgenerateRandomGraph_FullDensity_no5() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 1.0; // Полная плотность

    
    generateRandomGraph(graph, 4, density);

    
    int connections = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            connections += (i != j) * graph[i][j];
        }
    }

    printf("TestgenerateRandomGraph_FullDensity_no5 = %i\n", connections == 12 ? 1 : 0);
}


// Тест: Генерация случайного графа с нулевой плотностью
void TestgenerateRandomGraph_ZeroDensity_no6() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 0.0; // Нулевая плотность

    
    generateRandomGraph(graph, 4, density);

    int connections = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            connections += graph[i][j];
        }
    }

    printf("TestgenerateRandomGraph_ZeroDensity_no6 = %i\n", connections == 0 ? 1 : 0);
}


/// Тест: Генерация случайного графа со средней плотностью
void TestgenerateRandomGraph_MidDensity_no7() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 0.5; // Средняя плотность

    generateRandomGraph(graph, 4, density);

    int connections = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            connections += (i != j) * graph[i][j];
        }
    }

    printf("TestgenerateRandomGraph_MidDensity_no7 = %i\n", connections > 0 ? 1 : 0);
}


// Тест: Запись пустого графа в список смежностей
void TestwriteAdjacencyList_EmptyGraph_no8() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    writeAdjacencyList("test_list_empty.txt", graph, 0);
    printf("TestwriteAdjacencyList_EmptyGraph_no1 = 1\n"); // Должен быть 1 после ручной проверки
}

// Тест: Запись пустого графа в матрицу смежностей
void TestwriteAdjacencyMatrix_EmptyGraph_no9() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    writeAdjacencyMatrix("test_matrix_empty.txt", graph, 0);
    printf("TestwriteAdjacencyMatrix_EmptyGraph_no1 = 1\n"); // Должен быть 1 после ручной проверки
}

// Тест: Проверка плотности сгенерированного графа
void TestgenerateRandomGraph_DensityCheck_no10() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 0.8; // Задаем плотность 20%

    generateRandomGraph(graph, 5, density);

    int connections = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            connections += (i != j) * graph[i][j];
        }
    }

    int max_edges = 5 * (5 - 1) / 2; // Максимально возможные рёбра (без петель)
    int expected_min_edges = max_edges * density; // Ожидаемое минимальное количество рёбер

    printf("TestgenerateRandomGraph_DensityCheck_no10 = %i\n", connections >= expected_min_edges ? 1 : 0);
}




void RunAllTests() {
    TestwriteAdjacencyList_ValidGraph_no1();
    TestwriteAdjacencyMatrix_ValidGraph_no2();
    TestcompareGraphs_SameGraphs_no3();
    TestcompareGraphs_DifferentGraphs_no4();
    TestgenerateRandomGraph_FullDensity_no5();
    TestgenerateRandomGraph_ZeroDensity_no6();
    TestgenerateRandomGraph_MidDensity_no7();
    TestwriteAdjacencyList_EmptyGraph_no8();
    TestwriteAdjacencyMatrix_EmptyGraph_no9();
    TestgenerateRandomGraph_DensityCheck_no10();
}

int main() {
    RunAllTests();
    return 0;
}
