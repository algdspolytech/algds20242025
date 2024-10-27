#include <gtest/gtest.h>

extern "C" {
#include "LLStack.h"
#include "ArrStack.h"
}

TEST(LLStackTest, CreateStack) {
    LLStack_t stack = LLStackCreate();
    EXPECT_TRUE(LLStackEmpty(&stack));
}

TEST(LLStackTest, PushElement) {
    LLStack_t stack = LLStackCreate();
    int value = 42;
    LLStackPush(&stack, &value);
    EXPECT_FALSE(LLStackEmpty(&stack));
}

TEST(LLStackTest, PeekTopElement) {
    LLStack_t stack = LLStackCreate();
    int value1 = 42;
    int value2 = 99;
    LLStackPush(&stack, &value1);
    LLStackPush(&stack, &value2);

    int* topValue = (int*)LLStackPeek(&stack);
    EXPECT_EQ(*topValue, value2);
}

TEST(LLStackTest, PopElement) {
    LLStack_t stack = LLStackCreate();
    int value1 = 42;
    int value2 = 99;
    LLStackPush(&stack, &value1);
    LLStackPush(&stack, &value2);

    void* poppedValue = LLStackPop(&stack);
    EXPECT_EQ(*(int*)poppedValue, value2);

    int* newTopValue = (int*)LLStackPeek(&stack);
    EXPECT_EQ(*newTopValue, value1);
}

TEST(LLStackTest, EmptyAfterPops) {
    LLStack_t stack = LLStackCreate();
    int value1 = 42;
    int value2 = 99;
    LLStackPush(&stack, &value1);
    LLStackPush(&stack, &value2);

    LLStackPop(&stack);
    LLStackPop(&stack);

    EXPECT_TRUE(LLStackEmpty(&stack));
}

TEST(ArrStackTest, CreateStack) {
    ArrStack_t stack = ArrStackCreate();
    EXPECT_TRUE(ArrStackEmpty(&stack));
    ArrStackDestroy(&stack);
}

TEST(ArrStackTest, PushElement) {
    ArrStack_t stack = ArrStackCreate();
    int value = 42;
    ArrStackPush(&stack, &value);
    EXPECT_FALSE(ArrStackEmpty(&stack));
    ArrStackDestroy(&stack);
}

TEST(ArrStackTest, PeekTopElement) {
    ArrStack_t stack = ArrStackCreate();
    int value1 = 42;
    int value2 = 99;
    ArrStackPush(&stack, &value1);
    ArrStackPush(&stack, &value2);

    int* topValue = (int*)ArrStackPeek(&stack);
    EXPECT_EQ(*topValue, value2);
    ArrStackDestroy(&stack);
}

TEST(ArrStackTest, PopElement) {
    ArrStack_t stack = ArrStackCreate();
    int value1 = 42;
    int value2 = 99;
    ArrStackPush(&stack, &value1);
    ArrStackPush(&stack, &value2);

    void* poppedValue = ArrStackPop(&stack);
    EXPECT_EQ(*(int*)poppedValue, value2);

    int* newTopValue = (int*)ArrStackPeek(&stack);
    EXPECT_EQ(*newTopValue, value1);
    ArrStackDestroy(&stack);
}

TEST(ArrStackTest, ResizeOnPush) {
    ArrStack_t stack = ArrStackCreate();

    for (int i = 0; i <= 1024; ++i) {
        int *value = new int(i);
        ArrStackPush(&stack, value);
    }

    int* topValue = (int*)ArrStackPeek(&stack);
    EXPECT_EQ(*topValue, 1024);

    while (!ArrStackEmpty(&stack)) {
        delete (int*)ArrStackPop(&stack);
    }

    ArrStackDestroy(&stack);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
