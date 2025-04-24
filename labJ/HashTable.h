#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct {
    char *key;
    char *value;
    int deleted;
} HashTableValue;

typedef struct {
    HashTableValue *values;
    int capacity;
    int size;
} HashTable;


HashTable *createHashTable(int capacity);

void freeHashTable(HashTable *hash_table);

void addHashTable(HashTable *hash_table, char *key, char *value);

char *getHashTable(HashTable *hash_table, char *key);

int removeHashTable(HashTable *hash_table, char *key);

unsigned long djb2_hash(const char *str);


#endif //HASHTABLE_H
