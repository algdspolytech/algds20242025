#include "gtest/gtest.h"
extern "C"{
 #include "labH.h"
}

TEST(LabH_Test1, InsertAndSearch_ValidArguments_Correct) {
 //Arrange
 SplayNode *root = NULL;
 root = insert(root, 10);
 root = insert(root, 20);
 root = insert(root, 30);

 //Act
 root = search(root, 20);

 //Assert
 ASSERT_NE(root, nullptr);
 ASSERT_EQ(root->key, 20);

 //Act
 root = search(root, 40);

 //Assert
 ASSERT_NE(root, nullptr);
 ASSERT_NE(root->key, 40);

 freeTree(root);
}

TEST(LabH_Test2, MultipleInser_ValidArguments_Correct) {
  //Arrange
  SplayNode *root = NULL;

  //Act
  root = insert(root, 30);
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 5);
  root = insert(root, 7);

  //Assert
  inorder(root);

  freeTree(root);
}


TEST(LabH_Test3, DeleteRoot_ValidArguments_Deleted) {
 //Arrange
 SplayNode *root = NULL;

 //Act
 root = insert(root, 10);
 root = deleteNode(root, 10);

 //Assert
 ASSERT_EQ(root, nullptr);
}

TEST(LabH_Test4, Delete_NonExistent_NotDeleted) {
 //Arrange
 SplayNode *root = NULL;
 root = insert(root, 10);

 //Act
 root = deleteNode(root, 20);

 //Assert
 ASSERT_NE(root, nullptr);
 ASSERT_EQ(root->key, 10);

 freeTree(root);
}

TEST(LabH_Test5, DeleteAndSearch_ValidArguments_Nullptr) {
 //Arrange
 SplayNode *root = NULL;
 root = insert(root, 10);
 root = insert(root, 20);
 root = insert(root, 30);

 //Act
 root = deleteNode(root, 20);
 root = search(root, 20);

 //Assert
 ASSERT_NE(root, nullptr);
 ASSERT_NE(root->key, 20);
 freeTree(root);
}

TEST(LabH_Test6, MultipleInsertAndDelete_ValidArguments_Nullptr) {
 //Arrange
 SplayNode *root = NULL;

 //Act
 root = insert(root, 10);
 root = insert(root, 20);
 root = insert(root, 30);
 root = deleteNode(root, 10);
 root = insert(root, 5);
 root = deleteNode(root, 30);
 root = insert(root, 25);

 //Assert
 root = search(root, 5);
 ASSERT_NE(root, nullptr);
 ASSERT_EQ(root->key, 5);
 freeTree(root);
}

TEST(LabH_Test7, DeleteAndSearch_EmptyTree_BothNullptr) {
 //Arrange
 SplayNode *root = NULL;

 //Act
 root = search(root, 10);

 //Assert
 ASSERT_EQ(root, nullptr);

 //Act
 root = deleteNode(root, 10);

 //Assert
 ASSERT_EQ(root, nullptr);
}

TEST(LabH_Test8, Insert_SameKey_InsertedOnce) {

 //Arrange
 SplayNode *root = NULL;

 //Act
 root = insert(root, 10);
 root = insert(root, 10);

 //Assert
 ASSERT_NE(root, nullptr);
 ASSERT_EQ(root->key, 10);

 int count = 0;
 SplayNode *current = root;
 while(current != NULL) {
  count++;
   if (current->left != NULL) {
   current = current->left;
  } else {
   current = current->right;
  }
 }
 ASSERT_EQ(count, 1);
 freeTree(root);
}

TEST(LabH_Test9, RightRotate_ValidArguments_Correct) {
 //Arrange
 SplayNode *root = newNode(3);
 root->left = newNode(2);
 root->left->left = newNode(1);

 //Act
 SplayNode *new_root = rightRotate(root);

 //Assert
 ASSERT_EQ(new_root->key, 2);
 ASSERT_EQ(new_root->right->key, 3);
 ASSERT_EQ(new_root->left->key, 1);
 ASSERT_EQ(new_root->right->left, nullptr);
 ASSERT_EQ(new_root->right->right, nullptr);

 freeTree(new_root);
}


TEST(LabH_Test10, LeftRotate_ValidArguments_Correct) {
 //Arrange
 SplayNode *root = newNode(1);
 root->right = newNode(2);
 root->right->right = newNode(3);

 //Act
 root = leftRotate(root);

 //Assert
 ASSERT_EQ(root->key, 2);
 ASSERT_EQ(root->left->key, 1);
 ASSERT_EQ(root->right->key, 3);

 freeTree(root);
}