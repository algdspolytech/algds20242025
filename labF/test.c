#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "interval_tree.h" // ���������� ���� � ����������� ������ ����������

void test_insert_find() {
    Node* root = NULL;
    root = insert(root, 5, 10);
    root = insert(root, 15, 20);
    root = insert(root, 25, 30);

    // �������� �� ����������� � ���������� [12, 18]
    int intervalToFind[] = { 12, 18 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 15 && result[0]->high == 20);
}

void test_delete() {
    Node* root = NULL;
    root = insert(root, 5, 10);
    root = insert(root, 15, 20);
    root = insert(root, 25, 30);

    root = deleteNode(root, 15); // ������� �������� [15, 20]

    // �������� �� ����������� � ���������� [12, 18]
    int intervalToFind[] = { 12, 18 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 0); // ������ ���� 0 �����������
}

void test_empty_tree() {
    Node* root = NULL;

    int intervalToFind[] = { 14, 24 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 0); // ������ ������, ����������� ���
}

void test_single_element() {
    Node* root = NULL;
    root = insert(root, 10, 20); // ������� ��������� [10, 20]

    int intervalToFind[] = { 15, 18 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 10 && result[0]->high == 20); // ������ ����� [10, 20]
}

int main() {
    // ������ ������
    test_insert_find();
    test_delete();
    test_empty_tree();
    test_single_element();

    printf("��� ����� �������� �������.\n");
    return 0;
}