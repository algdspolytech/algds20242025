#include <gtest/gtest.h>
#include "Unrolled_linked_list.h"

// ���� �� �������� ������� ������
TEST(UnrolledLinkedListTest, CreateList) {
    UnrolledLinkedList* list = createList();
    ASSERT_NE(list, nullptr);
    ASSERT_EQ(getSize(list), 0);
    freeList(list);
}

// ���� �� ���������� ���������
TEST(UnrolledLinkedListTest, AddElements) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    ASSERT_EQ(getSize(list), 2);
    ASSERT_EQ(findByIndex(list, 0), 10);
    ASSERT_EQ(findByIndex(list, 1), 20);
    freeList(list);
}

// ���� �� ����� �������� �� �����
TEST(UnrolledLinkedListTest, FindIndexByKey) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    ASSERT_EQ(findIndexByKey(list, 20), 1);
    ASSERT_EQ(findIndexByKey(list, 40), -1); // �������� 40 ��� � ������
    freeList(list);
}

// ���� �� ����� �������� �� �������
TEST(UnrolledLinkedListTest, FindByIndex) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    ASSERT_EQ(findByIndex(list, 0), 10);
    ASSERT_EQ(findByIndex(list, 2), 30);
    ASSERT_EQ(findByIndex(list, 3), -1); // ������ �� ��������� ������
    freeList(list);
}

// ���� �� �������� �������� �� �������
TEST(UnrolledLinkedListTest, DeleteByIndex) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    deleteByIndex(list, 1);
    ASSERT_EQ(getSize(list), 2);
    ASSERT_EQ(findByIndex(list, 1), 30);
    freeList(list);
}

// ���� �� ��������� ������� ������
TEST(UnrolledLinkedListTest, GetSize) {
    UnrolledLinkedList* list = createList();
    ASSERT_EQ(getSize(list), 0);
    add(list, 10);
    add(list, 20);
    ASSERT_EQ(getSize(list), 2);
    freeList(list);
}

// ���� �� ��������� ���������� ��������
TEST(UnrolledLinkedListTest, GetNext) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    ASSERT_EQ(getNext(list, 20), 30);
    ASSERT_EQ(getNext(list, 30), -1); // 30 � ��������� �������
    freeList(list);
}

// ���� �� ���������� ��������� �� ���������� �����
TEST(UnrolledLinkedListTest, AddElementsTillBlockFull) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40); // ��������� ������ ����
    add(list, 50); // ��������� ����� ����
    ASSERT_EQ(getSize(list), 5);
    ASSERT_EQ(findByIndex(list, 4), 50);
    freeList(list);
}

// ���� �� ���������� ������������ ������
TEST(UnrolledLinkedListTest, FreeList) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    freeList(list);
    // ������������� ����� �������� �������� � �������������� ������������ ������� ������
}

// ���� �� ���������� � �������� ���������� ���������
TEST(UnrolledLinkedListTest, AddAndDeleteMultipleElements) {
    UnrolledLinkedList* list = createList();
    for (int i = 0; i < 10; ++i) {
        add(list, i * 10);
    }
    ASSERT_EQ(getSize(list), 10);
    deleteByIndex(list, 5); // ������� ������� � �������� 5
    ASSERT_EQ(getSize(list), 9);
    ASSERT_EQ(findByIndex(list, 5), 60);
    freeList(list);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}