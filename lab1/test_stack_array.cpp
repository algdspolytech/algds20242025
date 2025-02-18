#include "gtest/gtest.h"
#include "stack_array.h"  
#include <climits>

using namespace ::testing;

TEST(StackArrayTest, CreateDeleteStack) {
  Stack* stack = createStack();
  ASSERT_NE(stack, nullptr);
  deleteStack(stack);
}

TEST(StackArrayTest, IsEmpty) {
  Stack* stack = createStack();
  ASSERT_EQ(isEmpty(stack), 1);
  push(stack, 10);
  ASSERT_EQ(isEmpty(stack), 0);
  pop(stack);
  ASSERT_EQ(isEmpty(stack), 1);
  deleteStack(stack);
}

TEST(StackArrayTest, IsFull) {
  Stack* stack = createStack();
  for (int i = 0; i < STACK_SIZE; ++i) {
    push(stack, i);
  }
  ASSERT_EQ(isFull(stack), 1);
  deleteStack(stack);
}

TEST(StackArrayTest, PushPop) {
  Stack* stack = createStack();
  push(stack, 10);
  push(stack, 20);
  ASSERT_EQ(pop(stack), 20);
  ASSERT_EQ(pop(stack), 10);
  ASSERT_EQ(pop(stack), INT_MIN); 
  deleteStack(stack);
}

TEST(StackArrayTest, Peek) {
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

TEST(StackArrayTest, ClearStack) {
  Stack* stack = createStack();
  push(stack, 10);
  push(stack, 20);
  clearStack(stack);
  ASSERT_EQ(isEmpty(stack), 1);
  deleteStack(stack);
}