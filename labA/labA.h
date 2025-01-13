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
    char first_name[20];
    char last_name[20];
    char middle_name[20];
    struct Node* next;
} Node;

#ifdef __cplusplus
extern "C" {
#endif

    char* create_fullname(char* last_name, char* first_name, char* middle_name);
    Node* insert_sorted(Node* head, Node* new_node);
    Node* parse_line(char* line);
    Node* read_from_file(char* filename);
    void display_list(Node* head);
    void free_memory(Node** head);

#ifdef __cplusplus
}
#endif
