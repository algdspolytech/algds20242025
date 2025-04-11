#ifndef LABA_H
#define LABA_H

#include <stdbool.h>

typedef struct Node {
    char* data;          // ASCII-Z строка
    struct Node* np;     // XOR указатель
} Node;

typedef struct XORList {
    Node* head;          // первый элемент
    Node* tail;          // последний элемент
} XORList;

// инициализация 
void init_list(XORList* list);

// добавить элемент
bool add_element(XORList* list, const char* data);

// удалить элемент по ключу
bool remove_by_key(XORList* list, const char* key);

// удалить элемент по адресу
bool remove_by_address(XORList* list, Node* address);

// искать элемент по ключу
Node* find_by_key(const XORList* list, const char* key);

// итерировать (возвращает следующий узел)
Node* iterate_list(Node* prev, Node* current);

#endif