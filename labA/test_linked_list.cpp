#include <gtest/gtest.h>
extern "C" {
#include "linked_list.h"
}

// Тест 1: Добавление в пустой список
TEST(LinkedListTest, AddToEmptyList_no1) {
    LinkedList *list = create_list();
    add_to_list(list, "Hello");
    ASSERT_STREQ(list->head->data, "Hello");
    free_list(list);
}

// Тест 2: Добавление нескольких элементов
TEST(LinkedListTest, AddMultipleElements_no2) {
    LinkedList *list = create_list();
    add_to_list(list, "World");
    add_to_list(list, "Hello");
    ASSERT_STREQ(list->head->data, "Hello");
    ASSERT_STREQ(list->head->next->data, "World");
    free_list(list);
}

// Тест 3: Сортировка пустого списка
TEST(LinkedListTest, SortEmptyList_no3) {
    LinkedList *list = create_list();
    sort_list(list);
    ASSERT_EQ(list->head, nullptr);
    free_list(list);
}

// Тест 4: Сортировка списка с одним элементом
TEST(LinkedListTest, SortSingleElement_no4) {
    LinkedList *list = create_list();
    add_to_list(list, "A");
    sort_list(list);
    ASSERT_STREQ(list->head->data, "A");
    free_list(list);
}

// Тест 5: Сортировка уже отсортированного списка
TEST(LinkedListTest, SortAlreadySortedList_no5) {
    LinkedList *list = create_list();
    add_to_list(list, "A");
    add_to_list(list, "B");
    add_to_list(list, "C");
    sort_list(list);

    ASSERT_STREQ(list->head->data, "A");
    ASSERT_STREQ(list->head->next->data, "B");
    ASSERT_STREQ(list->head->next->next->data, "C");
    
    free_list(list);
}

// Тест 6: Сортировка неотсортированного списка
TEST(LinkedListTest, SortUnsortedList_no6) {
    LinkedList *list = create_list();
    add_to_list(list, "C");
    add_to_list(list, "A");
    add_to_list(list, "B");
    
    sort_list(list);
    
    ASSERT_STREQ(list->head->data, "A");
    ASSERT_STREQ(list->head->next->data, "B");
    ASSERT_STREQ(list->head->next->next->data, "C");
    
    free_list(list);
}

// Тест 7: Сортировка списка с повторяющимися элементами
TEST(LinkedListTest, SortWithDuplicates_no7) {
    LinkedList *list = create_list();
    add_to_list(list, "B");
    add_to_list(list, "A");
    add_to_list(list, "B");
    
    sort_list(list);
    
    ASSERT_STREQ(list->head->data, "A");
    ASSERT_STREQ(list->head->next->data, "B");
    ASSERT_STREQ(list->head->next->next->data, "B");

    free_list(list);
}

// Тест 8: Сортировка длинного списка
TEST(LinkedListTest, SortLongList_no8) {
    LinkedList *list = create_list();
    
    for (char c = 'Z'; c >= 'A'; --c) {
        char str[2] = {c, '0'};
        add_to_list(list, str);
    }
    
    sort_list(list);

    Node *current = list->head;
    
    for (char c = 'A'; c <= 'Z'; ++c) {
        char str[2] = {c, '0'};
        ASSERT_STREQ(current->data, str);
        current = current->next;
    }

    free_list(list);
}

// Тест 9: Освобождение памяти
TEST(LinkedListTest, FreeMemory_no9) {
    LinkedList *list = create_list();
    
    add_to_list(list, "Test");
    
    ASSERT_NO_THROW(free_list(list));
}

// Тест 10: Печать списка
TEST(LinkedListTest, PrintList_no10) {
    LinkedList *list = create_list();
    
    add_to_list(list, "Hello");
    
    ASSERT_NO_THROW(print_list(list));
    
    free_list(list);
}