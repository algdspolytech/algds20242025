
#include "xorList.h"   

Node* xor (Node* a, Node* b) {
    return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}

Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

xorList* createList() {
    xorList* list = (xorList*)malloc(sizeof(xorList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

xorList* add(xorList* list, const char* data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        newNode->link = xor (list->tail, NULL);
        list->tail->link = xor (list->tail->link, newNode);
        list->tail = newNode;
    }
    return list;
}
Node* find(xorList* list, const char* data) {
    Node* cur = list->head;
    Node* prev = NULL;
    Node* next;

    while (cur != NULL) {
        if (strcmp(cur->data, data) == 0) {
            return cur;
        }
        next = xor (prev, cur->link);
        prev = cur;
        cur = next;
    }
    return 0;
}
xorList* delByAd(xorList* list, Node* link) {
    Node* cur = list->head;
    Node* prev = NULL;
    Node* next;

    while (cur != NULL) {
        next = xor (prev, cur->link);

        if (cur->link == link) {
            if (prev != NULL) {
                prev->link = xor (xor (prev->link, cur), next);
            }
            if (next != NULL) {
                next->link = xor (xor (next->link, cur), prev);
            }
            if (cur == list->head) {
                list->head = next;
            }
            cur->data = NULL;
            free(cur);
            return;
        }
        prev = cur;
        cur = next;
    }
    return list;
}
xorList* delByD(xorList* list, const char* data) {
    Node* cur = find(list, data);
    if (cur) {
        delByAd(list, cur->link);
    }
    return list;
}
void iter(xorList* list) {
    Node* cur = list->head;
    Node* prev = NULL;
    Node* next;

    while (cur != NULL) {
        printf("%s ", cur->data);
        next = xor (prev, cur->link);
        prev = cur;
        cur = next;
    }
    printf("\n");
}
xorList* freeList(xorList* list) {

    Node* cur = list->head;
    Node* prev = NULL;
    Node* next;

    while (cur != NULL) {
        next = xor (prev, cur->link);
        cur->data = NULL;
        free(cur);
        prev = cur;
        cur = next;
    }
    free(list);
    return NULL;
}
