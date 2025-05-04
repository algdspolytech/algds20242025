#include "HashTable.h"

unsigned int hash1(const char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % size;
}

unsigned int hash2(const char* key, int size) {
    unsigned int hash = 5381;
    while (*key) {
        hash = (hash << 5) + hash + *key++; 
    }
    return (hash % (size - 1)) | 1;
}

HashTable* create_hash_table(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (HashItem*)calloc(size, sizeof(HashItem));
    
    for (int i = 0; i < size; i++) {
        table->items[i].key = NULL;
        table->items[i].is_deleted = 0;
        table->items[i].is_occupied = 0;
    }
    
    return table;
}

void free_hash_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->items[i].key) {
            free(table->items[i].key);
        }
    }
    free(table->items);
    free(table);
}

void insert_with_brent(HashTable* table, const char* key) {
    if (table->count >= table->size) {
        printf("Таблица переполнена!\n");
        return;
    }
    
    unsigned int h1 = hash1(key, table->size);
    unsigned int h2 = hash2(key, table->size);
    unsigned int index = h1;
    int attempts = 0;
    
    if (!table->items[index].is_occupied || table->items[index].is_deleted) {
        table->items[index].key = strdup(key);
        table->items[index].is_occupied = 1;
        table->items[index].is_deleted = 0;
        table->count++;
        return;
    }
    
    if (strcmp(table->items[index].key, key) == 0) {
        return;
    }
    
    int i = 1;
    int empty_index = -1;
    int candidate_index = index;
    char* candidate_key = table->items[index].key;
    
    while (attempts < table->size) {
        index = (h1 + i * h2) % table->size;
        attempts++;
        
        if (!table->items[index].is_occupied || table->items[index].is_deleted) {
            if (empty_index == -1) {
                empty_index = index;
            }
            break;
        }
        
        if (strcmp(table->items[index].key, key) == 0) {
            return;
        }
        
        unsigned int new_pos_for_existing = (hash1(table->items[index].key, table->size) + 
                                           (i + 1) * hash2(table->items[index].key, table->size)) % table->size;
        
        if (!table->items[new_pos_for_existing].is_occupied || 
            table->items[new_pos_for_existing].is_deleted) {
            table->items[new_pos_for_existing].key = table->items[index].key;
            table->items[new_pos_for_existing].is_occupied = 1;
            table->items[new_pos_for_existing].is_deleted = 0;
            
            table->items[index].key = strdup(key);
            table->items[index].is_occupied = 1;
            table->items[index].is_deleted = 0;
            table->count++;
            return;
        }
        
        i++;
    }
    
    if (empty_index != -1) {
        table->items[empty_index].key = strdup(key);
        table->items[empty_index].is_occupied = 1;
        table->items[empty_index].is_deleted = 0;
        table->count++;
        return;
    }
    
    printf("Не удалось вставить ключ %s\n", key);
}

int search(HashTable* table, const char* key) {
    unsigned int h1 = hash1(key, table->size);
    unsigned int h2 = hash2(key, table->size);
    unsigned int index = h1;
    int attempts = 0;
    
    while (attempts < table->size) {
        if (table->items[index].is_occupied && !table->items[index].is_deleted) {
            if (strcmp(table->items[index].key, key) == 0) {
                return index;
            }
        } else if (!table->items[index].is_occupied && !table->items[index].is_deleted) {
            return -1; 
        }
        
        attempts++;
        index = (h1 + attempts * h2) % table->size;
    }
    
    return -1; 
}

void del(HashTable* table, const char* key) {
    int index = search(table, key);
    if (index != -1) {
        free(table->items[index].key);
        table->items[index].key = NULL;
        table->items[index].is_deleted = 1;
        table->count--;
    }
}

