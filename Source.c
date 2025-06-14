#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#pragma warning(disable: 4996)

#define INITIAL_CAPACITY 1024

typedef enum { EMPTY, USED, DELETED } EntryState;

typedef struct {
    char* key;
    EntryState state;
} Entry;

typedef struct {
    Entry* entries;
    size_t  capacity;
    size_t  count;
} HashTable;



static HashTable* Create(size_t cap) {
    HashTable* ht = malloc(sizeof(*ht));
    if (!ht) exit(EXIT_FAILURE);
    ht->capacity = cap;
    ht->count = 0;
    ht->entries = calloc(cap, sizeof(*ht->entries));
    if (!ht->entries) exit(EXIT_FAILURE);
    return ht;
}


static void Free(HashTable* ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->capacity; i++) {
        if (ht->entries[i].state == USED)
            free(ht->entries[i].key);
    }
    free(ht->entries);
    free(ht);
}

static unsigned long long DJB2(const char* s) {
    unsigned long long h = 5381;
    unsigned char c;
    while ((c = (unsigned char)*s++))
        h = ((h << 5) + h) + c;
    return h;
}


static void Rehash(HashTable* ht) {
    size_t old_cap = ht->capacity;
    Entry* old_table = ht->entries;

    size_t new_cap = old_cap * 2;
    Entry* new_table = calloc(new_cap, sizeof(*new_table));
    if (!new_table) exit(EXIT_FAILURE);

    for (size_t i = 0; i < old_cap; i++) {
        if (old_table[i].state == USED) {
            unsigned long long h = DJB2(old_table[i].key);
            size_t base = (size_t)(h % new_cap);
            size_t offset = 0;

            for (size_t j = 0; j < new_cap; j++) {
                if (j) offset += 2 * j - 1;
                size_t idx = (base + offset) % new_cap;
                if (new_table[idx].state == EMPTY) {
                    new_table[idx].key = old_table[i].key;
                    new_table[idx].state = USED;
                    break;
                }
            }
        }
    }

    free(old_table);
    ht->entries = new_table;
    ht->capacity = new_cap;
}

static void Insert(HashTable* ht, const char* key) {
    if (ht->count * 10 > ht->capacity * 7)
        Rehash(ht);

    unsigned long long h = DJB2(key);
    size_t base = (size_t)(h % ht->capacity);
    size_t offset = 0;
    int    first_del = -1;

    for (size_t i = 0; i < ht->capacity; i++) {
        if (i) offset += 2 * i - 1;
        size_t idx = (base + offset) % ht->capacity;
        Entry* e = &ht->entries[idx];

        if (e->state == USED) {
            if (strcmp(e->key, key) == 0)
                return;
        }
        else if (e->state == DELETED) {
            if (first_del < 0) first_del = (int)idx;
        }
        else {
            size_t use = (first_del >= 0 ? (size_t)first_del : idx);
            Entry* u = &ht->entries[use];
            u->key = strdup(key);
            if (!u->key) exit(EXIT_FAILURE);
            u->state = USED;
            ht->count++;
            return;
        }
    }
}

static void Delete(HashTable* ht, const char* key) {
    unsigned long long h = DJB2(key);
    size_t base = (size_t)(h % ht->capacity);
    size_t offset = 0;

    for (size_t i = 0; i < ht->capacity; i++) {
        if (i) offset += 2 * i - 1;
        size_t idx = (base + offset) % ht->capacity;
        Entry* e = &ht->entries[idx];

        if (e->state == EMPTY) return;
        if (e->state == USED && strcmp(e->key, key) == 0) {
            free(e->key);
            e->key = NULL;
            e->state = DELETED;
            ht->count--;
            return;
        }
    }
}

static int Contains(HashTable* ht, const char* key) {
    unsigned long long h = DJB2(key);
    size_t base = (size_t)(h % ht->capacity);
    size_t offset = 0;

    for (size_t i = 0; i < ht->capacity; i++) {
        if (i) offset += 2 * i - 1;
        size_t idx = (base + offset) % ht->capacity;
        Entry* e = &ht->entries[idx];
        if (e->state == EMPTY) return 0;
        if (e->state == USED && strcmp(e->key, key) == 0)
            return 1;
    }
    return 0;
}

int main() {
    HashTable* ht = Create(INITIAL_CAPACITY);
    char cmd, buf[512];

    while (scanf(" %c %511s", &cmd, buf) == 2) {
        if (cmd == 'a') {
            Insert(ht, buf);
        }
        else if (cmd == 'r') {
            Delete(ht, buf);
        }
        else if (cmd == 'f') {
            puts(Contains(ht, buf) ? "yes" : "no");
        }
    }

    Free(ht);
    return 0;
}