#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

void initQueue(Queue* q) {
    q->front = 0;
    q->last = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->last;
}

void add_queue(Queue* q, int value) {
    q->items[q->last++] = value;
}

int out_queue(Queue* q) {
    return q->items[q->front++];
}

int bfs(int graph[MAX_VERTEXES][MAX_VERTEXES], int n, int start, int end, int resultPath[MAX_VERTEXES]) {
    int visited[MAX_VERTEXES] = { 0 };
    int parent[MAX_VERTEXES];
    Queue q;
    initQueue(&q);

    visited[start] = 1;
    add_queue(&q, start);
    parent[start] = -1;

    while (!isEmpty(&q)) {
        int current = out_queue(&q);

        if (current == end) {
            int path_length = 0;
            for (int v = end; v != -1; v = parent[v]) {
                resultPath[path_length++] = v;
            }
            for (int i = 0; i < path_length / 2; i++) {
                int temp = resultPath[i];
                resultPath[i] = resultPath[path_length - i - 1];
                resultPath[path_length - i - 1] = temp;
            }
            return path_length; 
        }
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = current;
                add_queue(&q, i);
            }
        }
    }
    return -1; 
}

void dfs(int graph[MAX_VERTEXES][MAX_VERTEXES], int n, int current, int end, int visited[MAX_VERTEXES], int depth, int* minDepth, int path[MAX_VERTEXES], int tempPath[MAX_VERTEXES], int tempIndex) {
    visited[current] = 1;
    tempPath[tempIndex] = current;

    if (current == end) {
        if (depth < *minDepth) {
            *minDepth = depth;
            for (int i = 0; i <= tempIndex; i++) {
                path[i] = tempPath[i];
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                dfs(graph, n, i, end, visited, depth + 1, minDepth, path, tempPath, tempIndex + 1);
            }
        }
    }
    visited[current] = 0;
}
