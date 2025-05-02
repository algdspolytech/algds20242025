#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


typedef enum {
    EMPTY,      
    OCCUPIED,   
    DELETED     
} CellState;


typedef struct {
    char* key;      
    CellState state; 
} HashEntry;


typedef struct {
    HashEntry* entries; 
    size_t capacity;    
    size_t size;        
    size_t deleted;     
} HashTable;


unsigned int hash_string(const char* str, size_t table_size) {
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = (hash * 31 + str[i]) % table_size;
    }
    return hash;
}


HashTable* create_hash_table(size_t capacity) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    table->entries = (HashEntry*)malloc(capacity * sizeof(HashEntry));
    if (!table->entries) {
        free(table);
        return NULL;
    }
    
    table->capacity = capacity;
    table->size = 0;
    table->deleted = 0;
    
    
    for (size_t i = 0; i < capacity; i++) {
        table->entries[i].key = NULL;
        table->entries[i].state = EMPTY;
    }
    
    return table;
}


bool hash_table_insert(HashTable* table, const char* key) {
    if (table->size + table->deleted >= table->capacity * 0.7) {
        return false;
    }
    
    unsigned int hash = hash_string(key, table->capacity);
    size_t index;
    int i = 0;
    
    do {
        index = (hash + i*i) % table->capacity;
        
        if (table->entries[index].state == EMPTY || 
            table->entries[index].state == DELETED) {
            
            if (table->entries[index].state == DELETED && table->entries[index].key) {
                free(table->entries[index].key);
                table->deleted--;
            }
            
            table->entries[index].key = strdup(key);
            if (!table->entries[index].key) return false;
            
            table->entries[index].state = OCCUPIED;
            table->size++;
            return true;
        }
       
        if (table->entries[index].state == OCCUPIED && 
            strcmp(table->entries[index].key, key) == 0) {
            return true; 
        }
        
        i++;
    } while (i < table->capacity); 
    
    return false; 
}

bool hash_table_search(HashTable* table, const char* key) {
    unsigned int hash = hash_string(key, table->capacity);
    size_t index;
    int i = 0;
    
    do {
        index = (hash + i*i) % table->capacity;
        
        if (table->entries[index].state == EMPTY) {
            return false;
        }
       
        if (table->entries[index].state == OCCUPIED && 
            strcmp(table->entries[index].key, key) == 0) {
            return true;
        }
        
        i++;
    } while (i < table->capacity && 
             table->entries[index].state != EMPTY);
    
    return false; 
}

bool hash_table_delete(HashTable* table, const char* key) {
    unsigned int hash = hash_string(key, table->capacity);
    size_t index;
    int i = 0;
    
    do {
        index = (hash + i*i) % table->capacity;
        
        if (table->entries[index].state == EMPTY) {
            return false;
        }
        
        if (table->entries[index].state == OCCUPIED && 
            strcmp(table->entries[index].key, key) == 0) {
            table->entries[index].state = DELETED;
            table->size--;
            table->deleted++;
            return true;
        }
        
        i++;
    } while (i < table->capacity && 
             table->entries[index].state != EMPTY);
    
    return false; 
}

void hash_table_destroy(HashTable* table) {
    if (!table) return;
    
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            free(table->entries[i].key);
        }
    }
    
    free(table->entries);
    free(table);
}

void hash_table_print(HashTable* table) {
    printf("Hash Table [size: %zu, capacity: %zu]\n", table->size, table->capacity);
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].state == OCCUPIED) {
            printf("[%zu] -> %s\n", i, table->entries[i].key);
        }
        else if (table->entries[i].state == DELETED) {
            printf("[%zu] -> (deleted)\n", i);
        }
    }
}



// Тест 1
void hash_string_SimpleString_returnExpectedHash() {
    const char* test_str = "test";
    size_t table_size = 10;
    unsigned int expected_hash = 8; 
    unsigned int actual_hash = hash_string(test_str, table_size);
    
    assert(actual_hash == expected_hash);
}

// Тест 2
void create_hash_table_ValidCapacity_returnInitializedTable() {
    size_t capacity = 5;
    
    HashTable* table = create_hash_table(capacity);
    
    assert(table != NULL);
    assert(table->entries != NULL);
    assert(table->capacity == capacity);
    assert(table->size == 0);
    assert(table->deleted == 0);
    
    for (size_t i = 0; i < capacity; i++) {
        assert(table->entries[i].state == EMPTY);
        assert(table->entries[i].key == NULL);
    }
    
    hash_table_destroy(table);
}

// Тест 3
void hash_table_insert_EmptyTable_returnTrue() {
    HashTable* table = create_hash_table(10);
    const char* key = "test";
    
    bool result = hash_table_insert(table, key);
    
    assert(result == true);
    assert(table->size == 1);
    
    hash_table_destroy(table);
}

// Тест 4
void hash_table_insert_DuplicateKey_returnTrueNoSizeChange() {
    HashTable* table = create_hash_table(10);
    const char* key = "test";
    
    hash_table_insert(table, key);
    size_t size_before = table->size;
    
    bool result = hash_table_insert(table, key);
    
    assert(result == true);
    assert(table->size == size_before); 
    
    hash_table_destroy(table);
}

// Тест 5
void hash_table_insert_CollisionResolution_returnTrue() {
    HashTable* table = create_hash_table(10);
    
    const char* key1 = "a";  
    const char* key2 = "k";  
    
    hash_table_insert(table, key1);
    bool result = hash_table_insert(table, key2);
    
    assert(result == true);
    assert(table->size == 2);
    assert(hash_table_search(table, key1)); 
    assert(hash_table_search(table, key2));
    
    hash_table_destroy(table);
}

// Тест 6
void hash_table_search_ExistingKey_returnTrue() {
    HashTable* table = create_hash_table(10);
    const char* key = "test";
    
    hash_table_insert(table, key);
    
    bool result = hash_table_search(table, key);
    
    assert(result == true);
    
    hash_table_destroy(table);
}

// Тест 7
void hash_table_search_NonExistingKey_returnFalse() {
    HashTable* table = create_hash_table(10);
    const char* key = "test";
    const char* non_existing_key = "nonexistent";
    
    hash_table_insert(table, key);
    
    bool result = hash_table_search(table, non_existing_key);
    
    assert(result == false);
    
    hash_table_destroy(table);
}

// Тест 8
void hash_table_delete_ExistingKey_returnTrue() {
    HashTable* table = create_hash_table(10);
    const char* key = "test";
    
    hash_table_insert(table, key);
    size_t size_before = table->size;
    
    bool result = hash_table_delete(table, key);
    
    assert(result == true);
    assert(table->size == size_before - 1);
    assert(table->deleted == 1);
    
    hash_table_destroy(table);
}

// Тест 9
void hash_table_delete_NonExistingKey_returnFalse() {
    HashTable* table = create_hash_table(10);
    const char* key = "test";
    const char* non_existing_key = "nonexistent";
    
    hash_table_insert(table, key);
    size_t size_before = table->size;
    
    bool result = hash_table_delete(table, non_existing_key);
    
    assert(result == false);
    assert(table->size == size_before);
    
    hash_table_destroy(table);
}

// Тест 10
void hash_table_insert_DeletedSlot_returnTrueAndDecrementDeleted() {
    HashTable* table = create_hash_table(10);

    const char* key1 = "a";  
    const char* key2 = "k";  
    
    hash_table_insert(table, key1);
    hash_table_delete(table, key1);
    size_t deleted_before = table->deleted;
    
    bool result = hash_table_insert(table, key2);
    
    assert(result == true);
    assert(table->deleted == deleted_before - 1);
    assert(hash_table_search(table, key2));
    
    hash_table_destroy(table);
}

int main() {
    hash_string_SimpleString_returnExpectedHash();
    create_hash_table_ValidCapacity_returnInitializedTable();
    hash_table_insert_EmptyTable_returnTrue();
    hash_table_insert_DuplicateKey_returnTrueNoSizeChange();
    hash_table_insert_CollisionResolution_returnTrue();
    
    hash_table_search_ExistingKey_returnTrue();
    hash_table_search_NonExistingKey_returnFalse();
    hash_table_delete_ExistingKey_returnTrue();
    hash_table_delete_NonExistingKey_returnFalse();
    hash_table_insert_DeletedSlot_returnTrueAndDecrementDeleted();

    return 0;
}
