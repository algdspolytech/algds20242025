#include "expanded_linked_list.h"
#include <gtest/gtest.h>

TEST(ExpandedLinkedListTest, AddElement_no1) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 10);
    EXPECT_EQ(get_total_count(&list), 1);
    EXPECT_EQ(find_element_by_index(&list, 0), 10);
}

TEST(ExpandedLinkedListTest, FindElementByKey_no2) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 20);
    EXPECT_EQ(find_element_by_key(&list, 20), 0);
    EXPECT_EQ(find_element_by_key(&list, 30), -1);
}

TEST(ExpandedLinkedListTest, FindElementByIndex_no3) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 10);
    add_element(&list, 20);
    EXPECT_EQ(find_element_by_index(&list, 1), 20);
    EXPECT_EQ(find_element_by_index(&list, 2), -1);
}

TEST(ExpandedLinkedListTest, RemoveElementByIndex_no4) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 10);
    add_element(&list, 20);
    EXPECT_TRUE(remove_element_by_index(&list, 1));
    EXPECT_EQ(get_total_count(&list), 1);
}

TEST(ExpandedLinkedListTest, GetNextElement_no5) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 10);
    add_element(&list, 20);
    add_element(&list, 30);
    EXPECT_EQ(get_next_element(&list, 20), 30);
    EXPECT_EQ(get_next_element(&list, 30), -1);
}

/ Тест добавления элементов для заполнения нескольких узлов
TEST(ExpandedLinkedListTest, MultipleNodeAddition_no6) {
    ExpandedLinkedList list;
    init_list(&list);
    for (int i = 0; i < 10; i++) {
        add_element(&list, i);
    }
    EXPECT_EQ(get_total_count(&list), 10);
    EXPECT_EQ(find_element_by_index(&list, 9), 9);
}

TEST(ExpandedLinkedListTest, FindElementAcrossNodes_no7) {
    ExpandedLinkedList list;
    init_list(&list);
    for (int i = 0; i < 8; i++) {
        add_element(&list, i);
    }
    EXPECT_EQ(find_element_by_index(&list, 4), 4);
    EXPECT_EQ(find_element_by_index(&list, 7), 7);
}

TEST(ExpandedLinkedListTest, RemoveAllElements_no8) {
    ExpandedLinkedList list;
    init_list(&list);
    for (int i = 0; i < 5; i++) {
        add_element(&list, i);
    }
    for (int i = 4; i >= 0; i--) {
        EXPECT_TRUE(remove_element_by_index(&list, i));
    }
    EXPECT_EQ(get_total_count(&list), 0);
    EXPECT_EQ(find_element_by_index(&list, 0), -1);
}

TEST(ExpandedLinkedListTest, FindNonExistentElement_no9) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 10);
    add_element(&list, 20);
    EXPECT_EQ(find_element_by_key(&list, 30), -1);
}

TEST(ExpandedLinkedListTest, IterateThroughList_no10) {
    ExpandedLinkedList list;
    init_list(&list);
    add_element(&list, 1);
    add_element(&list, 2);
    add_element(&list, 3);
    EXPECT_EQ(get_next_element(&list, 1), 2);
    EXPECT_EQ(get_next_element(&list, 2), 3);
    EXPECT_EQ(get_next_element(&list, 3), -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
