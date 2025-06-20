#ifndef LABJ_H
#define LABJ_H

typedef struct {
    char** data;     
    int capacity;    
    int size;        
} HashTable;

HashTable* ht_create(int capacity);
void ht_free(HashTable* ht);
int ht_insert(HashTable* ht, const char* str);
int ht_search(HashTable* ht, const char* str);

#endif