#include "gtest/gtest.h"
#include "stack_linked_list.h"  
#include <climits>

using namespace ::testing;

TEST(StackLinkedListTest, CreateDeleteStack) {
  Stack* stack = createStack();
  ASSERT_NE(stack, nullptr);
  deleteStack(stack);
}

TEST(StackLinkedListTest, IsEmpty) {
  Stack* stack = createStack();
  ASSERT_EQ(isEmpty(stack), 1);
  push(stack, 10);
  ASSERT_EQ(isEmpty(stack), 0);
  pop(stack);
  ASSERT_EQ(isEmpty(stack), 1);
  deleteStack(stack);
}

TEST(StackLinkedListTest, PushPop) {
  Stack* stack = createStack();
  push(stack, 10);
  push(stack, 20);
  ASSERT_EQ(pop(stack), 20);
  ASSERT_EQ(pop(stack), 10);
  ASSERT_EQ(pop(stack), INT_MIN); 
  deleteStack(stack);
}

TEST(StackLinkedListTest, Peek) {
  Stack* stack = createStack();
  push(stack, 10);
  ASSERT_EQ(peek(stack), 10);
  push(stack, 20);
  ASSERT_EQ(peek(stack), 20);
  pop(stack);
  ASSERT_EQ(peek(stack), 10);
  pop(stack);
  ASSERT_EQ(peek(stack), INT_MIN); 
  deleteStack(stack);
}