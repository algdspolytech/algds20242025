#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

// ����: ������� ������ ��������
void TestInsert_SingleElement_ReturnValidVal() {
    struct Node* root = NULL;
    root = insert(root, 1, 10);
    printf("TestInsert_SingleElement_ReturnValidVal = %d\n", root->c == 10);  // ���������, ��� �������� � ����� ����� 10
}

// ����: ������� ���������� ��������� � �������� ���������
void TestInsert_MultipleElements_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 2, 20);
    root = insert(root, 3, 15);
    printf("TestInsert_MultipleElements_ReturnValidMax = %d\n", find_max(root, 1, 4) == 20);
}

// ����: ����� ��������� � ��������� � ����� ���������
void TestGetMax_SingleElementRange_ReturnValidVal() {
    struct Node* root = NULL;
    root = insert(root, 2, 30);
    printf("TestGetMax_SingleElementRange_ReturnValidVal = %d\n", find_max(root, 2, 3) == 30);
}

// ����: ����� ��������� � ������ ���������
void TestGetMax_EmptyRange_ReturnZero() {
    struct Node* root = NULL;
    printf("TestGetMax_EmptyRange_ReturnZero = %d\n", find_max(root, 1, 2) == -1);  // ������ ������, ������ ���������� -1 (��� ����������� ��������)
}

// ����: ������� ����������
void TestInsert_DuplicateKeys_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 1, 20);  // ������� � ��� �� ������, �� ������ ���������
    printf("TestInsert_DuplicateKeys_ReturnValidMax = %d\n", find_max(root, 1, 2) == 20);  // �������� � ��������� [1, 2) ������ ���� 20
}

// ����: ������� ��������� � ��������� �������
void TestInsert_DescendingOrder_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 3, 10);
    root = insert(root, 2, 20);
    root = insert(root, 1, 30);
    printf("TestInsert_DescendingOrder_ReturnValidMax = %d\n", find_max(root, 1, 4) == 30);
}

// ����: ������� ��������� � ������������ �������
void TestInsert_AscendingOrder_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 5);
    root = insert(root, 2, 15);
    root = insert(root, 3, 25);
    printf("TestInsert_AscendingOrder_ReturnValidMax = %d\n", find_max(root, 1, 4) == 25);
}

// ����: ������� ������������� �������� � �������� ���������
// ����: ������� ������������� � ������������� �������� � �������� ��������� � ���������
void TestInsert_PositiveAndNegativeValues_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 5, 50);    // ������������� ��������
    root = insert(root, -10, 100); // ������������� ��������
    root = insert(root, 15, 70);   // ������������� ��������
    root = insert(root, -5, 120);  // ������������� ��������

    // ��������� ������������ �������� � ��������� [-10, 10)
    printf("TestInsert_PositiveAndNegativeValues_ReturnValidMax = %d\n", find_max(root, -10, 10) == 120); // ������� �������� 120
}



// ����: �������� ��������� �� ������������ ���������
void TestGetMax_SubsetRange_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 5);
    root = insert(root, 2, 15);
    root = insert(root, 3, 10);
    printf("TestGetMax_SubsetRange_ReturnValidMax = %d\n", find_max(root, 2, 3) == 15);
}

// ����: �������� ���������, ����� �������� ��� ��������� ������
void TestGetMax_OutOfBounds_ReturnZero() {
    struct Node* root = NULL;
    root = insert(root, 2, 10);
    root = insert(root, 4, 20);
    printf("TestGetMax_OutOfBounds_ReturnZero = %d\n", find_max(root, 5, 6) == -1);  // �������� ��� ��������� ������, ������ ���� -1
}

// ������ ���� ������
void RunAllTests() {
    TestInsert_SingleElement_ReturnValidVal();
    TestInsert_MultipleElements_ReturnValidMax();
    TestGetMax_SingleElementRange_ReturnValidVal();
    TestGetMax_EmptyRange_ReturnZero();
    TestInsert_DuplicateKeys_ReturnValidMax();
    TestInsert_DescendingOrder_ReturnValidMax();
    TestInsert_AscendingOrder_ReturnValidMax();
    TestInsert_PositiveAndNegativeValues_ReturnValidMax();
    TestGetMax_SubsetRange_ReturnValidMax();
    TestGetMax_OutOfBounds_ReturnZero();
}

int main() {
    RunAllTests();
    return 0;
}
