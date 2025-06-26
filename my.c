#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 1024

typedef enum { EMPTY, OCCUPIED, REMOVED } Status;

typedef struct {
    char* key;
    Status state;
} Entry;

typedef struct {
    Entry* arr;
    size_t size;
    size_t count;
} HashTable;

// strdup
char* my_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* res = malloc(len);
    if (!res) exit(1);
    memcpy(res, s, len);
    return res;
}

// djb2 hash
unsigned long djb2(const char* s) {
    unsigned long h = 5381;
    int c;
    while ((c = (unsigned char)*s++))
        h = ((h << 5) + h) + c;
    return h;
}

void table_init(HashTable* t, size_t sz) {
    t->arr = calloc(sz, sizeof(Entry));
    t->size = sz;
    t->count = 0;
    if (!t->arr) exit(1);
}

void entry_free(Entry* e) {
    if (e->state == OCCUPIED && e->key) {
        free(e->key);
        e->key = NULL;
    }
    e->state = REMOVED;
}

void table_free(HashTable* t) {
    for (size_t i = 0; i < t->size; ++i) {
        entry_free(&t->arr[i]);
    }
    free(t->arr);
}

void table_rehash(HashTable* t) {
    size_t old_size = t->size;
    Entry* old_arr = t->arr;
    size_t new_size = old_size * 2;
    Entry* new_arr = calloc(new_size, sizeof(Entry));
    if (!new_arr) exit(1);
    size_t new_count = 0;
    for (size_t i = 0; i < old_size; ++i) {
        if (old_arr[i].state == OCCUPIED) {
            unsigned long h = djb2(old_arr[i].key) % new_size;
            size_t idx;
            size_t j;
            for (j = 0; j < new_size; ++j) {
                idx = (h + j * j) % new_size;
                if (new_arr[idx].state == OCCUPIED && strcmp(new_arr[idx].key, old_arr[i].key) == 0)
                    break;
                if (new_arr[idx].state == EMPTY || new_arr[idx].state == REMOVED) {
                    new_arr[idx].key = old_arr[i].key;
                    new_arr[idx].state = OCCUPIED;
                    ++new_count;
                    break;
                }
            }
        }
    }
    free(old_arr);
    t->arr = new_arr;
    t->size = new_size;
    t->count = new_count;
}

int table_find(HashTable* t, const char* s) {
    unsigned long h = djb2(s) % t->size;
    size_t idx;
    for (size_t i = 0; i < t->size; ++i) {
        idx = (h + i * i) % t->size;
        if (t->arr[idx].state == EMPTY)
            return 0;
        if (t->arr[idx].state == OCCUPIED && strcmp(t->arr[idx].key, s) == 0)
            return 1;
    }
    return 0;
}

void table_insert(HashTable* t, const char* s) {
    if (table_find(t, s)) return;
    if (t->count * 10 > t->size * 7)
        table_rehash(t);
    unsigned long h = djb2(s) % t->size;
    size_t idx;
    size_t first_del = (size_t)(-1);
    for (size_t i = 0; i < t->size; ++i) {
        idx = (h + i * i) % t->size;
        if (t->arr[idx].state == REMOVED && first_del == (size_t)(-1))
            first_del = idx;
        if (t->arr[idx].state == EMPTY) {
            size_t use = (first_del != (size_t)(-1) ? first_del : idx);
            t->arr[use].key = my_strdup(s);
            if (!t->arr[use].key) exit(1);
            t->arr[use].state = OCCUPIED;
            t->count++;
            return;
        }
    }
    if (first_del != (size_t)(-1)) {
        t->arr[first_del].key = my_strdup(s);
        if (!t->arr[first_del].key) exit(1);
        t->arr[first_del].state = OCCUPIED;
        t->count++;
    }
}

void table_remove(HashTable* t, const char* s) {
    unsigned long h = djb2(s) % t->size;
    size_t idx;
    for (size_t i = 0; i < t->size; ++i) {
        idx = (h + i * i) % t->size;
        if (t->arr[idx].state == EMPTY)
            return;
        if (t->arr[idx].state == OCCUPIED && strcmp(t->arr[idx].key, s) == 0) {
            entry_free(&t->arr[idx]);
            t->count--;
            return;
        }
    }
}

void process(HashTable* t, char cmd, const char* word) {
    if (cmd == 'a') {
        table_insert(t, word);
    } else if (cmd == 'r') {
        table_remove(t, word);
    } else if (cmd == 'f') {
        puts(table_find(t, word) ? "yes" : "no");
    }
}

int main() {
    HashTable t;
    table_init(&t, INIT_SIZE);
    char cmd, word[512];
    while (scanf(" %c %511s", &cmd, word) == 2) {
        process(&t, cmd, word);
    }
    table_free(&t);
    return 0;
}
