#include <gtest/gtest.h>
#include "algosD/algos_4.h"  


TEST(subsetSum_EmptyArray_returnFalse, EmptyArray) {
    int arr[] = {};
    int B = 10;
    int result[10];
    int resultSize = 0;

    EXPECT_FALSE(subsetSum(arr, 0, B, result, &resultSize));
}

TEST(subsetSum_SingleElementEqualToB_returnTrue, SingleElementEqual) {
    int arr[] = { 10 };
    int B = 10;
    int result[10];
    int resultSize = 0;

    EXPECT_TRUE(subsetSum(arr, 1, B, result, &resultSize));
    EXPECT_EQ(resultSize, 1);
    EXPECT_EQ(result[0], 10);
}

TEST(subsetSum_SingleElementNotEqualToB_returnFalse, SingleElementNotEqual) {
    int arr[] = { 5 };
    int B = 10;
    int result[10];
    int resultSize = 0;

    EXPECT_FALSE(subsetSum(arr, 1, B, result, &resultSize));
}

TEST(subsetSum_MultipleElementsSumEqualsB_returnTrue, MultipleElementsSumEqual) {
    int arr[] = { 2, 3, 4, 5, 9 };
    int B = 10;
    int result[10];
    int resultSize = 0;

    EXPECT_TRUE(subsetSum(arr, 5, B, result, &resultSize));
    EXPECT_EQ(resultSize, 3);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 5);
}

TEST(subsetSum_MultipleElementsNoSubsetEqualsB_returnFalse, NoSubsetSumEqual) {
    int arr[] = { 1, 2, 3, 4 };
    int B = 10;
    int result[10];
    int resultSize = 0;

    EXPECT_FALSE(subsetSum(arr, 4, B, result, &resultSize));
}

TEST(subsetSum_BEqualZero_returnTrue, BEqualZero) {
    int arr[] = { 1, 2, 3 };
    int B = 0;
    int result[10];
    int resultSize = 0;

    EXPECT_TRUE(subsetSum(arr, 3, B, result, &resultSize));
    EXPECT_EQ(resultSize, 0);
}

TEST(subsetSum_BGreaterThanSumOfArray_returnFalse, BGreaterThanArraySum) {
    int arr[] = { 1, 2, 3 };
    int B = 10;
    int result[10];
    int resultSize = 0;

    EXPECT_FALSE(subsetSum(arr, 3, B, result, &resultSize));
}

TEST(subsetSum_NegativeValueInArray_returnTrue, NegativeValueInArray) {
    int arr[] = { -1, 2, 3 };
    int B = 2;
    int result[10];
    int resultSize = 0;

    EXPECT_TRUE(subsetSum(arr, 3, B, result, &resultSize));
    EXPECT_EQ(resultSize, 1);
    EXPECT_EQ(result[0], 2);
}

TEST(subsetSum_LargeArray_returnTrue, LargeArray) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int B = 15;
    int result[10];
    int resultSize = 0;

    EXPECT_TRUE(subsetSum(arr, 10, B, result, &resultSize));
    EXPECT_EQ(resultSize, 2); // Примерный результат
    EXPECT_TRUE((result[0] == 6 && result[1] == 9) || (result[0] == 5 && result[1] == 10));
}

TEST(subsetSum_EmptyResultArray_returnFalse, NoSubsetFound) {
    int arr[] = { 1, 2, 3 };
    int B = 7;
    int result[10];
    int resultSize = 0;

    EXPECT_FALSE(subsetSum(arr, 3, B, result, &resultSize));
    EXPECT_EQ(resultSize, 0);
}

// main функция для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
