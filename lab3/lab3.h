#pragma once

#include <limits.h>
#define ERROR INT_MIN
#define num_of_digits(INT_MAX) 10

typedef struct node_t{
	int vertex;
	struct node_t* next;
} node_t;

typedef struct {
	int numVertices;
	int* visited;
	node_t* adjLists;
} graph_t;

typedef struct list_t {
	int data;
	struct list_t* next;
} list_t;

typedef struct {
	int d;
	char next_symbol;
}digit_t;

node_t* ReadTxt(char const* filename);
node_t* Create_Node(int vertex);
void Print_AdjLists(node_t* AdjLists);
graph_t* ReadGraph(char const* filename);
int Find_DFS(graph_t* Grahp, int v1, int v2);
list_t* Push_LinkedStack(list_t* p, int data);
list_t* Pop_LinkedStack(list_t* p);
int Peek_LinkedStack(list_t* p);
digit_t Read_Number(FILE* ptrtxt);
void Free_AdjLists(node_t* adjLists, int numVertices);
void Free_Graph(graph_t* Graph);