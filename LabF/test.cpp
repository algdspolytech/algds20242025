#include "gtest/gtest.h"

extern "C" {
#include "labF.h"
}

TEST(IntervalTree_Test1, AddInterval_ValidArguments_Inserted) {
    // Arrange
    Node* rootNode = NULL;

    // Act
    addInterval(&rootNode, 1, 5);

    // Assert
    ASSERT_NE(rootNode, nullptr);
    ASSERT_EQ(rootNode->lowerBound, 1);
    ASSERT_EQ(rootNode->upperBound, 5);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test2, AddInterval_MultipleNodes_Inserted) {
    // Arrange
    Node* rootNode = NULL;

    // Act
    addInterval(&rootNode, 5, 10);
    addInterval(&rootNode, 1, 3);
    addInterval(&rootNode, 7, 12);

    // Assert
    ASSERT_NE(rootNode, nullptr);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test3, FindInterval_ExistingNode_Correct) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 5, 10);

    // Act
    Node* node = findInterval(rootNode, 5, 10);

    // Assert
    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->lowerBound, 5);
    ASSERT_EQ(node->upperBound, 10);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test4, FindInterval_NonExistingNode_Nullptr) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 5, 10);

    // Act
    Node* node = findInterval(rootNode, 1, 2);

    // Assert
    ASSERT_EQ(node, nullptr);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test5, RemoveInterval_LeafNode_Deleted) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 5, 10);
    addInterval(&rootNode, 1, 3);

    // Act
    removeInterval(&rootNode, 1, 3);
    Node* node = findInterval(rootNode, 1, 3);

    // Assert
    ASSERT_EQ(node, nullptr);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test6, RemoveInterval_NodeWithOneChild_Deleted) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 5, 10);
    addInterval(&rootNode, 1, 3);
    addInterval(&rootNode, 7, 12);

    // Act
    removeInterval(&rootNode, 5, 10);
    Node* node = findInterval(rootNode, 5, 10);

    // Assert
    ASSERT_EQ(node, nullptr);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test7, RemoveInterval_NodeWithTwoChildren_Deleted) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 5, 10);
    addInterval(&rootNode, 1, 3);
    addInterval(&rootNode, 7, 12);
    addInterval(&rootNode, 3, 6);

    // Act
    removeInterval(&rootNode, 5, 10);
    Node* node = findInterval(rootNode, 5, 10);

    // Assert
    ASSERT_EQ(node, nullptr);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test8, GetOverlappingIntervals_Valid_Correct) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 1, 5);
    addInterval(&rootNode, 3, 7);
    addInterval(&rootNode, 8, 12);
    Node* output[100];
    int count = 0;

    // Act
    getOverlappingIntervals(rootNode, 2, 6, output, &count);

    // Assert
    ASSERT_GE(count, 1);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test9, GetOverlappingIntervals_NoOverlap_Zero) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 1, 5);
    addInterval(&rootNode, 8, 12);
    Node* output[100];
    int count = 0;

    // Act
    getOverlappingIntervals(rootNode, 6, 7, output, &count);

    // Assert
    ASSERT_EQ(count, 0);
    releaseTree(rootNode);
}

TEST(IntervalTree_Test10, RemoveAndFind_ValidArguments_Valid) {
    // Arrange
    Node* rootNode = NULL;
    addInterval(&rootNode, 5, 10);
    addInterval(&rootNode, 1, 3);
    addInterval(&rootNode, 7, 12);

    // Act
    removeInterval(&rootNode, 1, 3);

    // Act & Assert
    ASSERT_EQ(findInterval(rootNode, 1, 3), nullptr);
    ASSERT_NE(findInterval(rootNode, 5, 10), nullptr);
    ASSERT_NE(findInterval(rootNode, 7, 12), nullptr);

    releaseTree(rootNode);
}
