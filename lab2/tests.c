#include "tests.h"
#include <assert.h>

void runAllTests()
{

    initQueue_Initialization_FrontAndRearEqual0_no1();

    isEmpty_EmptyQueue_returnTrue_no2();
    isEmpty_NotEmptyQueue_returnFalse_no3();

    addToQueue_AddToEmptyQueue_returnValidVal_no4();
    addToQueue_AddToNotEmpty_returnValidVal_no5();

    removeFromQueue_RemoveFromEmpty_returnMinus1_no6();
    removeFromQueue_RemoveFromNotEmpty_returnItem_no7();

    bfs_ThereIsAPath_returnShortestPath_no8();
    bfs_ThereAreNoPath_returnINF_no9();
    bfs_NoSuchVertex_returnINF_no10();
    bfs_PathIntoItself_return0_no11();

    printf("Tests ran successfully!\n");
}

void initQueue_Initialization_FrontAndRearEqual0_no1()
{
    Queue q;
    initQueue(&q);
    assert(q.front == 0 && q.rear == 0);
}

void isEmpty_EmptyQueue_returnTrue_no2()
{
    Queue q;
    q.front = 0;
    q.rear = 0;
    assert(isEmpty(&q) == 1);
}

void isEmpty_NotEmptyQueue_returnFalse_no3()
{
    Queue q;
    q.front = 0;
    q.rear = 1;
    q.items[0] = 0;
    assert(isEmpty(&q) == 0);
}

void addToQueue_AddToEmptyQueue_returnValidVal_no4()
{
    Queue q;
    q.front = 0;
    q.rear = 0;
    int item = 1;
    addToQueue(&q, item);
    assert(q.rear == 1 && q.front == 0 && q.items[0] == item);
}

void addToQueue_AddToNotEmpty_returnValidVal_no5()
{
    Queue q;
    q.front = 0;
    q.rear = 1;
    q.items[0] = 0;
    int item = 1;
    addToQueue(&q, item);
    assert(q.rear == 2 && q.front == 0 && q.items[1] == item);
}

void removeFromQueue_RemoveFromEmpty_returnMinus1_no6()
{
    Queue q;
    q.front = 0;
    q.rear = 0;
    int result = removeFromQueue(&q);
    assert(result == -1);
}

void removeFromQueue_RemoveFromNotEmpty_returnItem_no7()
{
    Queue q;
    q.front = 0;
    q.rear = 1;
    int item = 0;
    q.items[0] = item;
    int result = removeFromQueue(&q);
    assert(result == item);
}

void bfs_ThereIsAPath_returnShortestPath_no8()
{
    Graph g;
    g.numVertices = 3;
    int testGraph[3][3] = //There are pathes: 0-1, 0-2, 1-2; Shortest between 0 and 2 = 1
    {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0},
    };
    for (int i = 0; i < g.numVertices; i++) 
    {
        for (int j = 0; j < g.numVertices; j++) 
        {
            g.graph[i][j] = testGraph[i][j];
        }
    }
    int result = bfs(&g, 0, 2);
    int shortest = 1;
    assert(result == shortest);
}

void bfs_ThereAreNoPath_returnINF_no9()
{
    Graph g;
    g.numVertices = 2;
    int testGraph[2][2] = //There are no paths
    {
        {0, 0},
        {0, 0},
    };
    for (int i = 0; i < g.numVertices; i++) 
    {
        for (int j = 0; j < g.numVertices; j++) 
        {
            g.graph[i][j] = testGraph[i][j];
        }
    }
    int result = bfs(&g, 0, 1);
    assert(result == INF);
}

void bfs_NoSuchVertex_returnINF_no10()
{
    Graph g;
    g.numVertices = 3;
    int testGraph[3][3] = //There are pathes: 0-1, 0-2, 1-2; Shortest between 0 and 2 = 1
    {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0},
    };
    for (int i = 0; i < g.numVertices; i++) 
    {
        for (int j = 0; j < g.numVertices; j++) 
        {
            g.graph[i][j] = testGraph[i][j];
        }
    }
    int result = bfs(&g, 0, 4);
    assert(result == INF);
}

void bfs_PathIntoItself_return0_no11()
{
    Graph g;
    g.numVertices = 3;
    int testGraph[3][3] = //There are pathes: 0-1, 0-2, 1-2; Shortest between 0 and 2 = 1
    {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0},
    };
    for (int i = 0; i < g.numVertices; i++) 
    {
        for (int j = 0; j < g.numVertices; j++) 
        {
            g.graph[i][j] = testGraph[i][j];
        }
    }
    int result = bfs(&g, 0, 0);
    assert(result == 0);
}