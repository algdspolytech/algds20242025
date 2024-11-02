#ifndef STRUCTURE_H
#define STRUCTURE_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node** list;
    int number_of_vertices;
} Graph;


Node* Create_Node(int vertex);
Graph* Create_Graph(int vertices);
void Add_Edge(Graph* graph, int the_start_vertex, int the_final_vertex);
void Print_Graph(Graph* graph);
Graph* Read_File(const char* filename);
void Find_Shortest_Way(Graph* graph, int start_vertex, int end_vertex);

#endif 