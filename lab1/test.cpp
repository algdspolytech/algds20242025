#include "Extended_Linked_List.h"
#include <gtest/gtest.h>

using namespace std;

struct TestList : public testing::Test {
  Node *head;

  void SetUp() {
    head = CreateList();
    for (int i = 0; i < 20; i++) {
      InsertElement(head, 0, i);
    }
  }
  void TearDown() { DeleteList(head); }
};

struct NullTestList : public testing::Test {
  Node *head;
  void SetUp() {
    head = CreateList();
    for (int i = 0; i < 20; i++) {
      if (i % 3 == 0) {
        InsertElement(head, 0, NULL);
      } else {
        InsertElement(head, 0, i);
      }
    }
  }

  void TearDown() { DeleteList(head); }
};

TEST(ExtendedLinkedList, InsertingElement_no1) {
  Node *head = CreateList();
  int result = InsertElement(head, 0, 0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(head->data[0], 0);
  DeleteList(head);
}

TEST(ExtendedLinkedList, InsertElementInNotExistingIndex_no2) {
  Node *head = CreateList();
  int result = InsertElement(head, 1, 0);
  EXPECT_EQ(result, 1);
  DeleteList(head);
}

TEST(ExtendedLinkedList, DeleteTheOnlyOneElement_no3) {
  Node *head = CreateList();
  int result = InsertElement(head, 0, 0);
  RemoveElementWithIndex(head, 0);
  EXPECT_TRUE(head->next == NULL);
  EXPECT_TRUE(head != NULL);
}

TEST_F(TestList, FindElement_no4) {
  int *ele = FindElementWithIndex(head, 21);
  EXPECT_EQ(ele[1], 0);
  EXPECT_EQ(ele[0], 6);
}

TEST_F(TestList, FindElementWithNotExistingIndex_no5) {
  int *ele = FindElementWithIndex(head, 30);

  EXPECT_EQ(ele[1], -1);
  free(ele);
  ele = FindElementWithIndex(head, -10);

  EXPECT_EQ(ele[1], -1);
  free(ele);
}

TEST_F(TestList, FindIndex_no6) {
  int pos1 = FindIndexWithKey(head, 9);

  ASSERT_EQ(pos1, 24);
}

TEST_F(TestList, FindIndexWithNotExistingElement_no7) {
  int pos1 = FindIndexWithKey(head, 30);

  ASSERT_EQ(pos1, -1);
}

TEST_F(TestList, RemoveElementWithNotExistingIndex_no8) {
  int result = RemoveElementWithIndex(head, -10);
  EXPECT_EQ(result, -1);
  result = RemoveElementWithIndex(head, 18);
  EXPECT_EQ(result, 1);
  result = RemoveElementWithIndex(head, 31);
  EXPECT_EQ(result, 1);
}

TEST_F(TestList, RemoveLastElement_no9) {
  int result = RemoveElementWithIndex(head, 24);
  EXPECT_EQ(result, 0);
  int *ele = FindElementWithIndex(head, 24);
  EXPECT_EQ(ele[1], -1);
  EXPECT_EQ(head->next->next->current_length, 4);
}

TEST_F(TestList, RemoveElement_no10) {
  int result = RemoveElementWithIndex(head, 10);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(head->next->data[0], 11);
  EXPECT_EQ(head->next->data[4], 5);
  EXPECT_EQ(head->next->data[5], 6);
}

TEST_F(NullTestList, FindNullElement_no11) {
  int position = FindIndexWithKey(head, NULL);
  EXPECT_EQ(position, 2);
}

TEST_F(NullTestList, FindNullWithIndex_no12) {
  int *result = FindElementWithIndex(head, 2);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[0], NULL);
}

TEST_F(NullTestList, RemoveNullElement_no13) {
  int result = RemoveElementWithIndex(head, 2);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(head->next->data[2], 4);
}

TEST(ExtendedLinkedList, InfinityNexElement_no14) {
  Node *head = CreateList();
  Node *temp = NextElement(head);
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(temp == NULL);
    temp = NextElement(temp);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}