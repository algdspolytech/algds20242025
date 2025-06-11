#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_LEN 256

typedef struct node {
    char* key;
    struct node* next;
} node_t;

// ���-�������
unsigned int hash(const char* str);

// ���������� ����� � �������
void addNode(node_t** table, const char* key);

// �������� ����� �� �������
void deleteNode(node_t** table, const char* key);

// ����� ����� � �������
int findNode(node_t** table, const char* key);

#endif // HASH_TABLE_H
