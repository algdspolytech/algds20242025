#include "xor_linked_list.h"

Node* XOR(Node* a, Node* b) {
    return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

Node* add(Node* head, char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (!newNode) {
        fprintf(stderr, "error buffer memory for Node\n");
        return head;
    }

    unsigned dataSize = strlen(data);
    char* newData = (char*)malloc(sizeof(char) * (dataSize + 1));

    if (!newData) {
        fprintf(stderr, "error buffer memory for data\n");
        free(newNode);
        return head;
    }

    strcpy_s(newData, dataSize + 1, data);
    newNode->data = newData;
    newNode->dataSize = dataSize;
    newNode->xor_addr = head;

    if (head == NULL) {
        return newNode;
    }

    Node* curr = head;
    Node* prev = NULL;
    Node* next = XOR(prev, curr->xor_addr);

    while (next != NULL) {
        prev = curr;
        curr = next;
        next = XOR(prev, curr->xor_addr);
    }

    curr->xor_addr = XOR(prev, newNode);
    newNode->xor_addr = curr;

    return head;
}

Node* find(Node* head, char* key) {
    Node* curr = head;
    Node* prev = NULL;
    Node* next;

    while ((uintptr_t)curr & 0xFFFFFF000000) {
        //printf("%p", (uintptr_t)curr & 0xFFFFFFFF0000);
        if (strcmp(curr->data, key) == 0) {
            return curr;
        }
        next = XOR(prev, curr->xor_addr);
        prev = curr;
        curr = next;
    }
    return NULL;
}

Node* deleteNode(Node* head, Node* node) {
    if (head == NULL || node == NULL) {
        return head;
    }

    Node* curr = head;
    Node* prev = NULL;
    Node* next;

    while (curr != NULL) {
        next = XOR(prev, curr->xor_addr);

        if (curr == node) {
            if (prev != NULL) {
                prev->xor_addr = XOR(XOR(prev->xor_addr, curr), next);
            }
            if (next != NULL) {
                next->xor_addr = XOR(XOR(next->xor_addr, curr), prev);
            }
            if (curr == head) {
                head = next;
            }
            free(curr->data);
            free(curr);
            return head;
        }

        prev = curr;
        curr = next;
    }

    return head;
}

Node* deleteByKey(Node* head, char* key) {
    Node* node = find(head, key);
    if (node) {
        return deleteNode(head, node);
    }
    return head;
}

void iterate(Node* head) {
    if (!((uintptr_t)head & 0xFFFFFF000000)) {
        return;
    }
    Node* curr = head;
    Node* prev = NULL;
    Node* next;

    while ((uintptr_t)curr & 0xFFFFFF000000) {
        for (unsigned i = 0; i < curr->dataSize; i++) {
            printf("%c", curr->data[i]);
        }
        printf(" ");
        next = XOR(prev, curr->xor_addr);
        prev = curr;
        curr = next;
    }
    printf("\n");
}