#include "xor_list.h"
#include <gtest/gtest.h>

// �������� ��� ������������ XOR-�������� ������
class XORLinkedListTest : public ::testing::Test {
protected:
    Node* head;

    void SetUp() override {
        head = nullptr;
    }

    void TearDown() override {
        freeList(head);
        head = nullptr;
    }
};

// ���� 1: ���������� ��������� � ������
TEST_F(XORLinkedListTest, AddElements) {
    add(&head, "Hello");
    add(&head, "World");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: Hello -> World -> NULL\n");
}

// ���� 2: ����� ������������� ��������
TEST_F(XORLinkedListTest, FindElement) {
    add(&head, "A");
    add(&head, "B");
    add(&head, "C");

    Node* result = find(head, "B");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result->data, "B");
}

// ���� 3: ����� ��������������� ��������
TEST_F(XORLinkedListTest, FindNonExistingElement) {
    add(&head, "X");
    add(&head, "Y");

    Node* result = find(head, "Z");
    ASSERT_EQ(result, nullptr);
}

// ���� 4: �������� �������� �� �����
TEST_F(XORLinkedListTest, DeleteByKey) {
    add(&head, "1");
    add(&head, "2");
    add(&head, "3");

    deleteByKey(&head, "2");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: 1 -> 3 -> NULL\n");
}

// ���� 5: �������� �������� �� ������
TEST_F(XORLinkedListTest, DeleteByAddress) {
    add(&head, "First");
    add(&head, "Second");

    Node* toDelete = find(head, "First");
    deleteByAddress(&head, toDelete);

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: Second -> NULL\n");
}

// ���� 6: ���������� � �������� ���� ���������
TEST_F(XORLinkedListTest, AddAndDeleteAll) {
    add(&head, "A");
    add(&head, "B");
    add(&head, "C");

    deleteByKey(&head, "A");
    deleteByKey(&head, "B");
    deleteByKey(&head, "C");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: NULL\n");
}

// ���� 7: ��������� ������� ������
TEST_F(XORLinkedListTest, EmptyListOperations) {
    Node* result = find(head, "NonExistent");
    ASSERT_EQ(result, nullptr);

    deleteByKey(&head, "NonExistent");
    ASSERT_EQ(head, nullptr);
}

// ���� 8: �������� � ���������� �����
TEST_F(XORLinkedListTest, IterationTest) {
    add(&head, "One");
    add(&head, "Two");
    add(&head, "Three");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: One -> Two -> Three -> NULL\n");
}

// ���� 9: �������� �� ��������
TEST_F(XORLinkedListTest, DeleteMiddleElement) {
    add(&head, "Alpha");
    add(&head, "Beta");
    add(&head, "Gamma");

    deleteByKey(&head, "Beta");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: Alpha -> Gamma -> NULL\n");
}

// ���� 10: ��������� ���������� ����� ��������
TEST_F(XORLinkedListTest, ReAddAfterDeletion) {
    add(&head, "A");
    add(&head, "B");
    deleteByKey(&head, "A");

    add(&head, "C");
    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "������: B -> C -> NULL\n");
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); // ������ ���� ������
}