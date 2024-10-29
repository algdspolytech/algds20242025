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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
