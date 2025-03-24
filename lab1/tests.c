#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "struct.h"
#include "funcs.h"

void run_tests() {
    Node* root = NULL;

    // Test_no1: Inserting an element
    root = insert(root, 10);
    assert(root->key == 10);  // ������ ������ ���� 10

    // Test_no2: Inserting another element
    root = insert(root, 20);
    assert(root->key == 20);  // ��������� ����������� ������� ���������� ������

    // Test_no3: Finding an existing element
    root = search(root, 10);
    assert(root->key == 10);  // 10 ������ ���� ��������� � ������

    // Test_no4: Find the missing element (it should remain)
    root = search(root, 30);
    assert(root->key == 20);  // 20 ��������� ������, ��� ��� 30 �� ������

    // Test_no5: Delete element (10)
    root = delete(root, 10);
    assert(root->key != 10);  // 10 ������ ���� �����

    // Test_no6: Delete element (20)
    root = delete(root, 20);
    assert(root == NULL);  // ������ ������ ����� ������

    // Test_no7: Inserting multiple elements and deleting the root
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 60);
    root = delete(root, 50);
    assert(root->key != 50);  // 50 ������ ���� �����

    // Test_no8: Checking that search works correctly after deletion
    root = search(root, 70);
    assert(root->key == 70);  // 70 ������ ���� ������ ����� ������

    // Test_no9: Attempt to delete non-existent element
    root = delete(root, 100);
    assert(root != NULL);  // ������ �� ������ ����������

    // Test_no10: Remove all elements and check for empty tree
    root = delete(root, 30);
    root = delete(root, 70);
    root = delete(root, 60);
    assert(root == NULL);  // ������ ������ ���� ������

    printf("��� ����-����� �������� �������!\n");
}