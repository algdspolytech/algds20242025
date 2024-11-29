#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Header.h"
#include <locale.h>
/// ���� 1: ������ ���� (0 ������)
void testEmptyGraph() {
    resetGraph();
    readGraphFromFile("empty_graph.txt"); // ���� ������ ��������� 0 ������
    assert(findHamiltonianPath() == 0);
}
// ���� 2: ���� � 1 �������� (����������� ���� ����������)
void testSingleVertexGraph() {
    resetGraph();
    readGraphFromFile("single_vertex_graph.txt"); // ���� ������ ��������� 1 �������
    assert(findHamiltonianPath() == 1);
}
// ���� 3: ���� � 2 ��������� � ����� ������
void testTwoVerticesWithEdge() {
    resetGraph();
    readGraphFromFile("two_vertices_with_edge.txt"); // ���� ������ ��������� 2 ������� � 1 �����
    assert(findHamiltonianPath() == 1);
}

// ���� 4: ���� � 2 ��������� ��� �����
void testTwoVerticesWithoutEdge() {
    resetGraph();
    readGraphFromFile("two_vertices_without_edge.txt"); // ���� ������ ��������� 2 ������� ��� ����
    assert(findHamiltonianPath() == 0);
}


// ���� 5: ���� � 3 ��������� � ������
void testThreeVerticesCycle() {
    resetGraph();
    readGraphFromFile("three_vertices_cycle.txt"); // ���� ������ ��������� 3 ������� � 3 ����, ���������� ����
    assert(findHamiltonianPath() == 1);
}

// ���� 6: ������ ���� � 4 ���������
void testCompleteGraphFourVertices() {
    resetGraph();
    readGraphFromFile("complete_graph_four_vertices.txt"); // ���� � 4 ��������� � ����� ������
    assert(findHamiltonianPath() == 1);
}
// ���� 7: ���� � 4 ���������, �� ������
void testNonCompleteGraphFourVertices() {
    resetGraph();
    readGraphFromFile("non_complete_graph_four_vertices.txt"); // ���� � 4 ���������, �� �� ��� ����
    assert(findHamiltonianPath() == 1);
}
// ���� 8: ���� � 5 ��������� � ������� �������
void testFiveVerticesMixedEdges() {
    resetGraph();
    readGraphFromFile("five_vertices_mixed_edges.txt"); // ���� � 5 ��������� � ������
    assert(findHamiltonianPath() == 1);
}

// ���� 10: ���� � 6 ���������, ������ ����
void testCycleGraphSixVertices() {
    resetGraph();
    readGraphFromFile("cycle_graph_six_vertices.txt"); // ���� � 6 ���������, ������ ����
    assert(findHamiltonianPath() == 1);
}


// ���� 11: ���� � 7 ���������, ����� ����
void testGraphSevenVertices() {
    resetGraph();
    readGraphFromFile("seven_vertices_graph.txt"); // ���� � 7 ��������� � ������
    assert(findHamiltonianPath() == 1);
}



// �������� ������� ��� ������� ������
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
    printf("��� ����� ������ �������.\n");
    return 0;
}