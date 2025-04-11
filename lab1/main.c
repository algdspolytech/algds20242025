#include "labA.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

// ���������� �������� � ������ ������
void test_addElement_EmptyList_returnValidVal_no1() {
    XORList list;
    init_list(&list);
    bool result = add_element(&list, "test");
    assert(result == true && strcmp(list.head->data, "test") == 0);
}

// �������� �������� �� ������� ������
void test_removeByKey_EmptyList_returnFalse_no2() {
    XORList list;
    init_list(&list);
    bool result = remove_by_key(&list, "test");
    assert(result == false);
}

// �������� ������������� �������� �� �����
void test_removeByKey_ExistingElement_returnTrue_no3() {
    XORList list;
    init_list(&list);
    add_element(&list, "test");
    bool result = remove_by_key(&list, "test");
    assert(result == true);
    assert(list.head == NULL);
}

// ����� ��������������� ��������
void test_findByKey_NonexistentKey_returnNull_no4() {
    XORList list;
    init_list(&list);
    Node* result = find_by_key(&list, "test");
    assert(result == NULL);
}

// ����� ������������� ��������
void test_findByKey_ExistingKey_returnValidVal_no5() {
    XORList list;
    init_list(&list);
    add_element(&list, "test");
    Node* result = find_by_key(&list, "test");
    assert(result != NULL);
    assert(strcmp(result->data, "test") == 0);
}

// �������� �������� �� ������
void test_removeByAddress_ValidAddress_returnTrue_no6() {
    XORList list;
    init_list(&list);
    add_element(&list, "test");
    Node* node = list.head;
    bool result = remove_by_address(&list, node);
    assert(list.head == NULL);
}

// ������������ �� ������
void test_iterateList_TwoElements_returnValidVal_no7() {
    XORList list;
    init_list(&list);
    add_element(&list, "first");
    add_element(&list, "second");
    Node* prev = NULL;
    Node* current = list.head;
    Node* next = iterate_list(prev, current);
    assert(strcmp(next->data, "second") == 0);
}

// �������� ��������� ���������, ��������� �����
void test_addElement_MultipleElements_returnValidVal_no8() {
    XORList list;
    init_list(&list);
    add_element(&list, "first");
    add_element(&list, "second");
    assert(strcmp(list.tail->data, "second") == 0 && strcmp(list.head->data, "first") == 0);
}

// ������� ��� ��������
void test_removeAllElements_ValidList_returnEmptyList_no9() {
    XORList list;
    init_list(&list);
    add_element(&list, "first");
    add_element(&list, "second");
    remove_by_key(&list, "first");
    remove_by_key(&list, "second");
    assert(list.head == NULL && list.tail == NULL);
}

// ������� ������� �� ����� - ������ ��������� ���������. ������ ��������� ���� ������.
void test_removeByKey_MultipleKeys_returnTrue_no10() {
    XORList list1;
    init_list(&list1);

    add_element(&list1, "test");
    add_element(&list1, "duplicate");
    add_element(&list1, "test"); 
    remove_by_key(&list1, "test"); 
    XORList list2;
    init_list(&list2);

    add_element(&list2, "duplicate");
    add_element(&list2, "test");
    assert(strcmp(list1.head->data, list2.head->data) == 0 && strcmp(list1.tail->data, list2.tail->data) == 0);
}

int main() {
    test_addElement_EmptyList_returnValidVal_no1();
    test_removeByKey_EmptyList_returnFalse_no2();
    test_removeByKey_ExistingElement_returnTrue_no3();
    test_findByKey_NonexistentKey_returnNull_no4();
    test_findByKey_ExistingKey_returnValidVal_no5();
    test_removeByAddress_ValidAddress_returnTrue_no6();
    test_iterateList_TwoElements_returnValidVal_no7();
    test_addElement_MultipleElements_returnValidVal_no8();
    test_removeAllElements_ValidList_returnEmptyList_no9();
    test_removeByKey_MultipleKeys_returnTrue_no10();

    printf("Tests Success!");
    return 0;
}