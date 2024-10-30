#include <stdio.h>
#include "lab2.h"
#include <locale.h>

void TestPathExists_no1();       // Тест для проверки существования пути в графе
void TestPathExists_no2();       // Тест для проверки существования пути в графе с различными ветвлениями
void TestPathDoesNotExist_no3(); // Тест для проверки отсутствия пути в графе
void TestSingleVertex_no4();     // Тест для проверки графа с одной вершиной
void TestEmptyGraph_no5();       // Тест для проверки пустого графа
void TestPathWithMultipleEdges_no6(); // Тест для проверки существования пути с несколькими рёбрами
void TestCycleInGraph_no7();     // Тест для проверки существования цикла в графе
void TestDisconnectedGraph_no8(); // Тест для проверки отсутствия пути в несоединённом графе
void TestSelfLoop_no9();         // Тест для проверки наличия самопетли
void TestBidirectionalEdge_no10(); // Тест для проверки двустороннего ребра

int main() {
    
    setlocale(LC_ALL, "Rus");
    TestPathExists_no1();
    TestPathExists_no2();
    TestPathDoesNotExist_no3();
    TestSingleVertex_no4();
    TestEmptyGraph_no5();
    TestPathWithMultipleEdges_no6();
    TestCycleInGraph_no7();
    TestDisconnectedGraph_no8();
    TestSelfLoop_no9();
    TestBidirectionalEdge_no10();

    return 0;
}

// Тест 1: Проверка существования пути от 0 до 4 в графе с 5 вершинами (ожидается что путь не существует)
void TestPathExists_no1() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 1, 4);
    
    printf("Тест 1 (Существует путь от 0 до 4): %s\n", depthFirstSearch(graph, 0, 4) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 2: Проверка существования пути от 0 до 5 с несколькими возможными маршрутами
void TestPathExists_no2() {
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);

    // Ожидается, что путь существует
    printf("Тест 2 (Существует путь от 0 до 5): %s\n", depthFirstSearch(graph, 0, 5) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 3: Проверка отсутствия пути от 0 до 3 в графе
void TestPathDoesNotExist_no3() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);

    // Ожидается, что путь не существует
    printf("Тест 3 (Нет пути от 0 до 3): %s\n", depthFirstSearch(graph, 0, 3) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 4: Проверка существования пути в графе, содержащем только одну вершину
void TestSingleVertex_no4() {
    Graph* graph = createGraph(1);

    // Ожидается, что путь от 0 до 0 существует (самопетля)
    printf("Тест 4 (Существует путь от 0 до 0): %s\n", depthFirstSearch(graph, 0, 0) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 5: Проверка графа с 0 вершинами (пустой граф)
void TestEmptyGraph_no5() {
    Graph* graph = createGraph(0);

    // Путь в пустом графе не должен существовать
    printf("Тест 5 (В пустом графе нет пути): %s\n", depthFirstSearch(graph, 0, 0) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 6: Проверка пути с несколькими рёбрами
void TestPathWithMultipleEdges_no6() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 0, 2);

    // Ожидается, что путь от 0 до 3 существует
    printf("Тест 6 (Существует путь от 0 до 3 с несколькими рёбрами): %s\n", depthFirstSearch(graph, 0, 3) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 7: Проверка наличия цикла в графе
void TestCycleInGraph_no7() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0); // Цикл
    addEdge(graph, 2, 3);

    // Ожидается, что путь существует от 0 до 3

    printf("Тест 7 (Существует путь от 0 до 3 в графе с циклом): %s\n", depthFirstSearch(graph, 0, 3) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 8: Проверка несоединённого графа
void TestDisconnectedGraph_no8() {
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);

    // Ожидается, что пути от 3 до 4 не существует
    printf("Тест 8 (Нет пути от 3 до 4 в несоединённом графе): %s\n", depthFirstSearch(graph, 3, 4) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 9: Проверка самопетли
void TestSelfLoop_no9() {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 0); // Самопетля
    addEdge(graph, 0, 1);

    // Ожидается, что путь от 0 до 1 существует
    printf("Тест 9 (Существует путь от 0 до 1 с самопетлёй): %s\n", depthFirstSearch(graph, 0, 1) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}

// Тест 10: Проверка двустороннего ребра
void TestBidirectionalEdge_no10() {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 1); // Добавляем двустороннее ребро
    addEdge(graph, 1, 0); 

    // Ожидается, что путь от 0 до 1 существует
    printf("Тест 10 (Существует путь от 0 до 1 с двусторонним ребром): %s\n", depthFirstSearch(graph, 0, 1) ? "Пройден" : "Не пройден");

    freeGraph(graph);
}
