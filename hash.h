#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

// Ñòðóêòóðà äëÿ óçëà öåïî÷êè
typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

// Ñòðóêòóðà õåø-òàáëèöû
typedef struct {
    HashNode** buckets;
    int size;
    int capacity;
} HashTable;

// Èíèöèàëèçàöèÿ õåø-òàáëèöû
HashTable* ht_create(int capacity);

// Îñâîáîæäåíèå ïàìÿòè õåø-òàáëèöû
void ht_destroy(HashTable* table);

// Âñòàâêà ýëåìåíòà â õåø-òàáëèöó
bool ht_insert(HashTable* table, const char* key, const char* value);

// Ïîèñê ýëåìåíòà â õåø-òàáëèöå
char* ht_search(HashTable* table, const char* key);

// Óäàëåíèå ýëåìåíòà èç õåø-òàáëèöû
bool ht_delete(HashTable* table, const char* key);

// Âûâîä ñîäåðæèìîãî õåø-òàáëèöû (äëÿ îòëàäêè)
void ht_print(HashTable* table);

#endif 