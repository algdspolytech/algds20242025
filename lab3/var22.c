#define _CRT_SECURE_NO_WARNINGS
#include<locale.h>

#include "graph.h"

Node* createNode(int vertex) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Если граф неориентированный
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("\n Вершина %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL");
    }
}

Graph* readGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла.\n");
        return NULL;
    }

    int vertices;
    fscanf(file, "%d", &vertices); // Чтение количества вершин
    Graph* graph = createGraph(vertices);
    int src, dest;

    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }

    fclose(file);
    return graph;
}

void findShortestPath(Graph* graph, int startVertex, int endVertex) {
    int visited[MAX_VERTICES] = { 0 };
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int parent[MAX_VERTICES];

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = -1; // -1 означает, что вершина не посещена
        parent[i] = -1;  // -1 означает, что родитель еще не установлен
    }

    queue[rear++] = startVertex;
    visited[startVertex] = 1;

    while (front < rear) {
        int current = queue[front++];

        if (current == endVertex) break; // Достигли конечной вершины

        Node* temp = graph->adjLists[current];
        while (temp) {
            if (visited[temp->vertex] == -1) {
                visited[temp->vertex] = visited[current] + 1; // Увеличить количество ребер
                parent[temp->vertex] = current; // Установить родителя
                queue[rear++] = temp->vertex; // Добавить в очередь
            }
            temp = temp->next;
        }
    }

    // Вывод пути
    if (visited[endVertex] != -1) {
        printf("Кратчайший путь между %d и %d:\n", startVertex, endVertex);
        int path[MAX_VERTICES];
        int pathIndex = 0;

        for (int v = endVertex; v != -1; v = parent[v]) {
            path[pathIndex++] = v;
        }

        for (int i = pathIndex - 1; i >= 0; i--) {
            printf("%d ", path[i]);
            if (i > 0) printf("-> ");
        }
        printf("\n");
    }
    else {
        printf("Нет пути между %d и %d\n", startVertex, endVertex);
    }
}
