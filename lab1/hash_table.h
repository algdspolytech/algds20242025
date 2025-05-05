#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

// ��������� ��� ���� �������
typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

// ��������� ���-�������
typedef struct {
    HashNode** buckets;
    int size;
    int capacity;
} HashTable;

// ������������� ���-�������
HashTable* ht_create(int capacity);

// ������������ ������ ���-�������
void ht_destroy(HashTable* table);

// ������� �������� � ���-�������
bool ht_insert(HashTable* table, const char* key, const char* value);

// ����� �������� � ���-�������
char* ht_search(HashTable* table, const char* key);

// �������� �������� �� ���-�������
bool ht_delete(HashTable* table, const char* key);

// ����� ����������� ���-������� (��� �������)
void ht_print(HashTable* table);

#endif // HASH_TABLE_H