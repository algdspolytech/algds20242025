#pragma warning (disable: 4996)
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "tests.h"

void test_createNode_creatingNode_returnTrue() {
    Node* node = createNode("test");
    Node reference_node = { "test", NULL };
    assert((strcmp(node->str, reference_node.str) == 0) && (node->next == reference_node.next));
    free(node->str);
    free(node);
    node = NULL;
}

void test_appendNode_appendTwoNodes_returnTrue() {
    Node* head = NULL;
    Node reference_node_1 = { "first", NULL };
    Node reference_node_2 = { "second", NULL };
    reference_node_1.next = &reference_node_2;

    appendNode(&head, "first");
    appendNode(&head, "second");

    assert((strcmp(head->str, reference_node_1.str) == 0) && (head->next != NULL)); //проверка первого узла
    assert((strcmp(head->next->str, reference_node_2.str) == 0) && (head->next->next == NULL)); //проверка второго узла

    freeList(head);
}

void test_appendNode_appendFreeNode_returnTrue() {
    Node* head = NULL;
    Node reference_node_1 = { "", NULL };

    appendNode(&head, "");

    assert((strcmp(head->str, reference_node_1.str) == 0) && (head->next == NULL));

    freeList(head);
}


void test_calculateTotalLength_HelloPlusWorld_returnValidVal() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->str = (char*)malloc(strlen("hello") + 1);
    strcpy(head->str, "hello");
    head->next = NULL;

    Node* second = (Node*)malloc(sizeof(Node));
    second->str = (char*)malloc(strlen("world") + 1);
    strcpy(second->str, "world");
    second->next = NULL;

    head->next = second;

    size_t total_length = calculateTotalLength(head);

    assert(total_length == strlen("hello") + strlen("world"));

    free(head->str);
    free(head);

    free(second->str);
    free(second);
}


void test_calculateTotalLength_TwoEmptyStr_returnValidVal() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->str = (char*)malloc(strlen("") + 1);
    strcpy(head->str, "");
    head->next = NULL;

    Node* second = (Node*)malloc(sizeof(Node));
    second->str = (char*)malloc(strlen("") + 1);
    strcpy(second->str, "");
    second->next = NULL;

    head->next = second;

    size_t total_length = calculateTotalLength(head);

    assert(total_length == strlen("") + strlen(""));

    free(head->str);
    free(head);

    free(second->str);
    free(second);
}

void test_concatenateStrings_HelloPlusSpacePlusWorld_returnValidVal() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->str = (char*)malloc(strlen("Hello") + 1);
    strcpy(head->str, "Hello");
    head->next = NULL;

    Node* second = (Node*)malloc(sizeof(Node));
    second->str = (char*)malloc(strlen(" ") + 1);
    strcpy(second->str, " ");
    second->next = NULL;

    Node* third = (Node*)malloc(sizeof(Node));
    third->str = (char*)malloc(strlen("World") + 1);
    strcpy(third->str, "World");
    third->next = NULL;

    head->next = second;
    second->next = third;

    char* concatenated = concatenateStrings(head);
    assert(concatenated != NULL);
    assert(strcmp(concatenated, "Hello World") == 0);

    free(concatenated);
    freeList(head);
}

void test_concatenateStrings_EmpryPlusEmpty_returnValidVal() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->str = (char*)malloc(strlen("") + 1);
    strcpy(head->str, "");
    head->next = NULL;

    Node* second = (Node*)malloc(sizeof(Node));
    second->str = (char*)malloc(strlen("") + 1);
    strcpy(second->str, "");
    second->next = NULL;

    head->next = second;

    char* concatenated = concatenateStrings(head);
    assert(concatenated != NULL);
    assert(strcmp(concatenated, "") == 0);

    free(concatenated);
    freeList(head);
}

void TESTS() {
    printf("-------------ТЕСТИРОВАНИЕ------------\n");
    test_createNode_creatingNode_returnTrue();
    printf("+ ");
    test_appendNode_appendTwoNodes_returnTrue();
    printf("+ ");
    test_appendNode_appendFreeNode_returnTrue();
    printf("+ ");
    test_calculateTotalLength_HelloPlusWorld_returnValidVal();
    printf("+ ");
    test_calculateTotalLength_TwoEmptyStr_returnValidVal();
    printf("+ ");
    test_concatenateStrings_HelloPlusSpacePlusWorld_returnValidVal();
    printf("+ ");
    test_concatenateStrings_EmpryPlusEmpty_returnValidVal();
    printf("+ \n");
    printf("---------------ЗАВЕРШЕНО-------------\n");
}