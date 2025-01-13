#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

typedef struct GraphStructure {
    int vertexCount; // Кол-во вершин
    int** adjacencyList; // Список смежности графа
    char** vertexNames; // Имя каждой вершины
} GraphStructure;

// Создание графа
GraphStructure* create_graph() {
    GraphStructure* graph = (GraphStructure*)malloc(sizeof(GraphStructure));
    graph->vertexCount = 0;
    graph->adjacencyList = (int**)malloc(sizeof(int*));
    graph->vertexNames = (char**)malloc(sizeof(char*));

    return graph;
}

// Добавляем вершину
void insert_vertex(GraphStructure* graph, char* vertex) {
    graph->vertexCount++;
    graph->vertexNames = (char**)realloc(graph->vertexNames, sizeof(char*) * graph->vertexCount);
    graph->vertexNames[graph->vertexCount - 1] = vertex;

    graph->adjacencyList = (int**)realloc(graph->adjacencyList, sizeof(int*) * graph->vertexCount);
    graph->adjacencyList[graph->vertexCount - 1] = (int*)malloc(sizeof(int));
    graph->adjacencyList[graph->vertexCount - 1][0] = -1;
}

// Функция сравнения строк
static int string_compare(char* str1, char* str2) {
    int index = 0;
    while (str1[index] != '\0' || str2[index] != '\0')
        if (str1[index] != str2[index++]) return 0;

    return 1;
}

// Функция для получения индекса вершины по её названию
int find_vertex_index(GraphStructure* graph, char* vertex) {
    int index = 0;
    for (index = 0; index < graph->vertexCount; index++)
        if (string_compare(graph->vertexNames[index], vertex) == 1) return index;
    return -1;
}

// Функция для получения имени вершины по индексу
char* fetch_vertex_name(GraphStructure* graph, int index) {
    return graph->vertexNames[index];
}

// Добавляем ребро из v1 в v2
void insert_edge(GraphStructure* graph, char* source, char* destination) {
    int srcIndex = find_vertex_index(graph, source);
    int destIndex = find_vertex_index(graph, destination);

    int length = 0;
    while (graph->adjacencyList[srcIndex][length] != -1) length++;
    graph->adjacencyList[srcIndex] = (int*)realloc(graph->adjacencyList[srcIndex], sizeof(int) * (length + 2));
    graph->adjacencyList[srcIndex][length] = destIndex;
    graph->adjacencyList[srcIndex][length + 1] = -1;
}

// Функция для чтения одного слова из файла
static char* read_word(FILE* file) {
    int size = 0;
    char* word = (char*)malloc(sizeof(char));

    char character;
    do {
        character = fgetc(file);

        size++;
        word = (char*)realloc(word, sizeof(char) * size);
        word[size - 1] = character;

        if (character == ' ' || character == '\n' || character == EOF) {
            word = (char*)realloc(word, sizeof(char) * (size + 1));
            word[size] = '\0';

            return word;
        }
    } while (character != '\n' && character != EOF);
}

// Функция для получения длины строки 
static int get_length(char* str) {
    int length = 0;
    while (str[length] != '\0') length++;

    return length;
}

// Получаем граф из файла
GraphStructure* read_graph(FILE* file) {
    // Создаем граф
    GraphStructure* graph = create_graph();

    // Загружаем список вершин
    int continueLoading = 1;
    do {
        char* word = read_word(file);
        int length = get_length(word);

        if (word[length - 1] == '\n') continueLoading = 0;
        word[length - 1] = '\0';

        insert_vertex(graph, word);
    } while (continueLoading);

    // Загружаем ребра
    continueLoading = 1;
    do {
        char* firstWord = read_word(file);
        int length1 = get_length(firstWord);
        char* secondWord = read_word(file);
        int length2 = get_length(secondWord);

        if (secondWord[length2 - 1] == EOF) continueLoading = 0;
        firstWord[length1 - 1] = '\0';
        secondWord[length2 - 1] = '\0';

        insert_edge(graph, firstWord, secondWord);
    } while (continueLoading);

    return graph;
}

// Функция топологической сортировки
void perform_topological_sort(GraphStructure* graph, Stack* stack, int vertex, int* visited) {
    visited[vertex] = 1;

    int j = 0;
    while (graph->adjacencyList[vertex][j] != -1) {
        if (visited[graph->adjacencyList[vertex][j]] == 0)
            perform_topological_sort(graph, stack, graph->adjacencyList[vertex][j], visited);
        j++;
    }

    push_stack(stack, vertex);
}

// Рекурсивная часть функции проверки графа на ацикличность
static int check_cycle_recursively(GraphStructure* graph, int* visited, int vertex) {
    int j = 0;
    visited[vertex] = 1;
    while (graph->adjacencyList[vertex][j] != -1) {
        if (visited[graph->adjacencyList[vertex][j]] == 1)
            return 0;
        else {
            int result = check_cycle_recursively(graph, visited, graph->adjacencyList[vertex][j]);
            visited[vertex] = 0;
            return result;
        }
    }
    visited[vertex] = 0;
    return 1;
}

// Функция проверки графа на ацикличность
int verify_acylclic(GraphStructure* graph) {
    int* visited = (int*)malloc(sizeof(int) * graph->vertexCount);
    for (int i = 0; i < graph->vertexCount; i++)
        visited[i] = 0;

    for (int vertex = 0; vertex < graph->vertexCount; vertex++)
        if (check_cycle_recursively(graph, visited, vertex) == 0)
            return 0;

    return 1;
}
