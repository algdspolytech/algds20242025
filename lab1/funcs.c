#define _CRT_SECURE_NO_WARNINGS

#include "funcs.h"


FILE* input_open(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
        fprintf(stderr, "[Error] Could not open input file\n");
        return;
	}

	return file;
}

FILE* output_open(const char* filenmae)
{
	FILE* file = fopen(filenmae, "w");
    if (file == NULL)
    {
        fprintf(stderr, "[Error] Could not open output file\n");
        return;
    }

	return file;
}


int findWordIndex(Graph* graph, const char* word)
{
    for (int i = 0; i < graph->wordCount; i++)
    {
        if (strcmp(graph->words[i], word) == 0)
        {
            return i;
        }
    }
    return -1;
}


int addWord(Graph* graph, const char* word)
{
    int index = findWordIndex(graph, word);
    if (index == -1)
    {
        if (graph->wordCount >= MAX_WORDS)
        {
            printf("Too many words\n");
            return -2;
        }
        strcpy(graph->words[graph->wordCount], word);
        graph->indegree[graph->wordCount] = 0;
        index = graph->wordCount;
        graph->wordCount++;
    }
    return index;
}


void addEdge(Graph* graph, const char* word1, const char* word2)
{
    int index1 = addWord(graph, word1);
    int index2 = addWord(graph, word2);

    if (graph->adjMatrix[index1][index2] == 0)
    {
        graph->adjMatrix[index1][index2] = 1;
        graph->indegree[index2]++;
    }
}


bool topologicalSort(Graph* graph, char result[MAX_WORDS][MAX_LENGTH])
{
    int sortedCount = 0;
    int queue[MAX_WORDS];
    int front = 0, rear = 0;
    
    for (int i = 0; i < graph->wordCount; i++)
    {
        if (graph->indegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    while (front < rear)
    {
        int current = queue[front++];
        strcpy(result[sortedCount++], graph->words[current]);

        for (int i = 0; i < graph->wordCount; i++)
        {
            if (graph->adjMatrix[current][i] == 1)
            {
                graph->indegree[i]--;
                if (graph->indegree[i] == 0)
                {
                    queue[rear++] = i;
                }
            }
        }
    }

    return (sortedCount == graph->wordCount);
}