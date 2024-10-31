#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "functions.h"

Node* create_node(int v) {
    Node* ans = (Node*)malloc(sizeof(Node));
    ans->v = v;
    ans->next = NULL;
    return ans;
}
Graph* init_graph(int size) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->size = size;

    for (int i = 0; i < size; i++) {
        g->list[i] = NULL;
    }
    return g;
}
void add_edge(Graph* g, int start, int finish) {
    Node* tmp = create_node(finish);
    tmp->next = g->list[start];
    g->list[start] = tmp;
}



void find_path(Graph* g, int start, int finish) {
    int len_of_path[MAX];
    int parent[MAX];

    int front = 0;
    int rear = 0;
    int queue[MAX];
    
    for (int i = 0; i < g->size; i++) {
        len_of_path[i] = -1; 
        parent[i] = -1;  
    }

    queue[rear] = start;
    rear++;
    len_of_path[start] = 1;

    while (front < rear) {
        int cur = queue[front];
        front++;
        if (cur == finish) {
            break;
        }else {
            Node* neighbour = g->list[cur];
            while (neighbour) {
                if (len_of_path[neighbour->v] == -1) {
                    len_of_path[neighbour->v] = len_of_path[cur] + 1; 
                    parent[neighbour->v] = cur;
                    queue[rear] = neighbour->v;
                    rear++;
                }
                neighbour = neighbour->next;
            }
        }
    }

    if (len_of_path[finish] != -1) {
        printf("path between %d and %d: ", start, finish);
        int path[MAX];
        int ind = 0;

        for (int v = finish; v != -1; v = parent[v]) {
            path[ind] = v;
            ind++;
        }

        for (int i = ind - 1; i >= 0; i--) {
            printf("%d ", path[i]);
            if (i > 0) {
                printf("-> ");
            }
        }
        printf("\n");
    }
    else {
        printf("there is no path between %d ans %d\n", start, finish);
    }
}



Graph* read_graph(char* name) {
    FILE* file = fopen(name, "r");
    
    int size = 0;
    fscanf(file, "%d", &size);

    Graph* graph = init_graph(size);
    int start = 0;
    int finish = 0;

    while (fscanf(file, "%d--%d", &start, &finish) != EOF) {
        add_edge(graph, start, finish);
    }
    return graph;
}
void print_graph(Graph* g) {
    for (int v = 0; v < g->size; v++) {
        Node* temp = g->list[v];
        printf("v number %d is connected with -> ", v);
        while (temp) {
            printf("%d ", temp->v);
            temp = temp->next;
        }
        printf("\n");
    }
}