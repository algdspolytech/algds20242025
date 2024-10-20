#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct Entry {
    Date date;
    char name[20];
    char surname[20];
    int total_hours;
    struct Entry *next;
} Entry;

typedef struct Node {
    int hours;
    struct Entry *head;
    struct Node *next;
} Node;

Node* read_file(char* filename);
void print_list(Node* head);