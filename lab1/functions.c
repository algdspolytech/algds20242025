#pragma warning (disable: 4996)
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

Node* createNode(const char* s) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    new_node->str = strdup(s);
    new_node->next = NULL;
    return new_node;
}

void appendNode(Node** head, const char* s) {
    Node* new_node = createNode(s);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->str);
        free(temp);
    }
}

size_t calculateTotalLength(Node* head) {
    size_t total_length = 0;
    Node* current = head;
    while (current != NULL) {
        total_length += strlen(current->str);
        current = current->next;
    }
    return total_length;
}

char* concatenateStrings(Node* head) {
    size_t total_length = calculateTotalLength(head);
    char* result = (char*)malloc(total_length + 1);
    if (!result) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    result[0] = '\0';
    Node* current = head;
    while (current != NULL) {
        strcat(result, current->str);
        current = current->next;
    }
    return result;
}