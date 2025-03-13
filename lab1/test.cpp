#include <gtest/gtest.h>
#include "LabH.h" 

TEST(AVLTest, TestAddToEmptyList_HappyPath_no1) {
    Node* list = nullptr;
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 15);
    Node* first = find_kth(list, 1);
    Node* second = find_kth(list, 2);
    EXPECT_NE(first, nullptr);
    EXPECT_EQ(first->key, 10);
    EXPECT_NE(second, nullptr);
    EXPECT_EQ(second->key, 15);
}

TEST(AVLTest, TestInsertMultipleElements_HappyPath_no2) {
    Node* list = nullptr;
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 1, 15);
    list = insert_at(list, 3, 25);
    list = insert_at(list, 2, 17);
    int expected[] = { 10, 15, 17, 20, 25 };
    for (int i = 0; i < 5; i++) {
        Node* node = find_kth(list, i + 1);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, expected[i]);
    }
}

TEST(AVLTest, TestDeleteAtBeginning_HappyPath_no3) {
    Node* list = nullptr;
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 2, 30);
    list = delete_at(list, 0);
    int expected[] = { 20, 30 };
    for (int i = 0; i < 2; i++) {
        Node* node = find_kth(list, i + 1);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, expected[i]);
    }
}

TEST(AVLTest, TestDeleteAtMiddle_HappyPath_no4) {
    Node* list = nullptr;
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 2, 30);
    list = insert_at(list, 3, 40);
    list = delete_at(list, 2);
    int expected[] = { 10, 20, 40 };
    for (int i = 0; i < 3; i++) {
        Node* node = find_kth(list, i + 1);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, expected[i]);
    }
}


TEST(AVLTest, TestDeleteAtEnd_HappyPath_no5) {
    Node* list = nullptr;
    list = insert_at(list, 0, 5);
    list = insert_at(list, 1, 15);
    list = insert_at(list, 2, 25);
    list = delete_at(list, getSize(list) - 1);
    int expected[] = { 5, 15 };
    for (int i = 0; i < 2; i++) {
        Node* node = find_kth(list, i + 1);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, expected[i]);
    }
}

TEST(AVLTest, TestFindKthElement_Boundary_no6) {
    Node* list = nullptr;
    EXPECT_EQ(find_kth(list, 1), nullptr);
    list = insert_at(list, 0, 100);
    EXPECT_EQ(find_kth(list, 0), nullptr);
    EXPECT_EQ(find_kth(list, 2), nullptr);
    Node* node = find_kth(list, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->key, 100);
}

TEST(AVLTest, TestSearchByKey_ExistingAndNonexisting_no7) {
    Node* list = nullptr;
    list = insert_at(list, 0, 3);
    list = insert_at(list, 1, 7);
    list = insert_at(list, 2, 9);
    Node* node = search_by_key(list, 7);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->key, 7);
    node = search_by_key(list, 11);
    EXPECT_EQ(node, nullptr);
}

TEST(AVLTest, TestJoinTrees_HappyPath_no8) {
    Node* list1 = nullptr;
    list1 = insert_at(list1, 0, 1);
    list1 = insert_at(list1, 1, 3);
    list1 = insert_at(list1, 2, 5);
    Node* list2 = nullptr;
    list2 = insert_at(list2, 0, 2);
    list2 = insert_at(list2, 1, 4);
    list2 = insert_at(list2, 2, 6);
    Node* joined = join_trees(list1, list2);
    int expected[] = { 1, 3, 5, 2, 4, 6 };
    for (int i = 0; i < 6; i++) {
        Node* node = find_kth(joined, i + 1);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, expected[i]);
    }
}

TEST(AVLTest, TestComplexOperations_no9) {
    Node* list = nullptr;
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 2, 30);
    list = insert_at(list, 3, 40);
    list = delete_at(list, 1);
    list = insert_at(list, 2, 25);
    list = delete_at(list, 1);
    list = insert_at(list, 0, 5);
    int expected[] = { 5, 10, 25, 40 };
    for (int i = 0; i < 4; i++) {
        Node* node = find_kth(list, i + 1);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, expected[i]);
    }
}

TEST(AVLTest, TestEdgeCase_EmptyOperations_no10) {
    Node* list = nullptr;
    list = delete_at(list, 0);
    EXPECT_EQ(list, nullptr);
    EXPECT_EQ(find_kth(list, 1), nullptr);
    EXPECT_EQ(search_by_key(list, 100), nullptr);
    Node* list2 = nullptr;
    list2 = insert_at(list2, 0, 42);
    Node* joined = join_trees(list, list2);
    Node* node = find_kth(joined, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->key, 42);
    joined = join_trees(list2, nullptr);
    node = find_kth(joined, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->key, 42);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}