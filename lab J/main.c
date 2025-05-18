#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100003

typedef enum { EMPTY, OCCUPIED, DELETED } slot_status_t;
typedef struct {
    char* key;
    slot_status_t  status;
} entry_t;

static entry_t table[TABLE_SIZE];

void init_table(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = NULL;
        table[i].status = EMPTY;
    }
}

static unsigned int hash_str(const char* s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++))
        h = ((h << 5) + h) + c;
    return (unsigned int)(h % TABLE_SIZE);
}

static int find_pos(const char* key) {
    unsigned int h0 = hash_str(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (h0 + i) % TABLE_SIZE;
        if (table[idx].status == EMPTY)
            return -1;
        if (table[idx].status == OCCUPIED && strcmp(table[idx].key, key) == 0)
            return idx;
    }
    return -1;
}

void addEntry(const char* key) {
    if (find_pos(key) != -1) return;
    unsigned int h0 = hash_str(key);
    int first_del = -1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (h0 + i) % TABLE_SIZE;
        if (table[idx].status == DELETED && first_del < 0)
            first_del = idx;
        if (table[idx].status == EMPTY) {
            int pos = (first_del >= 0 ? first_del : idx);
            table[pos].key = _strdup(key);
            table[pos].status = OCCUPIED;
            return;
        }
    }
}

void deleteEntry(const char* key) {
    int pos = find_pos(key);
    if (pos < 0) return;
    free(table[pos].key);
    table[pos].key = NULL;
    table[pos].status = DELETED;
}

int findEntry(const char* key) {
    return find_pos(key) >= 0;
}

void run_tests(void);

int main(void) {
    run_tests();
    return 0;
}