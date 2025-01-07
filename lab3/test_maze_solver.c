#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "maze_solver.h"

void test_nodeCompare_2nodes_returnValidVal_no1() {
    Node n1 = {0, 0};
    Node n2 = {0, 0};
    Node n3 = {1, 1};

    assert(nodeCompare(&n1, &n2) == 1);
    assert(nodeCompare(&n1, &n3) == 0);

    printf("Test nodeCompare passed\n");
}

void test_pathSetup_createPath_returnValidNode_no2() {
    Node start = {0, 0};
    Path path;
    pathSetup(&path, &start);

    assert(path.head == 0);
    assert(path.path[0].x == start.x && path.path[0].y == start.y);

    free(path.path);
    printf("Test pathSetup passed\n");
}

void test_pathPushAndPop_addNode_returnValidNode_no3() {
    Node start = {0, 0};
    Node next = {0, 1};
    Path path;
    pathSetup(&path, &start);

    pathPush(&path, &next);
    assert(path.head == 1);
    assert(path.path[1].x == next.x && path.path[1].y == next.y);

    pathPop(&path);
    assert(path.head == 0);

    free(path.path);
    printf("Test pathPushandPop passed\n");
}

void test_pathEmbiggen_addMem_returnValidVal_no4() {
    Node start = {0, 0};
    Path path;
    pathSetup(&path, &start);

    int maxlen = path.maxlen;
    for (int i = 0; i <= maxlen; i++){
        Node n = {i, i};
        pathPush(&path, &n);
    }

    assert(path.head == maxlen + 1);
    assert(path.maxlen == 2 * maxlen);

    free(path.path);
    printf("Test pathEmbiggen passed \n");
}

void test_canMove_checkValidMove_returnValidVal_no5() {
    Node current = {0, 0};

    assert(canMove(&current, U) == 0);
    assert(canMove(&current, D) == 1);
    assert(canMove(&current, R) == 1);
    assert(canMove(&current, L) == 0);
    
    printf("Test canMove passed\n");
}

void test_findPath_success_returnTrue_no6() {
    Path path;
    pathSetup(&path, &start);
    visited[start.x][start.y] = 1;

    assert(findPath(&path, &start) == 1);

    free(path.path);
    printf("Test findPath_success passed\n");
}

void test_findPath_failureWithoutFinish_returnNULL_no7() {
    Path path;
    pathSetup(&path, &start);

    int invalidMaze[MAZE_X][MAZE_Y] = {
        {R|D|START, L, R|D, L},
        {U|R|D, L|R, U|D|L, D},
        {U|D, R|D, U|R|L, U|D|L},
        {U, U|R, L, U}
    };//лабиринт без финиша

    memcpy(maze, invalidMaze, sizeof(maze));
    visited[start.x][start.y] = 1;

    assert(findPath(&path, &start) == 0);

    free(path.path);
    printf("Test findPath_failureWithoutFinish passed\n");
}

void test_findPath_failureClosedWalls_returnNULL_no8() {
    Path path;
    pathSetup(&path, &start);

    int invalidMaze[MAZE_X][MAZE_Y] = {
        {R|D|START, L, R|D, L},
        {U|R|D, R, U|D|L, D},
        {U|D, R|D, U|R|L, U|D|L},
        {U, U|R, L, U|FINISH}
    };//лабиринт c закрытыми стенками без доступа к финишу

    memcpy(maze, invalidMaze, sizeof(maze));
    visited[start.x][start.y] = 1;

    assert(findPath(&path, &start) == 0);

    free(path.path);
    printf("Test findPath_failureClosedWalls passed\n");
}

void test_isValidMove_insideMaze_returnValidVal_no9() {
    assert(isValidMove(0, 0) == 1);
    assert(isValidMove(-1, 0) == 0);
    assert(isValidMove(0, 4) == 0);
    printf("Test isValidMove passed\n");
}

void test_pathPop_popEmptyPath_returnNull_no10() {
    Path path;
    Node start = {0, 0};
    pathSetup(&path, &start);
    pathPop(&path);
    pathPop(&path);

    assert(path.head == 0);

    printf("Test popEmptyPath passed\n");
}

int main() {
    test_nodeCompare_2nodes_returnValidVal_no1();
    test_pathSetup_createPath_returnValidNode_no2();
    test_pathPushAndPop_addNode_returnValidNode_no3();
    test_pathEmbiggen_addMem_returnValidVal_no4();
    test_canMove_checkValidMove_returnValidVal_no5();
    test_findPath_success_returnTrue_no6();
    test_findPath_failureWithoutFinish_returnNULL_no7();
    test_findPath_failureClosedWalls_returnNULL_no8();
    test_isValidMove_insideMaze_returnValidVal_no9();
    test_pathPop_popEmptyPath_returnNull_no10();

    printf("ALL TESTS PASSED\n");
    return 0;
}