#ifndef TESTS_H
#define TESTS_H

#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

void testPath_singleVertex_1(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);
void testPath_severalVertexes_2(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);
void testPath_severalVertexes_3(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);
void testNoPath_4(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);
void testPath_single_edge_5(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);
void testPath_Non_existentVertex_6(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);
void test_QueueInitialization_7();
void test_Queue_add_remove_8();
void test_Queue_multiple_addRemove_9();
void test_Multiple_paths_10(int graph[MAX_VERTEXES][MAX_VERTEXES], int n);

#endif
