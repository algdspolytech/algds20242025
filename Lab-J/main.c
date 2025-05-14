//
//  main.c
//  Lab_J
//
//  Created by Фёдор Филь on 08.05.2025.
//

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 101

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** buckets;
    int size;
} HashTable;

HashTable* create_table(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->buckets = (Node**)calloc(size, sizeof(Node*));
    return ht;
}

int hash(int key, int size) {
    return (key % size + size) % size; // Обработка отрицательных ключей
}

void insert(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* current = ht->buckets[index];
    
    // Проверка существования ключа
    while (current) {
        if (current->key == key) return;
        current = current->next;
    }
    
    // Вставка в начало списка
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
}

void delete(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* curr = ht->buckets[index];
    Node* prev = NULL;
    
    while (curr) {
        if (curr->key == key) {
            if (prev) prev->next = curr->next;
            else ht->buckets[index] = curr->next;
            
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int search(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* current = ht->buckets[index];
    
    while (current) {
        if (current->key == key) return 1;
        current = current->next;
    }
    return 0;
}

void free_table(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* curr = ht->buckets[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

int main(void) {
    HashTable* ht = create_table(TABLE_SIZE);
    char cmd;
    int key;
    
    while (scanf(" %c %d", &cmd, &key) == 2) {
        switch(cmd) {
            case 'a': insert(ht, key); break;
            case 'r': delete(ht, key); break;
            case 'f': printf(search(ht, key) ? "yes\n" : "no\n"); break;
        }
    }
    
    free_table(ht);
    return 0;
}
