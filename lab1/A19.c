#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



typedef struct node {
    char* data;
    struct node* next;
    struct node* prev;
} node_t;

typedef struct {
    node_t* head;
    node_t* tail;
} list_t;

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
        free(p->data); // строку
        free(p);       // узел
    }
    free(list); //  список
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

    //пузырьком
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
void utest_1() {
    list_t* myList = CreateList();
    AddToList(myList, "abcd");
    AddToList(myList, "bcdef");
    AddToList(myList, "cdefg");

    printf("\nBefore sorting 1:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_2() {
    list_t* myList = CreateList();
    AddToList(myList, " 12%");
    AddToList(myList, "123%");
    AddToList(myList, "1234%");

    printf("\nBefore sorting 2:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_3() {
    list_t* myList = CreateList();
    AddToList(myList, "1");
    AddToList(myList, "mmm");
    AddToList(myList, "123");

    printf("\nBefore sorting 3:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_4() {
    list_t* myList = CreateList();
    AddToList(myList, "!!!");
    AddToList(myList, "1");
    AddToList(myList, "0");

    printf("\nBefore sorting 4:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}


void utest_5() {
    list_t* myList = CreateList();
    AddToList(myList, "1 2 3");
    AddToList(myList, "a 3 4 5");
    AddToList(myList, "a b c d");

    printf("\nBefore sorting 5:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_6() {
    list_t* myList = CreateList();
    AddToList(myList, "1      2");
    AddToList(myList, "13");
    AddToList(myList, "123");

    printf("\nBefore sorting 6:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}


void utest_7() {
    list_t* myList = CreateList();
    AddToList(myList, "how are you ");
    AddToList(myList, "are");
    AddToList(myList, "how are");

    printf("\nBefore sorting 7:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_8() {
    list_t* myList = CreateList();
    AddToList(myList, "ABC");
    AddToList(myList, "aaa");
    AddToList(myList, "abc");

    printf("\nBefore sorting 8:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}


void utest_9() {
    list_t* myList = CreateList();
    AddToList(myList, "###0123");
    AddToList(myList, "##abcd");
    AddToList(myList, "ABCD");

    printf("\nBefore sorting 9:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_10() {
    list_t* myList = CreateList();
    AddToList(myList, "aaaaaaa");
    AddToList(myList, "a");
    AddToList(myList, "aaa");

    printf("\nBefore sorting 10:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

int main() {
    utest_1();
    utest_2();
    utest_3();
    utest_4();
    utest_5();
    utest_6();
    utest_7();
    utest_8();
    utest_9();
    utest_10();
    return 0;
}
