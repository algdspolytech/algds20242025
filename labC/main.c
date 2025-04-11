#include <stdio.h>
#include "labC.h"

void run_tests();

int main() {
    int size;
    int** graph = read_graph("graph.txt", &size);
    if (!graph) {
        printf("Error reading file\n");
        return 1;
    }

    int start = 0, end = size - 1;
    int path = find_shortest_path(graph, size, start, end);
    printf("Shortest path from %d to %d is size %d\n", start, end, path);

    free_graph(graph, size);

    run_tests();
    return 0;
}

void find_shortest_path_TwoConnectedNodes_return1_no1();
void find_shortest_path_DisconnectedGraph_returnMinus1_no2();
void find_shortest_path_LoopPath_return0_no3();
void find_shortest_path_ThreeNodeChain_return2_no4();
void find_shortest_path_MultiPathsShortest_return1_no5();
void find_shortest_path_SingleNodeGraph_return0_no6();
void find_shortest_path_IndirectConnection_return2_no7();
void find_shortest_path_SquareGraph_return1_no8();
void find_shortest_path_NoPathInThreeNode_returnMinus1_no9();
void find_shortest_path_FullConnection_return1_no10();

void run_tests() {
    find_shortest_path_TwoConnectedNodes_return1_no1();
    find_shortest_path_DisconnectedGraph_returnMinus1_no2();
    find_shortest_path_LoopPath_return0_no3();
    find_shortest_path_ThreeNodeChain_return2_no4();
    find_shortest_path_MultiPathsShortest_return1_no5();
    find_shortest_path_SingleNodeGraph_return0_no6();
    find_shortest_path_IndirectConnection_return2_no7();
    find_shortest_path_SquareGraph_return1_no8();
    find_shortest_path_NoPathInThreeNode_returnMinus1_no9();
    find_shortest_path_FullConnection_return1_no10();
    printf("Tests passed successfully\n");
}
