#define _CRT_SECURE_NO_WARNINGS
#include "topo_sort.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

List adj_list[MAX_WORDS];
char words[MAX_WORDS][MAX_LENGTH];
int word_count = 0;
int in_degree[MAX_WORDS];
int queue[MAX_WORDS];
int front = 0, rear = 0;

int compare_strings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

int find_index(char* word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i], word) == 0) return i;
    }
    strcpy(words[word_count], word);
    return word_count++;
}

void add_edge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->word, words[v]);
    node->next = adj_list[u].head;
    adj_list[u].head = node;
    in_degree[v]++;
}

void priority_enqueue(int val) {
    int i = rear - 1;
    while (i >= front && strcmp(words[queue[i]], words[val]) > 0) {
        queue[i + 1] = queue[i];
        i--;
    }
    queue[i + 1] = val;
    rear++;
}

int priority_dequeue() {
    return queue[front++];
}

void topological_sort(FILE* output) {
    int result[MAX_WORDS];
    int result_count = 0;

    for (int i = 0; i < word_count; i++) {
        if (in_degree[i] == 0) priority_enqueue(i);
    }

    while (front < rear) {
        int u = priority_dequeue();
        result[result_count++] = u;

        Node* temp = adj_list[u].head;
        while (temp) {
            int v = find_index(temp->word);
            if (--in_degree[v] == 0) priority_enqueue(v);
            temp = temp->next;
        }
    }

    if (result_count != word_count) {
        fprintf(output, "[Error]");
    }
    else {
        for (int i = 0; i < result_count; i++) {
            fprintf(output, "%s ", words[result[i]]);
        }
    }
}

#ifndef TESTING
int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        perror("Error opening file");
        return 1;
    }

    char line[256];
    if (fgets(line, sizeof(line), input)) {
        char* token = strtok(line, " ");
        while (token) {
            find_index(token);
            token = strtok(NULL, " ");
        }
    }

    while (fgets(line, sizeof(line), input)) {
        char word1[MAX_LENGTH], word2[MAX_LENGTH];
        if (sscanf(line, "%s %s", word1, word2) == 2) {
            int u = find_index(word1);
            int v = find_index(word2);
            add_edge(u, v);
        }
    }

    topological_sort(output);
    fclose(input);
    fclose(output);
    return 0;
}
#endif
