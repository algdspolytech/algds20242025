#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "gtest/gtest.h"

extern "C" {
#include "..\rucksack\rucksack.h"
#include "..\rucksack\rucksack.c"
}
struct TestData {
    int U; 
    int B; 
    int K; 
    int weights[6]; 
    int values[6]; 
    int expected; 
};

void RunTest(const TestData& data) {
    int result = knapsack(data.U, data.B, data.K, data.weights, data.values);
    EXPECT_EQ(result, data.expected);
}

TEST(KnapsackTests, Test1) {
    TestData data = { 5, 10, 15, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, 0 };
    RunTest(data);
}

TEST(KnapsackTests, Test2) {
    TestData data = { 5, 5, 10, {1, 2, 3, 4, 5}, {10, 20, 30, 40, 50}, 1 };
    RunTest(data);
}

TEST(KnapsackTests, Test3) {
    TestData data = { 3, 6, 10, {1, 2, 3}, {10, 20, 30}, 1 };
    RunTest(data);
}

TEST(KnapsackTests, Test4) {
    TestData data = { 4, 10, 20, {2, 3, 4, 5}, {10, 15, 25, 30}, 1 };
    RunTest(data);
}

TEST(KnapsackTests, Test5) {
    TestData data = { 3, 10, 25, {5, 6, 7}, {10, 15, 20}, 0 };
    RunTest(data);
}

TEST(KnapsackTests, Test6) {
    TestData data = { 5, 15, 30, {1, 3, 4, 5, 7}, {5, 10, 15, 20, 25}, 1 };
    RunTest(data);
}

TEST(KnapsackTests, Test7) {
    TestData data = { 6, 10, 40, {2, 2, 3, 3, 4, 5}, {10, 10, 20, 20, 30, 40}, 1 };
    RunTest(data);
}

TEST(KnapsackTests, Test8) {
    TestData data = { 4, 9, 50, {1, 2, 3, 4}, {10, 20, 30, 40}, 1 };
    RunTest(data);
}

TEST(KnapsackTests, Test9) {
    TestData data = { 5, 8, 15, {10, 10, 10, 10, 10}, {10, 15, 25, 30, 35}, 0 };
    RunTest(data);
}

TEST(KnapsackTests, Test10) {
    TestData data = { 5, 20, 50, {1, 4, 5, 6, 8}, {10, 20, 30, 40, 50}, 1 };
    RunTest(data);
}