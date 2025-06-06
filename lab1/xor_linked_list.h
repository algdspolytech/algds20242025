#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H

#include <stddef.h>
#include <stdint.h>

typedef struct Node{
    char * data;
    struct Node * link;
} Node;


Node *XOR_function(Node * a, Node * b);
Node *createNode(const char * data);
void listInsert(Node ** head, const char * data);
Node *find(Node * head, const char * key);
void deleteByKey(Node ** head, const char * key);
void deleteByAddress(Node ** head, Node * node);
void iterate(Node * head);
void clearList(Node ** head);

#endif