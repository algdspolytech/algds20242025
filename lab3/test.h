#pragma once 
#include <assert.h>
#include "lab3.h"

void ReadTxt_Filename_ReturnNode() {
	char* FileGraph = "lab3/graph.txt";
	int numVertices;
	node_t* AdjLists = ReadTxt(FileGraph, &numVertices);
	assert(AdjLists != NULL);
	Free_AdjLists(AdjLists, numVertices);
}

void ReadTxt_FilenameDoNotExist_ReturnNULL() {
	char* FileGraph = "lab3/graph0.txt";
	int numVertices;
	node_t* AdjLists = ReadTxt(FileGraph, &numVertices);
	assert(AdjLists == NULL);
}

void Create_Node_PositiveInteger_ReturnNode() {
	node_t* newNode = Create_Node(1);
	assert(newNode->vertex == 1);
	assert(newNode->next == NULL);
	free(newNode);
}

void Create_Node_NegativeInteger_ReturnNULL() {
	node_t* newNode = Create_Node(-1);
	assert(newNode == NULL);
}

void ReadGraph_Filename_ReturnGraph() {
	char* FileGraph = "lab3/graph.txt";
	graph_t* Graph = ReadGraph(FileGraph);
	assert(Graph->adjLists != NULL);
	assert(Graph->numVertices == 12);
	assert(Graph->visited[0] == 0);
	Free_Graph(Graph);
}

void ReadGraph_FilenameDoNotExist_ReturnNULL() {
	char* FileGraph = "lab3/graph0.txt";
	graph_t* Graph = ReadGraph(FileGraph);
	assert(Graph == NULL);
}

void Find_DFS_—onnectedVertices_Return1() {
	char* FileGraph = "lab3/graph.txt";
	graph_t* Graph = ReadGraph(FileGraph);
	int res = Find_DFS(Graph, 0, 4);
	assert(res == 1);
	Free_Graph(Graph);
}

void Find_DFS_Not—onnectedVertices_Return0() {
	char* FileGraph = "lab3/graph.txt";
	graph_t* Graph = ReadGraph(FileGraph);
	int res = Find_DFS(Graph, 0, 8);
	assert(res == 0);
	Free_Graph(Graph);
}

void Push_LinkedStack_Integer_returnValidVal() {
	list_t* p = NULL;
	p = Push_LinkedStack(p, 1);
	assert(p->data == 1);
	assert(p->next == NULL);
	p = Pop_LinkedStack(p);
}

void Pop_LinkedStack_NotEmptyStack_returnValidVal() {
	list_t* p = NULL;
	p = Push_LinkedStack(p, 1);
	p = Push_LinkedStack(p, 2);
	p = Pop_LinkedStack(p);
	assert(p->data == 1);
	assert(p->next == NULL);
	p = Pop_LinkedStack(p);
}

void Pop_LinkedStack_EmptyStack_returnNull() {
	list_t* p = NULL;
	p = Pop_LinkedStack(p);
	assert(p == NULL);
}

void Peek_LinkedStack_NotEmpty_returnInteger() {
	list_t* p = NULL;
	p = Push_LinkedStack(p, 1);
	assert(Peek_LinkedStack(p) == 1);
	p = Pop_LinkedStack(p);
}

void Peek_LinkedStack_Empty_returnERROR() {
	list_t* p = NULL;
	assert(Peek_LinkedStack(p) == ERROR);
}

void test() {
	ReadTxt_Filename_ReturnNode();
	ReadTxt_FilenameDoNotExist_ReturnNULL();
	Create_Node_PositiveInteger_ReturnNode();
	Create_Node_NegativeInteger_ReturnNULL();
	ReadGraph_Filename_ReturnGraph();
	ReadGraph_FilenameDoNotExist_ReturnNULL();
	Find_DFS_—onnectedVertices_Return1();
	Find_DFS_Not—onnectedVertices_Return0();
	Push_LinkedStack_Integer_returnValidVal();
	Pop_LinkedStack_NotEmptyStack_returnValidVal();
	Pop_LinkedStack_EmptyStack_returnNull();
	Peek_LinkedStack_NotEmpty_returnInteger();
	Peek_LinkedStack_Empty_returnERROR();
}