#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include "LabC.h"

Node* createNode(int vertex)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;
}

Queue* createQueue(int num_vertex)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->data = (int*)malloc(sizeof(int) * num_vertex);
	queue->startQueue = 0;
	queue->endQueue = 0;
	return queue;
}

Queue* addQueue(Queue* queue, int value)
{
	queue->data[queue->endQueue++] = value;
	return queue;
}

Queue* deleteQueue(Queue* queue)
{
	queue->startQueue++;
	return queue;
}

Queue* freeQueue(Queue* queue)
{
	free(queue->data);
	free(queue);
	return NULL;
}

Graf* createGraf(int num_vertex)
{
	Graf* graf = (Graf*)malloc(sizeof(Graf));
	graf->List = (Node**)malloc(sizeof(Node*) * num_vertex);
	graf->num_vertex = num_vertex;
	for (int i = 0; i < num_vertex; i++)
	{
		graf->List[i] = NULL;
	}
	return graf;
}

Graf* freeGraf(Graf* graf)
{
	for (int i = 0; i < graf->num_vertex; i++)
	{
		Node* temp = graf->List[i];
		while (temp)
		{
			Node* temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
	}
	free(graf->List);
	free(graf);
	return NULL;
}



void addEdge(Graf* graf, int vertex, int linkedNode)
{
	Node* newNode = createNode(vertex);
	newNode->next = graf->List[linkedNode];
	graf->List[linkedNode] = newNode;

	newNode = createNode(linkedNode);
	newNode->next = graf->List[vertex];
	graf->List[vertex] = newNode;
}

void printGraf(struct Graf* graf)
{
	for (int i = 0; i < graf->num_vertex; i++)
	{
		Node* temp = graf->List[i];
		printf("\n Adjacency list of vertex %d\n ", i);
		while (temp)
		{
			printf("%d -> ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}

Graf* ReadFile(const char* filename)
{
	setlocale(LC_ALL, "Rus");
	FILE* file = fopen(filename, "r");
	if (!file)
	{
		printf("Ошибка открытия файла.\n");
		return NULL;
	}

	int num_vertex;
	fscanf_s(file, "%d", &num_vertex);
	Graf* graf = createGraf(num_vertex);
	int vertex, linkedNode;

	while (fscanf_s(file, "%d %d", &vertex, &linkedNode) != EOF) {
		addEdge(graf, vertex, linkedNode);
	}

	fclose(file);
	return graf;
}


int BFS(Graf* graf, int start, int end)
{
	setlocale(LC_ALL, "Rus");
	int* flag = (int*)malloc(sizeof(int) * graf->num_vertex);
	int* dist = (int*)malloc(sizeof(int) * graf->num_vertex);
	for (int i = 0; i < graf->num_vertex; i++)
	{
		flag[i] = 0;
		dist[i] = INT_MAX;
	}
	Queue* queue = createQueue(graf->num_vertex);
	dist[start] = 0;
	flag[start] = 1;
	queue = addQueue(queue, start);
	while (queue->startQueue != queue->endQueue)
	{
		int vertex = queue->data[queue->startQueue];
		queue = deleteQueue(queue);
		Node* temp = graf->List[vertex];
		while (temp)
		{
			if (flag[temp->vertex] == 0)
			{
				flag[temp->vertex] = 1;
				dist[temp->vertex] = dist[vertex] + 1;
				queue = addQueue(queue, temp->vertex);
			}
			temp = temp->next;
		}
	}
	if (dist[end] == INT_MAX)
	{
		printf("Пути нет\n");
	}
	else
	{
		printf("Длина пути: %d\n", dist[end]);
	}
	int result = dist[end];
	free(flag);
	free(dist);
	queue = freeQueue(queue);
	return result;

}
