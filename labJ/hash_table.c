
#include "hash_table.h"


unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash += (unsigned char)(*str);
        str++;
    }
    return hash % TABLE_SIZE;
}

void addNode(node_t** table, const char* key) {
    unsigned int index = hash(key);
    node_t* current = table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) return; 
        current = current->next;
    }
    node_t* new_node = malloc(sizeof(node_t));
    new_node->key = _strdup(key); 
    new_node->next = table[index];
    table[index] = new_node;
}

void deleteNode(node_t** table, const char* key) {
    unsigned int index = hash(key);
    node_t* current = table[index];
    node_t* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) prev->next = current->next;
            else table[index] = current->next;
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int findNode(node_t** table, const char* key) {
    unsigned int index = hash(key);
    node_t* current = table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) return 1;
        current = current->next;
    }
    return 0;
}
