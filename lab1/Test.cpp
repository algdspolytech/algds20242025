#include <gtest/gtest.h>
#include "Unrolled_linked_list.h"

// Тест на создание пустого списка
TEST(UnrolledLinkedListTest, CreateList) {
    UnrolledLinkedList* list = createList();
    ASSERT_NE(list, nullptr);
    ASSERT_EQ(getSize(list), 0);
    freeList(list);
}

// Тест на добавление элементов
TEST(UnrolledLinkedListTest, AddElements) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    ASSERT_EQ(getSize(list), 2);
    ASSERT_EQ(findByIndex(list, 0), 10);
    ASSERT_EQ(findByIndex(list, 1), 20);
    freeList(list);
}

// Тест на поиск элемента по ключу
TEST(UnrolledLinkedListTest, FindIndexByKey) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    ASSERT_EQ(findIndexByKey(list, 20), 1);
    ASSERT_EQ(findIndexByKey(list, 40), -1); // Элемента 40 нет в списке
    freeList(list);
}

// Тест на поиск элемента по индексу
TEST(UnrolledLinkedListTest, FindByIndex) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    ASSERT_EQ(findByIndex(list, 0), 10);
    ASSERT_EQ(findByIndex(list, 2), 30);
    ASSERT_EQ(findByIndex(list, 3), -1); // Индекс за пределами списка
    freeList(list);
}

// Тест на удаление элемента по индексу
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

// Тест на получение размера списка
TEST(UnrolledLinkedListTest, GetSize) {
    UnrolledLinkedList* list = createList();
    ASSERT_EQ(getSize(list), 0);
    add(list, 10);
    add(list, 20);
    ASSERT_EQ(getSize(list), 2);
    freeList(list);
}

// Тест на получение следующего элемента
TEST(UnrolledLinkedListTest, GetNext) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    ASSERT_EQ(getNext(list, 20), 30);
    ASSERT_EQ(getNext(list, 30), -1); // 30 — последний элемент
    freeList(list);
}

// Тест на добавление элементов до заполнения блока
TEST(UnrolledLinkedListTest, AddElementsTillBlockFull) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40); // Заполняем первый блок
    add(list, 50); // Создается новый узел
    ASSERT_EQ(getSize(list), 5);
    ASSERT_EQ(findByIndex(list, 4), 50);
    freeList(list);
}

// Тест на корректное освобождение памяти
TEST(UnrolledLinkedListTest, FreeList) {
    UnrolledLinkedList* list = createList();
    add(list, 10);
    add(list, 20);
    freeList(list);
    // Дополнительно можно добавить проверку с использованием инструментов отладки памяти
}

// Тест на добавление и удаление нескольких элементов
TEST(UnrolledLinkedListTest, AddAndDeleteMultipleElements) {
    UnrolledLinkedList* list = createList();
    for (int i = 0; i < 10; ++i) {
        add(list, i * 10);
    }
    ASSERT_EQ(getSize(list), 10);
    deleteByIndex(list, 5); // Удаляем элемент с индексом 5
    ASSERT_EQ(getSize(list), 9);
    ASSERT_EQ(findByIndex(list, 5), 60);
    freeList(list);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}