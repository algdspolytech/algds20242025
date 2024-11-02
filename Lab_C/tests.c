#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Lab_C.h"
#include "tests.h"
#include <assert.h>


void test_createQueue_empty() {
    Queue *queue = createQueue();
    assert(queue != NULL);
    assert(queue->front == NULL);
    assert(queue->rear == NULL);
    free(queue);
}


void test_enqueue_empty() {
    Queue *queue = createQueue();
    enqueue(queue, 5);
    assert(queue->front != NULL);
    assert(queue->rear != NULL);
    assert(queue->front->data == 5);
    assert(queue->rear->data == 5);
    free(queue);
}

void test_enqueue_nonempty() {
    Queue *queue = createQueue();
    enqueue(queue, 5);
    enqueue(queue, 10);
    assert(queue->front != NULL);
    assert(queue->rear != NULL);
    assert(queue->front->data == 5);
    assert(queue->rear->data == 10);
    free(queue);
}


void test_dequeue_empty() {
    Queue *queue = createQueue();
    int data = dequeue(queue);
    assert(data == -1);
    free(queue);
}

void test_dequeue_nonempty() {
    Queue *queue = createQueue();
    enqueue(queue, 5);
    int data = dequeue(queue);
    assert(data == 5);
    assert(queue->front == NULL);
    assert(queue->rear == NULL);
    free(queue);
}

void test_dequeue_multiple() {
    Queue *queue = createQueue();
    enqueue(queue, 5);
    enqueue(queue, 10);
    int data1 = dequeue(queue);
    int data2 = dequeue(queue);
    assert(data1 == 5);
    assert(data2 == 10);
    assert(queue->front == NULL);
    assert(queue->rear == NULL);
    free(queue);
}


void test_isEmpty_empty() {
    Queue *queue = createQueue();
    assert(isEmpty(queue) == 1);
    free(queue);
}

void test_isEmpty_nonempty() {
    Queue *queue = createQueue();
    enqueue(queue, 5);
    assert(isEmpty(queue) == 0);
    free(queue);
}


int test_findShortestPath_empty_graph(void) {
    int graph[MAX_NODES][MAX_NODES] = {{0}};
    int num_nodes = 0;
    int path_length = 0;
    int *path = findShortestPath(graph, 0, 1, num_nodes, &path_length);

    if (path != NULL) {
        return 1; 
    }

    if (path_length != 0) {
        return 1; 
    }

    return 0; 
}


int test_findShortestPath_unreachable_node(void) {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    int num_nodes = 3;
    int path_length = 0;
    int *path = findShortestPath(graph, 0, 2, num_nodes, &path_length);

    if (path != NULL) {
        return 1; 
    }

    if (path_length != 0) {
        return 1; 
    }

    return 0; 
}


int test_findShortestPath_simple_path(void) {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    int num_nodes = 4;
    int path_length = 0;
    int *path = findShortestPath(graph, 0, 3, num_nodes, &path_length);

    if (path == NULL) {
        return 1; 
    }

    if (path_length != 3) {
        return 1; 
    }

    if (path[0] != 0 || path[1] != 1 || path[2] != 2 || path[3] != 3) {
        return 1; 
    }

    free(path);
    return 0; 
}

void test_readGraphFromFile_valid() {
    int graph[MAX_NODES][MAX_NODES];
    int num_nodes;
    int result = readGraphFromFile("test_graph.txt", graph, &num_nodes);
    assert(result == 0);
    assert(num_nodes == 4);
   
}

void test_readGraphFromFile_invalid_file() {
    int graph[MAX_NODES][MAX_NODES];
    int num_nodes;
    int result = readGraphFromFile("nonexistent_file.txt", graph, &num_nodes);
    assert(result == 1);
}

void test_readGraphFromFile_invalid_format() {
    int graph[MAX_NODES][MAX_NODES];
    int num_nodes;
    int result = readGraphFromFile("invalid_format.txt", graph, &num_nodes);
    assert(result == 1);
}

void run_tests() {
  test_createQueue_empty();
  test_enqueue_empty();
  test_enqueue_nonempty();
  test_dequeue_empty();
  test_dequeue_nonempty();
  test_dequeue_multiple();
  test_isEmpty_empty();
  test_isEmpty_nonempty();
  test_findShortestPath_empty_graph();
  test_findShortestPath_unreachable_node();
  test_findShortestPath_simple_path();
  test_readGraphFromFile_valid();
  test_readGraphFromFile_invalid_file();
  test_readGraphFromFile_invalid_format();
}