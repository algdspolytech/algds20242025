#include <assert.h>
#include "labC.h"

#define ARRAY_TO_PTR(mat, ptrArr, N) \
    int* ptrArr[N]; \
    for (int i = 0; i < N; ++i) ptrArr[i] = mat[i];

void find_shortest_path_TwoConnectedNodes_return1_no1() {
    int g[2][2] = { {0, 1}, {1, 0} };
    ARRAY_TO_PTR(g, gp, 2);
    assert(find_shortest_path(gp, 2, 0, 1) == 1);
}

void find_shortest_path_DisconnectedGraph_returnMinus1_no2() {
    int g[2][2] = { {0, 0}, {0, 0} };
    ARRAY_TO_PTR(g, gp, 2);
    assert(find_shortest_path(gp, 2, 0, 1) == -1);
}

void find_shortest_path_LoopPath_return0_no3() {
    int g[1][1] = { {0} };
    ARRAY_TO_PTR(g, gp, 1);
    assert(find_shortest_path(gp, 1, 0, 0) == 0);
}

void find_shortest_path_ThreeNodeChain_return2_no4() {
    int g[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    ARRAY_TO_PTR(g, gp, 3);
    assert(find_shortest_path(gp, 3, 0, 2) == 2);
}

void find_shortest_path_MultiPathsShortest_return1_no5() {
    int g[3][3] = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}
    };
    ARRAY_TO_PTR(g, gp, 3);
    assert(find_shortest_path(gp, 3, 0, 2) == 1);
}

void find_shortest_path_SingleNodeGraph_return0_no6() {
    int g[1][1] = { {0} };
    ARRAY_TO_PTR(g, gp, 1);
    assert(find_shortest_path(gp, 1, 0, 0) == 0);
}

void find_shortest_path_IndirectConnection_return2_no7() {
    int g[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    ARRAY_TO_PTR(g, gp, 3);
    assert(find_shortest_path(gp, 3, 0, 2) == 2);
}

void find_shortest_path_SquareGraph_return1_no8() {
    int g[4][4] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    ARRAY_TO_PTR(g, gp, 4);
    assert(find_shortest_path(gp, 4, 0, 1) == 1);
}

void find_shortest_path_NoPathInThreeNode_returnMinus1_no9() {
    int g[3][3] = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}
    };
    ARRAY_TO_PTR(g, gp, 3);
    assert(find_shortest_path(gp, 3, 0, 2) == -1);
}

void find_shortest_path_FullConnection_return1_no10() {
    int g[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    ARRAY_TO_PTR(g, gp, 3);
    assert(find_shortest_path(gp, 3, 0, 2) == 1);
}
