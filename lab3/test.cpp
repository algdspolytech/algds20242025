#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\User\OneDrive\Desktop\test\algds20242025\lab3\Rukzak\Rukzak\main.h"

// Тестовые данные
struct TestData {
    int U; // Количество предметов
    int B; // Вместимость рюкзака
    int K; // Минимальная стоимость
    int weights[5]; // Веса предметов
    int values[5]; // Ценности предметов
    int expected; // Ожидаемый результат
};

// Функция для выполнения теста
void RunKnapsackTest(const TestData& data) {
    int* selected_items = nullptr;
    int result = knapsack(data.U, data.B, data.K, data.weights, data.values, &selected_items);
    EXPECT_EQ(result, data.expected);
    free(selected_items); // Освобождение памяти
}

// Тесты
TEST(KnapsackTests, Test1) {
    TestData data = { 5, 10, 15, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, 1 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test2) {
    TestData data = { 5, 5, 10, {1, 2, 3, 4, 5}, {10, 20, 30, 40, 50}, 0 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test3) {
    TestData data = { 3, 6, 10, {1, 2, 3}, {10, 20, 30}, 1 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test4) {
    TestData data = { 4, 10, 20, {2, 3, 4, 5}, {10, 15, 25, 30}, 1 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test5) {
    TestData data = { 3, 10, 25, {5, 6, 7}, {10, 15, 20}, 0 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test6) {
    TestData data = { 5, 15, 30, {1, 3, 4, 5, 7}, {5, 10, 15, 20, 25}, 1 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test7) {
    TestData data = { 6, 10, 40, {2, 2, 3, 3, 4, 5}, {10, 10, 20, 20, 30, 40}, 1 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test8) {
    TestData data = { 4, 9, 50, {1, 2, 3, 4}, {10, 20, 30, 40}, 1 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test9) {
    TestData data = { 5, 8, 15, {2, 3, 5, 7, 8}, {10, 15, 25, 30, 35}, 0 };
    RunKnapsackTest(data);
}

TEST(KnapsackTests, Test10) {
    TestData data = { 5, 20, 50, {1, 4, 5, 6, 8}, {10, 20, 30, 40, 50}, 1 };
    RunKnapsackTest(data);
}