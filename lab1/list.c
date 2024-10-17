#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = _strdup(data);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, const char* data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    Node* result = NULL;

    if (strcmp(left->data, right->data) <= 0) {
        result = left;
        result->next = merge(left->next, right);
        if (result->next) result->next->prev = result;
        result->prev = NULL;
    }
    else {
        result = right;
        result->next = merge(left, right->next);
        if (result->next) result->next->prev = result;
        result->prev = NULL;
    }
    return result;
}

void split(Node* source, Node** front, Node** back) {
    Node* fast = source->next;
    Node* slow = source;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* left;
    Node* right;

    if (head == NULL || head->next == NULL) {
        return;
    }

    split(head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *headRef = merge(left, right);
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%s ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(Node* node) {
    while (node != NULL) {
        Node* temp = node;
        node = node->next;
        free(temp->data);
        free(temp);
    }
}
