#define _CRT_SECURE_NO_WARNINGS


#include <assert.h>

#include "tests.h"

void Test_input_open_file_is_null_No1(void)
{
	assert(input_open("test.exe"));
	printf("Test 1 passed\n");
}

void Test_output_open_file_is_null_No2(void)
{
	assert(output_open("test.exe"));
	printf("Test 2 passed\n");
}

void Test_findWordIndex_No3(void)
{
    Graph graph = { .wordCount = 0 };
    addWord(&graph, "a");
    addWord(&graph, "b");

    assert(findWordIndex(&graph, "a") == 0);
    assert(findWordIndex(&graph, "b") == 1);
    assert(findWordIndex(&graph, "c") == -1);

    printf("Test 3 passed\n");
}

void Test_addWord_same_again_No4(void)
{
    Graph graph = { .wordCount = 0 };
    assert(addWord(&graph, "a") == 0);
    assert(addWord(&graph, "b") == 1);
    assert(addWord(&graph, "a") == 0);

    printf("Test 4 passed\n");
}

void Test_addWord_wordCount_No5(void)
{
    Graph graph = { .wordCount = 0 };
    assert(addWord(&graph, "a") == 0);
    assert(addWord(&graph, "b") == 1);
    assert(addWord(&graph, "a") == 0);
    assert(graph.wordCount == 2);

    printf("Test 5 passed\n");
}

void Test_addEdge_No6(void)
{
    Graph graph = { .wordCount = 0 };
    memset(graph.adjMatrix, 0, sizeof(graph.adjMatrix));

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");

    int indexA = findWordIndex(&graph, "a");
    int indexB = findWordIndex(&graph, "b");
    int indexC = findWordIndex(&graph, "c");

    assert(graph.adjMatrix[indexA][indexB] == 1);
    assert(graph.adjMatrix[indexB][indexC] == 1);

    printf("Test 6 passed\n");
}

void Test_addEdge_No7(void)
{
    Graph graph = { .wordCount = 0 };
    memset(graph.adjMatrix, 0, sizeof(graph.adjMatrix));

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");

    int indexA = findWordIndex(&graph, "a");
    int indexC = findWordIndex(&graph, "c");

    assert(graph.adjMatrix[indexC][indexA] == 0);

    printf("Test 7 passed\n");
}

void Test_topologicalSort_true_No8(void)
{
    Graph graph = { .wordCount = 0 };
    memset(graph.adjMatrix, 0, sizeof(graph.adjMatrix));

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");

    char result[MAX_WORDS][MAX_LENGTH];
    bool success = topologicalSort(&graph, result);

    assert(success == true);

    printf("Test 8 passed\n");
}


void Test_topologicalSort_false_No9(void)
{
    Graph graph = { .wordCount = 0 };
    memset(graph.adjMatrix, 0, sizeof(graph.adjMatrix));

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");
    addEdge(&graph, "c", "a");

    char result[MAX_WORDS][MAX_LENGTH];
    bool success = topologicalSort(&graph, result);

    assert(success == false);

    printf("Test 9 passed\n");
}


void Test_addWord_more_args_No10(void)
{
    Graph graph = { .wordCount = 0 };
    addWord(&graph, "a1");
    addWord(&graph, "a2");
    addWord(&graph, "a3");
    addWord(&graph, "a4");
    addWord(&graph, "a5");
    addWord(&graph, "a6");
    addWord(&graph, "a7");
    addWord(&graph, "a8");
    addWord(&graph, "a9");
    addWord(&graph, "a10");
    assert(addWord(&graph, "a11") == -2);

    printf("Test 10 passed\n");
}