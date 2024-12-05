#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xor_linked_list.h"

Node * create_test_list(const char * data1, const char * data2, const char * data3){
    Node * head = NULL;
    listInsert(&head, data1);
    listInsert(&head, data2);
    listInsert(&head, data3);
    return head;
}

// Тесты

void test_XOR_function_CorrectlyComputesXOR_no1(){
    Node * node1 = createNode("A");
    Node * node2 = createNode("B");
    node1 -> link = XOR_function(NULL, node2);
    node2 -> link = XOR_function(node1, NULL);

    assert(XOR_function(NULL, node1 -> link) == node2);
    assert(XOR_function(NULL, node2 -> link) == node1);

    free(node1->data);
    free(node1);
    free(node2->data);
    free(node2);
}

void test_clearList_ClearNonEmptyList_HeadIsNull_no2(){
    Node * head = create_test_list("A", "B", "C");
    clearList(&head);

    assert(head == NULL);
}

void test_clearList_ClearEmptyList_HeadUnchanged_no3(){
    Node * head = NULL;
    clearList(&head);

    assert(head == NULL);
}

void test_listInsert_AddToEmptyList_HeadUpdated_no4(){
    Node * head = NULL;
    listInsert(&head, "A");

    assert(head != NULL);
    assert(strcmp(head -> data, "A") == 0);
    assert(head -> link == NULL);

    clearList(&head);
}

void test_listInsert_AddToNonEmptyList_HeadUpdated_no5(){
    Node * head = NULL;
    listInsert(&head, "A");
    listInsert(&head, "B");

    assert(head != NULL);
    assert(strcmp(head -> data, "B") == 0);
    assert(head -> link != NULL);

    clearList(&head);
}

void test_find_FindExistingElement_ReturnValidNode_no6(){
    Node * head = create_test_list("A", "B", "C");
    Node * found = find(head, "B");

    assert(found != NULL);
    assert(strcmp(found -> data, "B") == 0);

    clearList(&head);
}

void test_find_FindNonExistingElement_ReturnNULL_no7(){
    Node * head = create_test_list("A", "B", "C");
    Node * found = find(head, "D");

    assert(found == NULL);

    clearList(&head);
}

void test_deletedByKey_DeleteExistingElement_ElementRemoved_no8(){
    Node * head = create_test_list("A", "B", "C");
    deleteByKey(&head, "B");
    
    Node * found = find(head, "B");
    assert(found == NULL);

    clearList(&head);
}

void test_deleteByKey_DeleteNonExistingElement_ListUnchanged_no9(){
    Node * head = create_test_list("A", "B", "C");
    deleteByKey(&head, "D");

    assert(find(head, "A") != NULL);
    assert(find(head, "B") != NULL);
    assert(find(head, "C") != NULL);

    clearList(&head);
}

void test_deleteByAddress_DeleteExistingNode_ElementRemoves_no10(){
    Node * head = create_test_list("A", "B", "C");
    Node * to_delete = find(head, "B");
    deleteByAddress(&head, to_delete);

    Node * found = find(head, "B");
    assert(found == NULL);

    clearList(&head);
}

int main() {
    test_XOR_function_CorrectlyComputesXOR_no1();
    test_clearList_ClearNonEmptyList_HeadIsNull_no2();
    test_clearList_ClearEmptyList_HeadUnchanged_no3();
    test_listInsert_AddToEmptyList_HeadUpdated_no4();
    test_listInsert_AddToNonEmptyList_HeadUpdated_no5();
    test_find_FindExistingElement_ReturnValidNode_no6();
    test_find_FindNonExistingElement_ReturnNULL_no7();
    test_deletedByKey_DeleteExistingElement_ElementRemoved_no8();
    test_deleteByKey_DeleteNonExistingElement_ListUnchanged_no9();
    test_deleteByAddress_DeleteExistingNode_ElementRemoves_no10();
    printf("All tests passed successfully.\n");
    
    return 0;
}