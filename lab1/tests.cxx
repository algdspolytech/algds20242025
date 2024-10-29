#include <gtest/gtest.h>

extern "C" {
#include "labA.h"
}

TEST(LabATests, IsEmptyStack) {
    Stack *stack = createStack();
    ASSERT_TRUE(isEmpty(stack));
    free(stack);
}

TEST(LabATests, EmptyStackPop) {
    Stack *stack = createStack();
    ASSERT_EQ(pop(stack), -1);
    free(stack);
}

TEST(LabATests, EmptyStackPeek) {
    Stack *stack = createStack();
    ASSERT_EQ(peek(stack), -1);
    free(stack);
}

TEST(LabATests, PushPop) {
    Stack *stack = createStack();
    push(stack, 10);
    ASSERT_FALSE(isEmpty(stack));
    ASSERT_EQ(peek(stack), 10);
    ASSERT_EQ(pop(stack), 10);
    ASSERT_TRUE(isEmpty(stack));
    free(stack);
}

TEST(LabATests, MultiplePushPop) {
    Stack *stack = createStack();
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    ASSERT_EQ(peek(stack), 30);
    ASSERT_EQ(pop(stack), 30);
    ASSERT_EQ(peek(stack), 20);
    ASSERT_EQ(pop(stack), 20);
    ASSERT_EQ(peek(stack), 10);
    ASSERT_EQ(pop(stack), 10);
    ASSERT_TRUE(isEmpty(stack));
    free(stack);
}

TEST(LabATests, Peek) {
    Stack *stack = createStack();
    push(stack, 10);
    ASSERT_EQ(peek(stack), 10);
    push(stack, 20);
    ASSERT_EQ(peek(stack), 20);
    free(stack);
}

TEST(LabATests, PushOneElement) {
    Stack *stack = createStack();
    push(stack, 5);
    ASSERT_EQ(peek(stack), 5);
    free(stack);
}

TEST(LabATests, PopLastElement) {
    Stack *stack = createStack();
    push(stack, 1);
    push(stack, 2);
    ASSERT_EQ(pop(stack), 2);
    ASSERT_EQ(peek(stack), 1);
    free(stack);
}

TEST(LabATests, EmptyAfterMultiplePops) {
    Stack *stack = createStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    pop(stack);
    pop(stack);
    pop(stack);
    ASSERT_TRUE(isEmpty(stack));
    free(stack);
}

TEST(LabATests, PeekAfterMultiplePushes) {
    Stack *stack = createStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    ASSERT_EQ(peek(stack), 3);
    free(stack);
}
TEST(LabATests, IsEmptyArrayStack) {
    ArrayStack *stack = createArrayStack(10);
    ASSERT_TRUE(isEmptyArrayStack(stack));
    free(stack->data);
    free(stack);
}

TEST(LabATests, EmptyArrayStackPop) {
    ArrayStack *stack = createArrayStack(10);
    ASSERT_EQ(popArrayStack(stack), -1);
    free(stack->data);
    free(stack);
}

TEST(LabATests, PushArrayPop) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 10);
  ASSERT_FALSE(isEmptyArrayStack(stack));
  ASSERT_EQ(peekArrayStack(stack), 10);
  ASSERT_EQ(popArrayStack(stack), 10);
  ASSERT_TRUE(isEmptyArrayStack(stack));
  free(stack->data);
  free(stack);
}

TEST(LabATests, MultiplePushArrayPop) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 10);
  pushArrayStack(stack, 20);
  pushArrayStack(stack, 30);
  ASSERT_EQ(peekArrayStack(stack), 30);
  ASSERT_EQ(popArrayStack(stack), 30);
  ASSERT_EQ(peekArrayStack(stack), 20);
  ASSERT_EQ(popArrayStack(stack), 20);
  ASSERT_EQ(peekArrayStack(stack), 10);
  ASSERT_EQ(popArrayStack(stack), 10);
  ASSERT_TRUE(isEmptyArrayStack(stack));
  free(stack->data);
  free(stack);
}

TEST(LabATests, PeekArray) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 10);
  ASSERT_EQ(peekArrayStack(stack), 10);
  pushArrayStack(stack, 20);
  ASSERT_EQ(peekArrayStack(stack), 20);
  free(stack->data);
  free(stack);
}

TEST(LabATests, PushOneElementArray) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 5);
  ASSERT_EQ(peekArrayStack(stack), 5);
  free(stack->data);
  free(stack);
}

TEST(LabATests, PopLastElementArray) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 1);
  pushArrayStack(stack, 2);
  ASSERT_EQ(popArrayStack(stack), 2);
  ASSERT_EQ(peekArrayStack(stack), 1);
  free(stack->data);
  free(stack);
}

TEST(LabATests, EmptyAfterMultiplePopsArray) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 1);
  pushArrayStack(stack, 2);
  pushArrayStack(stack, 3);
  popArrayStack(stack);
  popArrayStack(stack);
  popArrayStack(stack);
  ASSERT_TRUE(isEmptyArrayStack(stack));
  free(stack->data);
  free(stack);
}

TEST(LabATests, PeekAfterMultiplePushesArray) {
  ArrayStack *stack = createArrayStack(10);
  pushArrayStack(stack, 1);
  pushArrayStack(stack, 2);
  pushArrayStack(stack, 3);
  ASSERT_EQ(peekArrayStack(stack), 3);
  free(stack->data);
  free(stack);
}

TEST(LabATests, ArrayStackOverflow) {
  ArrayStack *stack = createArrayStack(3);
  pushArrayStack(stack, 1);
  pushArrayStack(stack, 2);
  pushArrayStack(stack, 3);
  pushArrayStack(stack, 4);
  free(stack->data);
  free(stack);
}