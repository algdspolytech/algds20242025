#include "graph_sort.h"

void initializeGraph(Graph* graph) {
    graph->wordCount = 0;
    memset(graph->adjMatrix, 0, sizeof(graph->adjMatrix));
}

int findWordIndex(Graph* graph, const char* word) {
    for (int i = 0; i < graph->wordCount; i++) {
        if (strcmp(graph->words[i], word) == 0) return i;
    }
    return -1;
}

void addEdge(Graph* graph, const char* word1, const char* word2) {
    int index1 = findWordIndex(graph, word1);
    int index2 = findWordIndex(graph, word2);

    if (index1 == -1) {
        strcpy(graph->words[graph->wordCount], word1);
        index1 = graph->wordCount++;
    }
    if (index2 == -1) {
        strcpy(graph->words[graph->wordCount], word2);
        index2 = graph->wordCount++;
    }

    graph->adjMatrix[index1][index2] = 1; // Добавляем ребро
}

bool topologicalSort(Graph* graph, char output[MAX_WORDS][MAX_LEN], int* outputSize) {
    int inDegree[MAX_WORDS] = { 0 };
    int queue[MAX_WORDS];
    int front = 0, rear = 0;
    *outputSize = 0;

    // Подсчет степеней входа
    for (int i = 0; i < graph->wordCount; i++) {
        for (int j = 0; j < graph->wordCount; j++) {
            if (graph->adjMatrix[i][j]) inDegree[j]++;
        }
    }

    // Добавление вершин с нулевой степенью входа
    for (int i = 0; i < graph->wordCount; i++) {
        if (inDegree[i] == 0) queue[rear++] = i;
    }

    // Топологическая сортировка
    while (front < rear) {
        int current = queue[front++];
        strcpy(output[(*outputSize)++], graph->words[current]);

        for (int j = 0; j < graph->wordCount; j++) {
            if (graph->adjMatrix[current][j]) {
                if (--inDegree[j] == 0) queue[rear++] = j;
            }
        }
    }

    // Проверка на циклы
    return (*outputSize == graph->wordCount);
}

void readInputFile(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input file");
        exit(1);
    }

    char buffer[256];
    initializeGraph(graph);

    // Чтение первой строки (слова)
    if (fgets(buffer, sizeof(buffer), file)) {
        char* token = strtok(buffer, " \n");
        while (token) {
            if (findWordIndex(graph, token) == -1) {
                strcpy(graph->words[graph->wordCount++], token);
            }
            token = strtok(NULL, " \n");
        }
    }

    // Чтение пар слов
    while (fgets(buffer, sizeof(buffer), file)) {
        char word1[MAX_LEN], word2[MAX_LEN];
        if (sscanf(buffer, "%s %s", word1, word2) == 2) {
            addEdge(graph, word1, word2);
        }
    }

    fclose(file);
}

void writeOutputFile(const char* filename, char output[MAX_WORDS][MAX_LEN], int outputSize, bool hasError) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening output file");
        exit(1);
    }

    if (hasError) {
        fprintf(file, "[Error]\n");
    }
    else {
        for (int i = 0; i < outputSize; i++) {
            fprintf(file, "%s ", output[i]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    Graph graph;
    char output[MAX_WORDS][MAX_LEN];
    int outputSize;

    const char* inputFilename = "input.txt";
    const char* outputFilename = "output.txt";

    readInputFile(inputFilename, &graph);
    bool hasError = !topologicalSort(&graph, output, &outputSize);
    writeOutputFile(outputFilename, output, outputSize, hasError);

    return 0;
}