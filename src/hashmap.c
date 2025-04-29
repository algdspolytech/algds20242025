#include "hashmap.h"

struct node {
    int value;
    char* key;
    struct node* next;
};

static unsigned int hash(const char* str, unsigned int size) {
    unsigned int sum = 0;
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        sum += str[i];
    }
    return sum % size;
}

struct node** createHashMap(unsigned int size) {
    struct node** map = (struct node**)malloc(size * sizeof(struct node*));
    if (!map) return NULL;

    for (unsigned int i = 0; i < size; ++i) {
        map[i] = (struct node*)malloc(sizeof(struct node));
        if (!map[i]) {
            for (unsigned int j = 0; j < i; ++j) free(map[j]);
            free(map);
            return NULL;
        }
        map[i]->key = NULL; 
        map[i]->value = 0;
        map[i]->next = NULL;
    }
    return map;
}

int insertValue(struct node** map, unsigned int size, const char* key, int val) {
    unsigned int index = hash(key, size);
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return -1;

    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return -1;
    }

    new_node->value = val;
    new_node->next = map[index]->next; 
    map[index]->next = new_node;
    return 0;
}

struct node* getVal(struct node** map, unsigned int size, const char* key) {
    unsigned int index = hash(key, size);
    struct node* current = map[index]->next; 

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteHashMap(struct node** map, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        struct node* current = map[i];
        while (current != NULL) {
            struct node* tmp = current;
            current = current->next;
            if (tmp->key) free(tmp->key);
            free(tmp);
        }
    }
    free(map);
}