#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct HashTable {
    char** keys;
    bool* occupied;
    size_t size;
    size_t count;
} HashTable;

size_t hash1(const char* key, size_t size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % size;
}

size_t hash2(const char* key, size_t size) {
    unsigned long hash = 0;
    int c;
    while ((c = *key++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    size_t h2 = (hash % (size - 1)) + 1;
    return h2 == 0 ? 1 : h2;
}

HashTable* createHashTable(size_t size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->keys = (char**)malloc(size * sizeof(char*));
    table->occupied = (bool*)calloc(size, sizeof(bool));

    if (!table->keys || !table->occupied) {
        free(table->keys);
        free(table->occupied);
        free(table);
        return NULL;
    }

    table->size = size;
    table->count = 0;
    return table;
}

void destroyHashTable(HashTable* table) {
    if (table) {
        for (size_t i = 0; i < table->size; i++) {
            if (table->occupied[i]) {
                free(table->keys[i]);
            }
        }
        free(table->keys);
        free(table->occupied);
        free(table);
    }
}

bool insert(HashTable* table, const char* key) {
    if (table->count >= table->size) return false;

    size_t h1 = hash1(key, table->size);
    size_t h2 = hash2(key, table->size);
    size_t index = h1;
    size_t attempts = 0;

    while (attempts < table->size) {
        if (!table->occupied[index]) {
            char* new_key = _strdup(key);
            if (!new_key) return false;

            table->keys[index] = new_key;
            table->occupied[index] = true;
            table->count++;
            return true;
        }
        else if (strcmp(table->keys[index], key) == 0) {
            return false;
        }
        else {
            char* existing_key = table->keys[index];
            size_t existing_h1 = hash1(existing_key, table->size);
            size_t existing_h2 = hash2(existing_key, table->size);
            size_t new_index = (existing_h1 + existing_h2) % table->size;
            size_t steps = 1;
            bool moved = false;

            while (steps < table->size) {
                if (new_index == index) break;

                if (!table->occupied[new_index]) {
                    char* new_key = _strdup(key);
                    if (!new_key) break;

                    table->keys[new_index] = existing_key;
                    table->occupied[new_index] = true;

                    table->keys[index] = new_key;
                    table->count++;
                    return true;
                }

                new_index = (new_index + existing_h2) % table->size;
                steps++;
            }

            index = (index + h2) % table->size;
            attempts++;
        }
    }
    return false;
}

bool contains(HashTable* table, const char* key) {
    size_t h1 = hash1(key, table->size);
    size_t h2 = hash2(key, table->size);
    size_t index = h1;
    size_t attempts = 0;

    while (attempts < table->size) {
        if (!table->occupied[index]) return false;
        if (strcmp(table->keys[index], key) == 0) return true;

        index = (index + h2) % table->size;
        attempts++;
    }
    return false;
}

void testCreateEmptyTable() {
    HashTable* table = createHashTable(10);

    assert(table != NULL);
    assert(table->size == 10);
    assert(table->count == 0);
    assert(table->keys != NULL);
    assert(table->occupied != NULL);

    for (size_t i = 0; i < table->size; i++) {
        assert(table->occupied[i] == false);
    }
}

void testInsertIntoEmptyTable() {
    HashTable* table = createHashTable(5);

    bool result = insert(table, "test");
    assert(result == true);
    assert(table->count == 1);
    assert(table->occupied[hash1("test", 5)] == true);
    assert(strcmp(table->keys[hash1("test", 5)], "test") == 0);
}

void testInsertDuplicate() {
    HashTable* table = createHashTable(5);
    insert(table, "apple");

    bool result = insert(table, "apple");
    assert(result == false);
    assert(table->count == 1);
}

void testBrentCollisionResolution() {
    HashTable* table = createHashTable(3);

    insert(table, "a");
    insert(table, "b");

    assert(contains(table, "a"));
    assert(contains(table, "b"));
}

void testContainsExisting() {
    HashTable* table = createHashTable(10);
    insert(table, "apple");

    assert(contains(table, "apple") == true);
}

void testContainsMissing() {
    HashTable* table = createHashTable(10);
    insert(table, "apple");

    assert(contains(table, "banana") == false);
}

void testTableOverflow() {
    HashTable* table = createHashTable(2);
    insert(table, "a");
    insert(table, "b");

    bool result = insert(table, "c");
    assert(result == false);
}

void testInsertIntoNonEmptyTable() {
    HashTable* table = createHashTable(10);
    assert(insert(table, "apple") == true);
    assert(table->count == 1);
    assert(insert(table, "banana") == true);
    assert(table->count == 2);
    assert(insert(table, "orange") == true);
    assert(table->count == 3);
    assert(contains(table, "apple") == true);
    assert(contains(table, "banana") == true);
    assert(contains(table, "orange") == true);
}

void testHashFunctions() {
    size_t size = 100;
    const char* key1 = "hello";
    const char* key2 = "world";

    assert(hash1(key1, size) != hash1(key2, size));
    assert(hash2(key1, size) != hash2(key2, size));
    assert(hash2("test", size) != 0);
}

void testBrentMoving() {
    HashTable* table = createHashTable(5);

    insert(table, "a");
    insert(table, "b");

    bool result = insert(table, "c");
    assert(result == true);
    assert(table->count == 3);

    assert(contains(table, "a"));
    assert(contains(table, "b"));
    assert(contains(table, "c"));
}

int main() {
    testCreateEmptyTable();
    testInsertIntoEmptyTable();
    testInsertDuplicate();
    testBrentCollisionResolution();
    testContainsExisting();
    testContainsMissing();
    testTableOverflow();
    testInsertIntoNonEmptyTable();
    testHashFunctions();
    testBrentMoving();
    return 0;
}
