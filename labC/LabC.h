#pragma once

typedef struct Node
{
	int vertex;
	struct Node* next;
}Node;

typedef struct Graf
{
	Node** List;
	int num_vertex;
}Graf;

typedef struct Queue
{
	int* data;
	int startQueue;
	int endQueue;
}Queue;

Node* createNode(int vertex);
Queue* createQueue(int num_vertex);
Queue* addQueue(Queue* queue, int value);
Queue* deleteQueue(Queue* queue);
Queue* freeQueue(Queue* queue);
Graf* createGraf(int num_vertex);
Graf* freeGraf(Graf* graf);
void addEdge(Graf* graf, int vertex, int linkedNode);
void printGraf(struct Graf* graf);
Graf* ReadFile(const char* filename);
int BFS(Graf* graf, int start, int end);
