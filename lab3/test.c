#include <assert.h>
#include <stdio.h>
#include "graph.h"
#include<locale.h>

// ���� ��� ������� createNode
void test_createNode_ValidVertex_returnValidVal() {
    Node* node = createNode(5);
    assert(node != NULL);
    assert(node->vertex == 5);
    free(node);
    printf("test_createNode_ValidVertex_returnValidVal: PASSED\n");
}

// ���� ��� ������� createGraph
void test_createGraph_ValidVertices_returnValidVal() {
    Graph* graph = createGraph(5);
    assert(graph != NULL);
    assert(graph->numVertices == 5);
    for (int i = 0; i < graph->numVertices; i++) {
        assert(graph->adjLists[i] == NULL);
    }
    free(graph);
    printf("test_createGraph_ValidVertices_returnValidVal: PASSED\n");
}

// ���� ��� ������� addEdge
void test_addEdge_ValidEdge_returnValidVal() {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);

    assert(graph->adjLists[0] != NULL);
    assert(graph->adjLists[0]->vertex == 1);

    assert(graph->adjLists[1] != NULL);
    assert(graph->adjLists[1]->vertex == 0);

    free(graph);
    printf("test_addEdge_ValidEdge_returnValidVal: PASSED\n");
}


// ���� ��� ������� readGraphFromFile
void test_readGraphFromFile_ValidFile_returnValidVal() {
    Graph* graph = readGraphFromFile("graph.txt");
    assert(graph != NULL);
    assert(graph->numVertices == 5);
    free(graph);
    printf("test_readGraphFromFile_ValidFile_returnValidVal: PASSED\n");
}

// ���� ��� ������� findShortestPath (���� ����������)
void test_findShortestPath_ExistingPath_returnValidVal() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    int startVertex = 0;
    int endVertex = 2;

    // ��������� ������� ��� ������
    findShortestPath(graph, startVertex, endVertex);

    free(graph);
    printf("test_findShortestPath_ExistingPath_returnValidVal: PASSED\n");
}

// ���� ��� ������� findShortestPath (���� �� ����������)
void test_findShortestPath_NonExistingPath_returnValidVal() {
    Graph* graph = createGraph(5);
    int startVertex = 0;
    int endVertex = 4;

    // ��������� ������� ��� ������
    findShortestPath(graph, startVertex, endVertex);

    free(graph);
    printf("test_findShortestPath_NonExistingPath_returnValidVal: PASSED\n");
}

// ���� ��� ������� addEdge �� ����������������� ����
void test_addEdge_UndirectedGraph_returnValidVal() {
    Graph* graph = createGraph(3);
    addEdge(graph, 1, 2);

    assert(graph->adjLists[1] != NULL);
    assert(graph->adjLists[1]->vertex == 2);

    assert(graph->adjLists[2] != NULL);
    assert(graph->adjLists[2]->vertex == 1);

    free(graph);
    printf("test_addEdge_UndirectedGraph_returnValidVal: PASSED\n");
}

// ���� ��� ������� createGraph � �������� ���������
void test_createGraph_ZeroVertices_returnValidVal() {
    Graph* graph = createGraph(0);
    assert(graph != NULL);
    assert(graph->numVertices == 0);
    free(graph);
    printf("test_createGraph_ZeroVertices_returnValidVal: PASSED\n");
}

// ���� ��� ������� addEdge � ����������� ������
void test_addEdge_DuplicateEdge_returnValidVal() {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 1); // ��������� ��������

    int count = 0;
    Node* temp = graph->adjLists[0];
    while (temp) {
        count++;
        temp = temp->next;
    }
    assert(count == 1); // ������� ������ ���� �����
    free(graph);
    printf("test_addEdge_DuplicateEdge_returnValidVal: PASSED\n");
}

// ���� ��� ������� readGraphFromFile_EmptyFile
void test_readGraphFromFile_EmptyFile_returnNull() {
    Graph* graph = readGraphFromFile("empty_graph.txt"); // ��������������, ��� ���� ����
    assert(graph == NULL);
    printf("test_readGraphFromFile_EmptyFile_returnNull: PASSED\n");
}

// ���� ��� ������� createNode_InvalidVertex_returnNull
void test_createNode_InvalidVertex_returnsValidVal() {
    Node* node = createNode(-1);
    assert(node != NULL);
    assert(node->vertex == -1);
    free(node);
    printf("test_createNode_InvalidVertex_returnsValidVal: PASSED\n");
}

// ���� ��� ������� addEdge_SelfLoop_returnValidVal
void test_addEdge_SelfLoop_returnValidVal() {
    Graph* graph = createGraph(2);
    addEdge(graph, 0, 0); // ��������� �����
    assert(graph->adjLists[0] != NULL);
    assert(graph->adjLists[0]->vertex == 0);
    free(graph);
    printf("test_addEdge_SelfLoop_returnValidVal: PASSED\n");
}


// ���� ��� ������� findShortestPath_StartingAtEnd_returnValidVal
void test_findShortestPath_StartingAtEnd_returnValidVal() {
    Graph* graph = createGraph(2);
    addEdge(graph, 0, 1);
    int startVertex = 1;
    int endVertex = 0;

    // ��������� ������� ��� ������
    findShortestPath(graph, startVertex, endVertex);

    free(graph);
    printf("test_findShortestPath_StartingAtEnd_returnValidVal: PASSED\n");
}

int main() {
    // ������ ���� ������
    setlocale(LC_CTYPE, "Russian");
    test_createNode_ValidVertex_returnValidVal();
    test_createGraph_ValidVertices_returnValidVal();
    test_addEdge_ValidEdge_returnValidVal();
    test_readGraphFromFile_ValidFile_returnValidVal();
    test_findShortestPath_ExistingPath_returnValidVal();
    test_findShortestPath_NonExistingPath_returnValidVal();
    test_addEdge_UndirectedGraph_returnValidVal();
    test_createGraph_ZeroVertices_returnValidVal();
    test_readGraphFromFile_EmptyFile_returnNull();
    test_createNode_InvalidVertex_returnsValidVal();
    test_addEdge_SelfLoop_returnValidVal();
    test_findShortestPath_StartingAtEnd_returnValidVal();

    return 0;
}
