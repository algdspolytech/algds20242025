#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "funcs.h"
#include "tests.h"

int main()
{
    FILE* inputFile = input_open("input.txt");
    FILE* outputFile = output_open("output.txt");


    Graph graph = { .wordCount = 0 };
    memset(graph.adjMatrix, 0, sizeof(graph.adjMatrix));

    char line[256];
    if (fgets(line, sizeof(line), inputFile))
    {
        char* word = strtok(line, " \n");
        while (word)
{
            addWord(&graph, word);
            word = strtok(NULL, " \n");
        }
    }

    while (fgets(line, sizeof(line), inputFile))
    {
        char word1[MAX_LENGTH], word2[MAX_LENGTH];
        if (sscanf(line, "%s %s", word1, word2) == 2)
        {
            addEdge(&graph, word1, word2);
        }
        else
        {
            printf("[Error]Incorrect input\n");
        }
    }

    fclose(inputFile);

    char result[MAX_WORDS][MAX_LENGTH];
    if (topologicalSort(&graph, result)) {
        for (int i = 0; i < graph.wordCount; i++) {
            fprintf(outputFile, "%s ", result[i]);
        }
        fprintf(outputFile, "\n");
    }
    else {
        fprintf(outputFile, "[Error]\n");
    }

    fclose(outputFile);

    Test_input_open_file_is_null_No1();
    Test_output_open_file_is_null_No2();
    Test_findWordIndex_No3();
    Test_addWord_same_again_No4();
    Test_addWord_wordCount_No5();
    Test_addEdge_No6();
    Test_addEdge_No7();
    Test_topologicalSort_true_No8();
    Test_topologicalSort_false_No9();
    Test_addWord_more_args_No10();

    return 0;
}
