#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "lab3.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	test();
	printf("Test succeeded\n");
	getchar();
	getchar();
	return 0;
}

int Find_DFS(graph_t* Graph, int v1, int v2){
	int i = v1;
	list_t* p = NULL;                           //stack 
	node_t* adj_list;
	do {
		p = Pop_LinkedStack(p);
		if (Graph->visited[i] == 0) {
			adj_list = &(Graph->adjLists[i]);   //we consider adjacent vertices
			Graph->visited[i] = 1;                     //1 - visited, 0 - not visited
			while (adj_list != NULL) {
				if (Graph->visited[adj_list->vertex] == 0) {
					p = Push_LinkedStack(p, adj_list->vertex);
				}
				adj_list = adj_list->next;
			}
		}
		i = Peek_LinkedStack(p);
	} while (i != ERROR);
	
	return Graph->visited[v2] == 0 ? 0 : 1;
}

graph_t* ReadGraph(char const* filename) {
	graph_t* Graph = (graph_t*)malloc(sizeof(graph_t));
	Graph->adjLists = ReadTxt(filename, &(Graph->numVertices));

	if (Graph->adjLists == NULL) {
		free(Graph);
		return NULL;
	}

	Graph->visited = (int*)malloc(Graph->numVertices * sizeof(int));
	for (int i = 0; i < Graph->numVertices; i++) {
		Graph->visited[i] = 0;
	}
	return Graph;
}

node_t* Create_Node(int vertex) {
	if (vertex < 0)
		return NULL;
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->vertex = vertex;
	node->next = NULL;
	return node;
}

node_t* ReadTxt(char const* filename, int* numVertices) {
	*numVertices = 0;
	FILE* ptrtxt = fopen(filename, "r");

	if (ptrtxt == NULL) {
		printf("Error: file pointer is null.\n");
		return NULL;
		//exit(1);
	}
	
	*numVertices = 1;
	node_t* AdjLists = (node_t*)malloc(*numVertices * sizeof(node_t));    //memory allocation
	
	digit_t digit = Read_Number(ptrtxt);
	node_t* temp;
	while (digit.next_symbol != EOF) {
		if (digit.d >= *numVertices) {
			(*numVertices) = digit.d + 1;
			AdjLists = realloc(AdjLists, *numVertices * sizeof(node_t));
		}
		temp = &AdjLists[digit.d];
		digit = Read_Number(ptrtxt);
		if (digit.next_symbol == '\n') {
			temp->vertex = digit.d;
			temp->next = NULL;
			digit = Read_Number(ptrtxt);
			continue;
		}
		temp->vertex = digit.d;
		temp->next = NULL;
		do {
			digit = Read_Number(ptrtxt);
			temp->next = Create_Node(digit.d);
			temp = temp->next;
		} while (digit.next_symbol != '\n');
		digit = Read_Number(ptrtxt);
	}
	fclose(ptrtxt);
	return AdjLists;
}

void Print_AdjLists(node_t* AdjLists, int numVertices) {
	node_t* temp;
	for (int i = 0; i < numVertices; i++) {
		temp = &AdjLists[i];
		printf("%d : ", i);
		do {
			printf("%d ", temp->vertex);
			temp = temp->next;
		} while (temp != NULL);
		printf("\n");
	}
	printf("\n");
}

list_t* Push_LinkedStack(list_t* p, int data) {
	list_t* t = (list_t*)malloc(sizeof(list_t));
	if (t == NULL) {
		free(t);
		printf("MEMORY ALLOCATION ERROR\n");
		return p;
	}
	list_t* a = t;
	a->data = data;
	a->next = p;
	return a;
}

list_t* Pop_LinkedStack(list_t* p) {
	if (p == NULL) {
		//printf("There are no more elements\n");
		return NULL;
	}
	list_t* p1 = p->next;
	free(p);
	return p1;
}

int Peek_LinkedStack(list_t* p) {
	if (p == NULL)
		return ERROR;             
	return p->data;
}

digit_t Read_Number(FILE* ptrtxt) {
	char c = '0';
	do {
		c = fgetc(ptrtxt);
		if (c == EOF)
			return (digit_t) { INT_MIN, c };
	} while (c == ' ');
	int res = 0;
	do {
		res = res * 10 + (c - '0');
		c = fgetc(ptrtxt);
	} while (c != ' ' && c != '\n' && c != EOF);
	return (digit_t) { res, c };
}

void Free_AdjLists(node_t* adjLists, int numVertices) {
	node_t* temp1;
	node_t* temp2;
	for (int i = numVertices-1; i >= 0; i--) {
		temp1 = adjLists[i].next;
		while (temp1 != NULL) {
			temp2 = temp1->next;
			free(temp1);
			temp1 = temp2;
		}
	}
	free(adjLists);
}

void Free_Graph(graph_t* Graph) {
	free(Graph->visited);
	Free_AdjLists(Graph->adjLists, Graph->numVertices);
	free(Graph);
}