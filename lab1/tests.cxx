#include "gtest/gtest.h"

extern "C" {
#include "labF.h"
}

TEST(LabF_Test1, Insert_ValidArguments_Inserted) {
    //Arrange
    IntervalNode* root = NULL;

    //Act
    insert(&root, 1, 5);

    //Assert
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->start, 1);
    ASSERT_EQ(root->end, 5);
    freeTree(root);
}

TEST(LabF_Test2, Insert_MultipleNodes_Inserted) {
    //Arrange
    IntervalNode* root = NULL;

    //Act
    insert(&root, 5, 10);
    insert(&root, 1, 3);
    insert(&root, 7, 12);

    //Assert
    ASSERT_NE(root, nullptr);
    freeTree(root);
}

TEST(LabF_Test3, Search_ExistingNode_Correct) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 5, 10);

    //Act
    IntervalNode* node = search(root, 5, 10);

    //Assert
    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->start, 5);
    ASSERT_EQ(node->end, 10);
    freeTree(root);
}

TEST(LabF_Test4, Search_NonExistingNode_Nullptr) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 5, 10);

    //Act
    IntervalNode* node = search(root, 1, 2);

    //Assert
    ASSERT_EQ(node, nullptr);
    freeTree(root);
}

TEST(LabF_Test5, Delete_LeafNode_Deleted) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 5, 10);
    insert(&root, 1, 3);

    //Act
    deleteNode(&root, 1, 3);
    IntervalNode* node = search(root, 1, 3);

    //Assert
    ASSERT_EQ(node, nullptr);
    freeTree(root);
}

TEST(LabF_Test6, Delete_NodeWithOneChild_Deleted) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 5, 10);
    insert(&root, 1, 3);
    insert(&root, 7, 12);

    //Act
    deleteNode(&root, 5, 10);
    IntervalNode* node = search(root, 5, 10);

    //Assert
    ASSERT_EQ(node, nullptr);
    freeTree(root);
}

TEST(LabF_Test7, Delete_NodeWithTwoChildren_Deleted) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 5, 10);
    insert(&root, 1, 3);
    insert(&root, 7, 12);
    insert(&root, 3, 6);

    //Act
    deleteNode(&root, 5, 10);
    IntervalNode* node = search(root, 5, 10);

    //Assert
    ASSERT_EQ(node, nullptr);
    freeTree(root);
}

TEST(LabF_Test8, FindOverlappingIntervals_Valid_Correct) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 1, 5);
    insert(&root, 3, 7);
    insert(&root, 8, 12);
    IntervalNode* result[100];
    int count = 0;

    //Act
    findOverlappingIntervals(root, 2, 6, result, &count);

    //Assert
    ASSERT_GE(count,1);
    freeTree(root);
}

TEST(LabF_Test9, FindOverlappingIntervals_NoOverlap_Zero) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 1, 5);
    insert(&root, 8, 12);
    IntervalNode* result[100];
    int count = 0;

    //Act
    findOverlappingIntervals(root, 6, 7, result, &count);

    //Assert
    ASSERT_EQ(count, 0);
    freeTree(root);
}

TEST(LabF_Test10, DeleteAndSearch_ValidArguments_Valid) {
    //Arrange
    IntervalNode* root = NULL;
    insert(&root, 5, 10);
    insert(&root, 1, 3);
    insert(&root, 7, 12);

    //Act
    deleteNode(&root, 1, 3);

    //Act & Assert
    ASSERT_EQ(search(root, 1, 3), nullptr);
    ASSERT_NE(search(root, 5, 10), nullptr);
    ASSERT_NE(search(root, 7, 12), nullptr);

    freeTree(root);
}
