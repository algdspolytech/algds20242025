#include "xor_list.h"
#include <gtest/gtest.h>

// Фикстура для тестирования XOR-связного списка
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

// Тест 1: Добавление элементов в список
TEST_F(XORLinkedListTest, AddElements) {
    add(&head, "Hello");
    add(&head, "World");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Список: Hello -> World -> NULL\n");
}

// Тест 2: Поиск существующего элемента
TEST_F(XORLinkedListTest, FindElement) {
    add(&head, "A");
    add(&head, "B");
    add(&head, "C");

    Node* result = find(head, "B");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result->data, "B");
}

// Тест 3: Поиск несуществующего элемента
TEST_F(XORLinkedListTest, FindNonExistingElement) {
    add(&head, "X");
    add(&head, "Y");

    Node* result = find(head, "Z");
    ASSERT_EQ(result, nullptr);
}

// Тест 4: Удаление элемента по ключу
TEST_F(XORLinkedListTest, DeleteByKey) {
    add(&head, "1");
    add(&head, "2");
    add(&head, "3");

    deleteByKey(&head, "2");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Список: 1 -> 3 -> NULL\n");
}

// Тест 5: Удаление элемента по адресу
TEST_F(XORLinkedListTest, DeleteByAddress) {
    add(&head, "First");
    add(&head, "Second");

    Node* toDelete = find(head, "First");
    deleteByAddress(&head, toDelete);

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Список: Second -> NULL\n");
}

// Тест 6: Добавление и удаление всех элементов
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

    ASSERT_EQ(output, "Список: NULL\n");
}

// Тест 7: Обработка пустого списка
TEST_F(XORLinkedListTest, EmptyListOperations) {
    Node* result = find(head, "NonExistent");
    ASSERT_EQ(result, nullptr);

    deleteByKey(&head, "NonExistent");
    ASSERT_EQ(head, nullptr);
}

// Тест 8: Итерация и корректный вывод
TEST_F(XORLinkedListTest, IterationTest) {
    add(&head, "One");
    add(&head, "Two");
    add(&head, "Three");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Список: One -> Two -> Three -> NULL\n");
}

// Тест 9: Удаление из середины
TEST_F(XORLinkedListTest, DeleteMiddleElement) {
    add(&head, "Alpha");
    add(&head, "Beta");
    add(&head, "Gamma");

    deleteByKey(&head, "Beta");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Список: Alpha -> Gamma -> NULL\n");
}

// Тест 10: Повторное добавление после удаления
TEST_F(XORLinkedListTest, ReAddAfterDeletion) {
    add(&head, "A");
    add(&head, "B");
    deleteByKey(&head, "A");

    add(&head, "C");
    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Список: B -> C -> NULL\n");
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); // Запуск всех тестов
}