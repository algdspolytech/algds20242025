#include <assert.h>
#include <stdio.h>
#include<locale.h>
#include "structure.h"


void test_СreateNode_Valid_Vertex() {

    Node* node = Create_Node(4);
    assert(node != NULL);
    assert(node->vertex == 4);

    free(node);
}

void test_Сreate_Graph_Valid_Vertices() {

    Graph* graph = Create_Graph(4);

    assert(graph != NULL);
    assert(graph->number_of_vertices == 4);
    
    for (int i = 0; i < graph->number_of_vertices; i++) {
        assert(graph->list[i] == NULL);
    }
    free(graph);
}

void test_Add_Edge_Valid_Edge() {

    Graph* graph = Create_Graph(3);
    Add_Edge(graph, 0, 1);

    assert(graph->list[0] != NULL);
    assert(graph->list[0]->vertex == 1);

    assert(graph->list[1] != NULL);
    assert(graph->list[1]->vertex == 0);

    free(graph);
}


void test_Read_File() {

    Graph* graph = Read_File("graph.txt");

    assert(graph != NULL);
    assert(graph->number_of_vertices == 5);

    free(graph);
}

void test_Find_Shortest_Way() {

    Graph* graph = Create_Graph(4);

    Add_Edge(graph, 0, 1);
    Add_Edge(graph, 1, 2);

    int start_vertex = 0;
    int end_vertex = 2;

    Find_Shortest_Way(graph, start_vertex, end_vertex);

    free(graph);
}

void test_Find_Shortest_No_Way() {

    Graph* graph = Create_Graph(4);

    int start_vertex = 0;
    int end_vertex = 4;

    Find_Shortest_Way(graph, start_vertex, end_vertex);

    free(graph);
}


void test_Create_Graph_Null() {

    Graph* graph = Create_Graph(0);

    assert(graph != NULL);
    assert(graph->number_of_vertices == 0);

    free(graph);
}

void test_Add_Edge_Duplicate_Edge() {

    Graph* graph = Create_Graph(3);

    Add_Edge(graph, 0, 1);
    Add_Edge(graph, 0, 1); 

    int count = 0;

    Node* temp = graph->list[0];

    while (temp) {
        count++;
        temp = temp->next;
    }
    assert(count == 1);

    free(graph);
}

void test_Create_Node_Invalid_Vertex() {

    Node* node = Create_Node(-1);
    assert(node != NULL);
    assert(node->vertex == -1);

    free(node);
}

void test_Find_Shortest_Way_Starting_At_End() {

    Graph* graph = Create_Graph(2);
    Add_Edge(graph, 0, 1);
    int start_vertex = 1;
    int end_vertex = 0;

    Find_Shortest_Way(graph, start_vertex, end_vertex);

    free(graph);
}

int main() {

    setlocale(LC_CTYPE, "Russian");
    test_СreateNode_Valid_Vertex();
    test_Сreate_Graph_Valid_Vertices();
    test_Add_Edge_Valid_Edge();
    test_Read_File();
    test_Find_Shortest_Way();
    test_Find_Shortest_No_Way();
    test_Create_Graph_Null();
    test_Add_Edge_Duplicate_Edge();
    test_Create_Node_Invalid_Vertex();
    test_Find_Shortest_Way_Starting_At_End();

    return 0;
}