#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "header_A19.h"


list_t* CreateList(void) {
    list_t* list = malloc(sizeof(list_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void DestroyList(list_t* list) {
    if (list == NULL) return;
    while (list->head != NULL) {
        node_t* p = list->head;
        list->head = list->head->next;
        free(p->data); // ñòðîêó
        free(p);       // óçåë
    }
    free(list); //  ñïèñîê
}

void PrintLine(char* str) {
    while ((*str) != 0) {
        printf("%c", *str);
        str++;
    }
}

void PrintList(list_t* list) {
    node_t* tmp = list->head;
    while (tmp != NULL) {
        PrintLine(tmp->data);
        printf("\n");
        tmp = tmp->next;
    }
}

int Length(char* str) {
    int len = 0;
    while (str[len] != 0) len++;
    return len;
}

char* CopyStr(char* from) {
    int length = Length(from), i;
    char* to = malloc((length + 1) * sizeof(char));
    if (to == NULL) return NULL;
    for (i = 0; i <= length; i++) {
        to[i] = from[i];
    }
    return to;
}

void AddToList(list_t* list, char data[]) {
    node_t* newNode = malloc(sizeof(node_t));
    if (newNode == NULL) return;
    newNode->data = CopyStr(data);
    newNode->next = list->head;
    newNode->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = newNode;
    }
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void SwapNodes(node_t* a, node_t* b) {
    char* temp = a->data;
    a->data = b->data;
    b->data = temp;
}

list_t* SortList(list_t* list) {
    if (list == NULL || list->head == NULL) {
        return list;
    }

    int swapped;
    node_t* ptr1;
    node_t* lptr = NULL;

    //ïóçûðüêîì
    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                SwapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return list;
}


char* GetElement(list_t* list, int index) {
    node_t* current = list->head;
    for (int i = 0; i < index; i++) {
        if (current == NULL) return NULL; // если индекс выходит за пределы
        current = current->next;
    }
    return current ? current->data : NULL;
}
