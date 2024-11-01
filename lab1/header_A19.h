#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* data;              
    struct node* next;      
    struct node* prev;      
} node_t;


typedef struct {
    node_t* head;          
    node_t* tail;         
} list_t;

list_t* CreateList(void);
void DestroyList(list_t* list);
void PrintLine(char* str);
void PrintList(list_t* list);
int Length(char* str);
char* CopyStr(char* from);
void AddToList(list_t* list, char data[]);
void SwapNodes(node_t* a, node_t* b);
list_t* SortList(list_t* list);

