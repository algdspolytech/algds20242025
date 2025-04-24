#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

HashTable *createHashTable(int capacity) {
    if (capacity <= 0) {
        capacity = 1;
    }

    HashTable *hash_table = malloc(sizeof(HashTable));
    hash_table->capacity = capacity;
    hash_table->size = 0;
    hash_table->values = calloc(hash_table->capacity, sizeof(HashTableValue));
    for (int i = 0; i < hash_table->capacity; i++) {
        hash_table->values[i].key = NULL;
        hash_table->values[i].deleted = 0;
    }
    return hash_table;
}

void freeHashTable(HashTable *hash_table) {
    free(hash_table->values);
    free(hash_table);
}

unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void resize(HashTable *hash_table) {
    size_t new_capacity = hash_table->capacity * 2;

    HashTableValue *new_values = calloc(new_capacity, sizeof(HashTableValue));

    for (int i = 0; i < hash_table->capacity; i++) {
        if (hash_table->values[i].key != NULL) {
            size_t new_index = djb2_hash(hash_table->values[i].key) % new_capacity;
            int j = 0;
            while (j < new_capacity && new_values[new_index].key != NULL) {
                j++;
                new_index = (new_index + j * j) % new_capacity;
            }
            new_values[new_index].key = hash_table->values[i].key;
            new_values[new_index].value = hash_table->values[i].value;
            new_values[new_index].deleted = 0;
        }
    }

    free(hash_table->values);
    hash_table->values = new_values;
    hash_table->capacity = new_capacity;
}

void addHashTable(HashTable *hash_table, char *key, char *value) {
    int index = djb2_hash(key) % hash_table->capacity;

    if (((double) hash_table->size + 1) / (hash_table->capacity) >= 0.7) resize(hash_table);

    int i = 0;
    int current_index = index;
    while (hash_table->values[current_index].key != NULL && i < hash_table->capacity) {
        if (strcmp(hash_table->values[current_index].key, key) == 0) break;
        i++;
        current_index = (index + i * i) % hash_table->capacity;
    }

    hash_table->values[current_index].key = key;
    hash_table->values[current_index].value = value;
    hash_table->size++;
}


char *getHashTable(HashTable *hash_table, char *key) {
    int index = djb2_hash(key) % hash_table->capacity;
    int i = 0;
    while (i < hash_table->capacity) {
        int next_index = (index + i * i) % hash_table->capacity;
        if (hash_table->values[next_index].key != NULL) {
            if (strcmp(hash_table->values[next_index].key, key) == 0) {
                return hash_table->values[next_index].value;
            }
        } else {
            if (!hash_table->values[next_index].deleted) return NULL;
        }
        i++;
    }
    return NULL;
}


int removeHashTable(HashTable *hash_table, char *key) {
    int index = djb2_hash(key) % hash_table->capacity;
    int i = 0;

    while (i < hash_table->capacity) {
        int current_index = (index + i * i) % hash_table->capacity;

        if (hash_table->values[current_index].key != NULL &&
            strcmp(hash_table->values[current_index].key, key) == 0) {
            // free(hash_table->values[current_index].key);
            // free(hash_table->values[current_index].value);

            hash_table->values[current_index].key = NULL;
            hash_table->values[current_index].value = NULL;
            hash_table->values[current_index].deleted = 1;
            hash_table->size--;
            return 1;
        }

        if (!hash_table->values[current_index].deleted) break;

        i++;
    }
    return 0;
}

// int main(void) {
//     HashTable* hash_table = createHashTable(10);
//     addHashTable(hash_table, "key1", "value1");
//     printf("\n %s", getHashTable(hash_table, "key1"));
//     removeHashTable(hash_table, "key1");
//     printf("\n %s", getHashTable(hash_table, "key1"));
//     freeHashTable(hash_table);
//     return 0;
// }
