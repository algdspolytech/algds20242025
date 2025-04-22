#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define TABLE_SIZE 1000003

typedef struct Node {
    char* key;
    long long hash;
    struct Node* next;
} Node;

Node* hash_table[TABLE_SIZE];

unsigned int hash(const char* str) {
    unsigned int hash = 5381;
    char c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

char* fast_strdup(const char* str) {
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1);
    if (copy) memcpy(copy, str, len + 1);
    return copy;
}

void insert(const char* key) {
    unsigned int hash_key = hash(key);
    unsigned int idx = hash_key % TABLE_SIZE;
    Node* node = hash_table[idx];
    while (node) {
        if (node->hash == hash_key)
            return;
        node = node->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->hash = hash_key;
    new_node->key = fast_strdup(key);
    new_node->next = hash_table[idx];
    hash_table[idx] = new_node;
}

void delete(const char* key) {
    unsigned int hash_key = hash(key);
    unsigned int idx = hash_key % TABLE_SIZE;
    Node* node = hash_table[idx], * prev = NULL;

    while (node) {
        if (node->hash == hash_key) {
            if (prev)
                prev->next = node->next;
            else
                hash_table[idx] = node->next;
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

int find(const char* key) {
    unsigned int hash_key = hash(key);
    unsigned int idx = hash_key % TABLE_SIZE;
    Node* node = hash_table[idx];
    while (node) {
        if (node->hash == hash_key)
            return 1;
        node = node->next;
    }
    return 0;
}

int main() {
    char cmd;
    char buffer[1024];

    while (scanf(" %c %1023s", &cmd, buffer) == 2) { 
        if (cmd == 'a') {
            insert(buffer);
        }
        else if (cmd == 'r') {
            delete(buffer);
        }
        else if (cmd == 'f') {
            printf("%s\n", find(buffer) ? "yes" : "no");
        }
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* node = hash_table[i];
        while (node) {
            Node* tmp = node;
            node = node->next;
            free(tmp->key);
            free(tmp);
        }
    }

    return 0;
}