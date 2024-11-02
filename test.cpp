#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" { 
#include "lab_a.h" 
}




TEST(LinkedListTest, InsertIntoEmptyList_no1) {
    Node* head = NULL;
    ASSERT_EQ(insertSorted(&head, "Word1", 10), 1);
    ASSERT_NE(head, NULL);
}

TEST(LinkedListTest, InsertIntoNonEmptyList_HappyPath_no2) {
    Node* head = createNode("Word1", 10);
    ASSERT_EQ(insertSorted(&head, "Word2", 20), 1);
    ASSERT_STREQ(head->next->word, "Word2");
}

TEST(LinkedListTest, InsertDuplicateKey_no3) {
    Node* head = createNode("Word1", 10);
    ASSERT_EQ(insertSorted(&head, "Word2", 10), 0); 
}

TEST(LinkedListTest, InsertMultipleKeys_no4) {
    Node* head = NULL;
    insertSorted(&head, "Word1", 10);
    insertSorted(&head, "Word3", 30);

    ASSERT_EQ(insertSorted(&head, "Word2", 20), 1); 
    ASSERT_STREQ(head->next->word, "Word2");
}

TEST(LinkedListTest, SearchExistingKey_no5) {
    Node* head = NULL;
    insertSorted(&head, "Word1", 10);

    const char* result = searchByKey(head, 10);
    ASSERT_STREQ(result, "Word1");
}

TEST(LinkedListTest, SearchNonExistingKey_no6) {
    Node* head = NULL;
    insertSorted(&head, "Word1", 10);

    const char* result = searchByKey(head, 20);
    ASSERT_EQ(result, NULL);
}

TEST(LinkedListTest, SearchMultipleKeys_no7) {
    Node* head = NULL;
    insertSorted(&head, "Word1", 10);
    insertSorted(&head, "Word2", 20);

    const char* result = searchByKey(head, 20);
    ASSERT_STREQ(result, "Word2");
}

TEST(LinkedListTest, InsertMultipleDuplicates_no8) {
    Node* head = NULL;

    insertSorted(&head, "Word1", 10);

    ASSERT_EQ(insertSorted(&head, "Word2", 10), 0); 
}

TEST(LinkedListTest, PrintEmptyList_no9) {
    Node* head = NULL;

    EXPECT_NO_THROW(printList(head));
}

TEST(LinkedListTest, PrintSingleElement_no10) {
    Node* head = createNode("Word1", 10);

}

TEST(LinkedListTest, PrintMultipleElements_no11) {
    Node* head = NULL;

    insertSorted(&head, "Word1", 10);
    insertSorted(&head, "Word2", 20);

}

TEST(LinkedListTest, InsertAtHead_no12) {
    Node* head = NULL;

    insertSorted(&head, "Word2", 20);

    ASSERT_EQ(insertSorted(&head, "Word1", 10), 1); 

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
