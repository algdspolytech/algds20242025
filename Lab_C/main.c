#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"


int main() {
    int n1, n2;
    int big_graph[MAX_VERTEXES][MAX_VERTEXES];
    int small_graph[MAX_VERTEXES][MAX_VERTEXES];

    readGraphFromFile("graph.txt", big_graph, &n1);
    readGraphFromFile("small_graph.txt", small_graph, &n2);



    testPath_singleVertex_1(big_graph, n1);
    testPath_severalVertexes_2(big_graph, n1);
    testPath_severalVertexes_3(big_graph, n1);
    testNoPath_4(small_graph, n2);
    testPath_single_edge_5(big_graph, n1);
    testPath_Non_existentVertex_6(small_graph, n2);


    test_QueueInitialization_7();
    test_Queue_add_remove_8();
    test_Queue_multiple_addRemove_9();

    test_Multiple_paths_10(big_graph, n1);


    return 0;
}
