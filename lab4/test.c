#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Header.h"
#include <locale.h>
/// Тест 1: Пустой граф (0 вершин)
void testEmptyGraph() {
    resetGraph();
    readGraphFromFile("empty_graph.txt"); // Файл должен содержать 0 вершин
    assert(findHamiltonianPath() == 0);
}
// Тест 2: Граф с 1 вершиной (гамильтонов путь существует)
void testSingleVertexGraph() {
    resetGraph();
    readGraphFromFile("single_vertex_graph.txt"); // Файл должен содержать 1 вершину
    assert(findHamiltonianPath() == 1);
}
// Тест 3: Граф с 2 вершинами и одним ребром
void testTwoVerticesWithEdge() {
    resetGraph();
    readGraphFromFile("two_vertices_with_edge.txt"); // Файл должен содержать 2 вершины и 1 ребро
    assert(findHamiltonianPath() == 1);
}

// Тест 4: Граф с 2 вершинами без ребра
void testTwoVerticesWithoutEdge() {
    resetGraph();
    readGraphFromFile("two_vertices_without_edge.txt"); // Файл должен содержать 2 вершины без рёбер
    assert(findHamiltonianPath() == 0);
}


// Тест 5: Граф с 3 вершинами и циклом
void testThreeVerticesCycle() {
    resetGraph();
    readGraphFromFile("three_vertices_cycle.txt"); // Файл должен содержать 3 вершины и 3 рёбра, образующие цикл
    assert(findHamiltonianPath() == 1);
}

// Тест 6: Полный граф с 4 вершинами
void testCompleteGraphFourVertices() {
    resetGraph();
    readGraphFromFile("complete_graph_four_vertices.txt"); // Файл с 4 вершинами и всеми рёбрами
    assert(findHamiltonianPath() == 1);
}
// Тест 7: Граф с 4 вершинами, не полный
void testNonCompleteGraphFourVertices() {
    resetGraph();
    readGraphFromFile("non_complete_graph_four_vertices.txt"); // Файл с 4 вершинами, но не все рёбра
    assert(findHamiltonianPath() == 1);
}
// Тест 8: Граф с 5 вершинами и разными связями
void testFiveVerticesMixedEdges() {
    resetGraph();
    readGraphFromFile("five_vertices_mixed_edges.txt"); // Файл с 5 вершинами и рёбрами
    assert(findHamiltonianPath() == 1);
}

// Тест 10: Граф с 6 вершинами, полный цикл
void testCycleGraphSixVertices() {
    resetGraph();
    readGraphFromFile("cycle_graph_six_vertices.txt"); // Файл с 6 вершинами, полный цикл
    assert(findHamiltonianPath() == 1);
}


// Тест 11: Граф с 7 вершинами, много рёбер
void testGraphSevenVertices() {
    resetGraph();
    readGraphFromFile("seven_vertices_graph.txt"); // Файл с 7 вершинами и рёбрами
    assert(findHamiltonianPath() == 1);
}



// Основная функция для запуска тестов
int main() {
    setlocale(LC_CTYPE, "Russian");
    testEmptyGraph();
    testSingleVertexGraph();
    testTwoVerticesWithEdge();
    testTwoVerticesWithoutEdge();
    testThreeVerticesCycle();
    testCompleteGraphFourVertices();
    testNonCompleteGraphFourVertices();
    testFiveVerticesMixedEdges();
    testCycleGraphSixVertices();
    testGraphSevenVertices();
    printf("Все тесты прошли успешно.\n");
    return 0;
}