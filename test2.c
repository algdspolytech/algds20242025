#include <stdio.h>
#include "lab2.h"
#include <locale.h>

void TestPathExists_no1();       // ���� ��� �������� ������������� ���� � �����
void TestPathExists_no2();       // ���� ��� �������� ������������� ���� � ����� � ���������� �����������
void TestPathDoesNotExist_no3(); // ���� ��� �������� ���������� ���� � �����
void TestSingleVertex_no4();     // ���� ��� �������� ����� � ����� ��������
void TestEmptyGraph_no5();       // ���� ��� �������� ������� �����
void TestPathWithMultipleEdges_no6(); // ���� ��� �������� ������������� ���� � ����������� ������
void TestCycleInGraph_no7();     // ���� ��� �������� ������������� ����� � �����
void TestDisconnectedGraph_no8(); // ���� ��� �������� ���������� ���� � ������������ �����
void TestSelfLoop_no9();         // ���� ��� �������� ������� ���������
void TestBidirectionalEdge_no10(); // ���� ��� �������� ������������� �����

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

// ���� 1: �������� ������������� ���� �� 0 �� 4 � ����� � 5 ��������� (��������� ��� ���� �� ����������)
void TestPathExists_no1() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 1, 4);
    
    printf("���� 1 (���������� ���� �� 0 �� 4): %s\n", depthFirstSearch(graph, 0, 4) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 2: �������� ������������� ���� �� 0 �� 5 � ����������� ���������� ����������
void TestPathExists_no2() {
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);

    // ���������, ��� ���� ����������
    printf("���� 2 (���������� ���� �� 0 �� 5): %s\n", depthFirstSearch(graph, 0, 5) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 3: �������� ���������� ���� �� 0 �� 3 � �����
void TestPathDoesNotExist_no3() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);

    // ���������, ��� ���� �� ����������
    printf("���� 3 (��� ���� �� 0 �� 3): %s\n", depthFirstSearch(graph, 0, 3) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 4: �������� ������������� ���� � �����, ���������� ������ ���� �������
void TestSingleVertex_no4() {
    Graph* graph = createGraph(1);

    // ���������, ��� ���� �� 0 �� 0 ���������� (���������)
    printf("���� 4 (���������� ���� �� 0 �� 0): %s\n", depthFirstSearch(graph, 0, 0) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 5: �������� ����� � 0 ��������� (������ ����)
void TestEmptyGraph_no5() {
    Graph* graph = createGraph(0);

    // ���� � ������ ����� �� ������ ������������
    printf("���� 5 (� ������ ����� ��� ����): %s\n", depthFirstSearch(graph, 0, 0) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 6: �������� ���� � ����������� ������
void TestPathWithMultipleEdges_no6() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 0, 2);

    // ���������, ��� ���� �� 0 �� 3 ����������
    printf("���� 6 (���������� ���� �� 0 �� 3 � ����������� ������): %s\n", depthFirstSearch(graph, 0, 3) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 7: �������� ������� ����� � �����
void TestCycleInGraph_no7() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0); // ����
    addEdge(graph, 2, 3);

    // ���������, ��� ���� ���������� �� 0 �� 3

    printf("���� 7 (���������� ���� �� 0 �� 3 � ����� � ������): %s\n", depthFirstSearch(graph, 0, 3) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 8: �������� ������������� �����
void TestDisconnectedGraph_no8() {
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);

    // ���������, ��� ���� �� 3 �� 4 �� ����������
    printf("���� 8 (��� ���� �� 3 �� 4 � ������������ �����): %s\n", depthFirstSearch(graph, 3, 4) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 9: �������� ���������
void TestSelfLoop_no9() {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 0); // ���������
    addEdge(graph, 0, 1);

    // ���������, ��� ���� �� 0 �� 1 ����������
    printf("���� 9 (���������� ���� �� 0 �� 1 � ���������): %s\n", depthFirstSearch(graph, 0, 1) ? "�������" : "�� �������");

    freeGraph(graph);
}

// ���� 10: �������� ������������� �����
void TestBidirectionalEdge_no10() {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 1); // ��������� ������������ �����
    addEdge(graph, 1, 0); 

    // ���������, ��� ���� �� 0 �� 1 ����������
    printf("���� 10 (���������� ���� �� 0 �� 1 � ������������ ������): %s\n", depthFirstSearch(graph, 0, 1) ? "�������" : "�� �������");

    freeGraph(graph);
}
