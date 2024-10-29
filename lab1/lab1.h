#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct Node {
    Date date;
    char name[20];
    char surname[20];
    char patronymic[20];
    struct Node* next;
} Node;

#ifdef __cplusplus
extern "C" {
#endif

    char* name(char* surname, char* name, char* patronymic);
    Node* sort_list(Node* head, Node* New);
    Node* parse(char* line);
    Node* read_file(char* filename);
    void print_filtered_list(Node* head, int N);
    void free_all(Node** head);

#ifdef __cplusplus
}
#endif
