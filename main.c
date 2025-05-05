#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define TABLE_SIZE 199999
#define MAX_KEY_LEN 256
#define FNV_PRIME_32 16777619u
#define FNV_OFFSET_BASIS_32 2166136261u
typedef struct Node {
    char* key;
    struct Node* next;
} Node;
Node* hash_table[TABLE_SIZE];
unsigned int fnv1a_hash(const char* key) {
    uint32_t hash = FNV_OFFSET_BASIS_32;
    while (*key) {
        hash ^= (uint32_t)(unsigned char)(*key);
        hash *= FNV_PRIME_32;
        key++;
    }
    return hash % TABLE_SIZE;
}
void insert_item(const char* key) {
    unsigned int index = fnv1a_hash(key);
    Node* current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return;
        }
        current = current->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    size_t key_len = strlen(key);
    new_node->key = (char*)malloc(key_len + 1);
    memcpy(new_node->key, key, key_len + 1);

    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}
void remove_item(const char* key) {
    unsigned int index = fnv1a_hash(key);
    Node* current = hash_table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hash_table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
bool find_item(const char* key) {
    unsigned int index = fnv1a_hash(key);
    Node* current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
void free_table() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = hash_table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}
int main() {
    char operation;
    char key_str[MAX_KEY_LEN];

    while (scanf(" %c %s", &operation, key_str) == 2) {
        switch (operation) {
        case 'a':
            insert_item(key_str);
            break;
        case 'r':
            remove_item(key_str);
            break;
        case 'f':
            if (find_item(key_str)) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
            break;
        }
    }

    free_table();
    return 0;
}