#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 101
#define MAX_STRING_LEN 256

typedef enum {
    HT_OK,
    HT_ALREADY_EXISTS,
    HT_NOT_FOUND,
    HT_FULL,
} HT_Result;

int ht_init();
HT_Result ht_insert(const char* key);
HT_Result ht_search(const char* key);
HT_Result ht_delete(const char* key);
void ht_free();

#endif
