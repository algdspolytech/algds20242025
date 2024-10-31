#ifndef TOPO_SORT_H
#define TOPO_SORT_H

#include <stdio.h>

#define MAX_WORDS 100
#define MAX_LENGTH 20

typedef struct Node {
    char word[MAX_LENGTH];
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} List;

extern List adj_list[MAX_WORDS];
extern char words[MAX_WORDS][MAX_LENGTH];
extern int word_count;
extern int in_degree[MAX_WORDS];
extern int queue[MAX_WORDS];
extern int front, rear;

int find_index(char* word);
void add_edge(int u, int v);
void priority_enqueue(int val);
int priority_dequeue();
void topological_sort(FILE* output);

#endif
