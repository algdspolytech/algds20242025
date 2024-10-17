#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "tests.h"

void runTest(const char* testName, int result, const char* expected, const char* actual) {
    if (result) {
        printf("%s: Test passed\n", testName);
    }
    else {
        printf("%s: Test failed\nExpected: %s\nActual: %s\n", testName, expected, actual);
    }
}

int compareLists(Node* list1, Node* list2) {
    while (list1 != NULL && list2 != NULL) {
        if (strcmp(list1->data, list2->data) != 0) {
            return 0;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    if (list1 != NULL || list2 != NULL) {
        return 0;
    }
    return 1;
}

void test_createNode_1() {
    Node* node = createNode("test");
    Node* expected = createNode("test");
    runTest("test_createNode_1", strcmp(node->data, expected->data) == 0, "test", node->data);
    freeList(node);
    freeList(expected);
}

void test_append_to_empty_list_2() {
    Node* head = NULL;
    append(&head, "first");
    Node* expected = createNode("first");
    runTest("test_append_to_empty_list_2", strcmp(head->data, expected->data) == 0, "first", head->data);
    freeList(head);
    freeList(expected);
}

void test_append_to_non_empty_list_3() {
    Node* head = createNode("first");
    Node* expected = createNode("first");
    append(&expected, "second");
    append(&head, "second");
    runTest("test_append_to_non_empty_list_3", strcmp(head->next->data, expected->next->data) == 0, "second", head->next->data);
    freeList(head);
    freeList(expected);
}

void test_merge_two_sorted_lists_4() {
    Node* list1 = createNode("ab");
    append(&list1, "ad");
    Node* list2 = createNode("a");
    append(&list2, "b");
    Node* expected = createNode("a");
    append(&expected, "ab");
    append(&expected, "ad");
    append(&expected, "b");
    Node* merged = merge(list1, list2);
    runTest("test_merge_two_sorted_lists_4", compareLists(merged, expected), "a", merged->data);
    freeList(merged);
    freeList(expected);
}

void test_empty_merge_5() {
    Node* list1 = NULL;
    Node* list2 = createNode("only");
    Node* expected = createNode("only");
    Node* merged = merge(list1, list2);
    runTest("test_empty_merge_5", compareLists(merged, expected), "only", merged->data);
    freeList(merged);
    freeList(expected);
}

void test_split_list_even_6() {
    Node* head = createNode("1");
    append(&head, "2");
    append(&head, "3");
    append(&head, "4");
    Node* front, * back;
    split(head, &front, &back);
    Node* expectedFront = createNode("1");
    append(&expectedFront, "2");
    Node* expectedBack = createNode("3");
    append(&expectedBack, "4");
    runTest("test_split_list_even_6", compareLists(front, expectedFront), "1", front->data);
    runTest("test_split_list_even_6", compareLists(back, expectedBack), "3", back->data);
    freeList(front);
    freeList(back);
    freeList(expectedFront);
    freeList(expectedBack);
}

void test_split_list_odd_7() {
    Node* head = createNode("1");
    append(&head, "2");
    append(&head, "3");
    append(&head, "4");
    append(&head, "5");
    Node* front, * back;
    split(head, &front, &back);
    Node* expectedFront = createNode("1");
    append(&expectedFront, "2");
    append(&expectedFront, "3");
    Node* expectedBack = createNode("4");
    append(&expectedBack, "5");
    runTest("test_split_list_odd_7", compareLists(front, expectedFront), "1", front->data);
    runTest("test_split_list_odd_7", compareLists(back, expectedBack), "4", back->data);

    freeList(front);
    freeList(back);
    freeList(expectedFront);
    freeList(expectedBack);
}

void test_mergeSort_randomlist_8() {
    Node* head = createNode("ab");
    append(&head, "a");
    append(&head, "b");
    append(&head, "ad");

    Node* expected = createNode("a");
    append(&expected, "ab");
    append(&expected, "ad");
    append(&expected, "b");

    mergeSort(&head);
    runTest("test_mergeSort_randomlist_8", compareLists(head, expected), "a", head->data);
    freeList(head);
    freeList(expected);
}

void test_mergeSort_single_element_9() {
    Node* head = createNode("single");
    Node* expected = createNode("single");
    mergeSort(&head);
    runTest("test_mergeSort_single_element_9", compareLists(head, expected), "single", head->data);

    freeList(head);
    freeList(expected);
}

void test_mergeSort_empty_list_10() {
    Node* head = NULL;
    Node* expected = NULL;

    mergeSort(&head);
    runTest("test_mergeSort_empty_list_10", compareLists(head, expected), "NULL", "NULL");
}

void test_mergeSort_sorted_list_11() {
    Node* head = createNode("a");
    append(&head, "ab");
    append(&head, "ad");
    append(&head, "b");

    Node* expected = createNode("a");
    append(&expected, "ab");
    append(&expected, "ad");
    append(&expected, "b");

    mergeSort(&head);
    runTest("test_mergeSort_sorted_list_11", compareLists(head, expected), "a", head->data);
    freeList(head);
    freeList(expected);
}
