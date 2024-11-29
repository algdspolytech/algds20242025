#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include<stdlib.h>
#include<locale.h>

//�������� �������� ���� � ����������� �������
void test_createNode_ValidString_returnValidNode_no1() {
    Node* node = createNode("test");
    printf("test_createNode_ValidString_returnValidNode_no1: %i\n", (node != NULL && strcmp(node->data, "test")==0));
    free(node->data);
    free(node);
}


//�������� ���������� ������ �� 2 ��������
void test_split_NonEmptyList_returnTwoHalves_no2() {
    Node* head = createNode("first");
    Node* second = createNode("second");
    head->next = second;
    second->prev = head;

    Node* firstHalf, * secondHalf;
    split(head, &firstHalf, &secondHalf);

    printf("test_split_NonEmptyList_returnTwoHalves_no2: %i\n", (firstHalf != head || secondHalf != NULL));

    freeList(firstHalf);
    freeList(secondHalf);
}


// ���������, ���  ������� merge ��������� ���������� ��� ��������������� ������.
void test_merge_TwoSortedLists_ReturnMergedList_no3() {
    Node* first = createNode("d");
    Node* second = createNode("e");
    first->next = second;
    second->prev = first;

    Node* third = createNode("a");
    Node* fourth = createNode("b");
    third->next = fourth;
    fourth->prev = third;

    Node* merged = merge(first, third);
    printf("test_merge_TwoSortedLists_ReturnMergedList_no3: %i\n",
        (strcmp(merged->data, "a") == 0 &&
            strcmp(merged->next->data, "b") == 0 &&
            strcmp(merged->next->next->data, "d") == 0 &&
            strcmp(merged->next->next->next->data, "e") == 0));

    freeList(merged);
}

//���������, ��� ������� mergeSort ��������� ������������ ��� ��������������� ������

void test_mergeSort_AlreadySortedList_ReturnSameList_no4() {
    Node* head = createNode("a");
    head->next = createNode("b");
    head->next->prev = head;

    Node* sorted = mergeSort(head);
    printf("test_mergeSort_AlreadySortedList_ReturnSameList_no4: %i\n",
        (strcmp(sorted->data, "a") == 0 && strcmp(sorted->next->data, "b") == 0));

    freeList(sorted);
}

// �������� ������ ������� mergeSort �� ������ � ������������ �����
void test_mergeSort_SingleElementList_ReturnSameList_no5() {
    Node* head = createNode("a");

    Node* sorted = mergeSort(head);
    printf("test_mergeSort_SingleElementList_ReturnSameList_no5: %i\n",
        (strcmp(sorted->data, "a") == 0));

    freeList(sorted);
}


//  ���� ��� split �� ������ �� ������ ����
void test_Split_SingleNode_ReturnSecondHalfNULL_no6() {
    Node* head = createNode("single");

    Node* firstHalf;
    Node* secondHalf;

    split(head, &firstHalf, &secondHalf);

    printf("test_Split_SingleNode_ReturnSecondHalfNULL_no6: %i\n", (firstHalf != NULL && strcmp(firstHalf->data, "single") == 0 &&
        secondHalf == NULL));
    freeList(firstHalf);
}



//���� ��� createNode � ������ �������
void test_CreateNode_EmptyString_SaveEmpty_no7() {
    Node* node = createNode("");
    printf("test_CreateNode_EmptyString_SaveEmpty_no7: %i\n", (node != NULL && strcmp(node->data, "") == 0));
    freeList(node);
}


//�������� mergeSort �� ������ ������
void test_mergeSort_EmptyList_ReturnNull_no8() {
    Node* sorted = mergeSort(NULL);
    printf("test_mergeSort_EmptyList_ReturnNull_no8: %i\n", (sorted == NULL));
}


//���� ��� split � �������� ����������� �����
int test_Split_OddNumberOfNodes_ReturntwoNodes_no9() {
    Node* head = createNode("one");
    head->next = createNode("two");
    head->next->next = createNode("three");

    Node* firstHalf;
    Node* secondHalf;

    split(head, &firstHalf, &secondHalf);


    printf("test_Split_OddNumberOfNodes_ReturntwoNodes_no9: %i\n", (firstHalf->data != NULL && secondHalf->data != NULL));
    freeList(firstHalf);
    freeList(secondHalf);
}


//���� ��� mergeSort �� ������ � �����������
void test_MergeSort_DuplicateValues_ReturnSortTrue_no10() {
    Node* head = createNode("a");
    head->next = createNode("b");
    head->next->next = createNode("a");

    Node* sorted = mergeSort(head);


    printf("test_MergeSort_DuplicateValues_no10: %i\n", (strcmp(sorted->data, "a") == 0 &&
        strcmp(sorted->next->data, "a") == 0 &&
        strcmp(sorted->next->next->data, "b") == 0));
    freeList(sorted);
 }

int main() {
    int n;
    setlocale(LC_CTYPE, "Russian");
    //printf("������� ���������� ���� ��� ����������: ");
    //scanf("%d", &n);

    //if (n <= 0) {
    //    printf("������: ���������� ���� ������ ���� ������ ����.\n");
    //    return 1;
    //}

    //Node* head = createListFromInput(n);

    //printf("�������� ������: ");
    //printList(head);

    //head = mergeSort(head);

    //printf("��������������� ������: ");
    //printList(head);
    test_createNode_ValidString_returnValidNode_no1();
    test_split_NonEmptyList_returnTwoHalves_no2();
    test_merge_TwoSortedLists_ReturnMergedList_no3();
    test_mergeSort_AlreadySortedList_ReturnSameList_no4();
    test_mergeSort_SingleElementList_ReturnSameList_no5();
    test_Split_SingleNode_ReturnSecondHalfNULL_no6();
    test_CreateNode_EmptyString_SaveEmpty_no7();
    test_mergeSort_EmptyList_ReturnNull_no8();
    test_Split_OddNumberOfNodes_ReturntwoNodes_no9();
    test_MergeSort_DuplicateValues_ReturnSortTrue_no10();

    //freeList(head);
    return 0;
}

