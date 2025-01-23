#include <gtest/gtest.h>
#include "sum_sizes.h"  


TEST(sumSizes_EmptyArray_returnFalse, EmptyArray) {
    int arr[] = {};
    int B = 10;
    int res[10];
    int resSize = 0;

    EXPECT_FALSE(sumSizes(arr, 0, B, res, &resSize));
}

TEST(sumSizes_SingleElementEqualToB_returnTrue, SingleElementEqual) {
    int arr[] = { 10 };
    int B = 10;
    int res[10];
    int resSize = 0;

    EXPECT_TRUE(sumSizes(arr, 1, B, res, &resSize));
    EXPECT_EQ(resSize, 1);
    EXPECT_EQ(res[0], 10);
}

TEST(sumSizes_SingleElementNotEqualToB_returnFalse, SingleElementNotEqual) {
    int arr[] = { 5 };
    int B = 10;
    int res[10];
    int resSize = 0;

    EXPECT_FALSE(sumSizes(arr, 1, B, res, &resSize));
}

TEST(sumSizes_MultipleElementsSumEqualsB_returnTrue, MultipleElementsSumEqual) {
    int arr[] = { 2, 3, 4, 5, 9 };
    int B = 10;
    int res[10];
    int resSize = 0;

    EXPECT_TRUE(sumSizes(arr, 5, B, res, &resSize));
    EXPECT_EQ(resSize, 3);
    EXPECT_EQ(res[0], 2);
    EXPECT_EQ(res[1], 3);
    EXPECT_EQ(res[2], 5);
}

TEST(sumSizes_MultipleElementsNoSubsetEqualsB_returnFalse, NosumSizesEqual) {
    int arr[] = { 1, 2, 3, 4 };
    int B = 10;
    int res[10];
    int resSize = 0;

    EXPECT_FALSE(sumSizes(arr, 4, B, res, &resSize));
}

TEST(sumSizes_BEqualZero_returnTrue, BEqualZero) {
    int arr[] = { 1, 2, 3 };
    int B = 0;
    int res[10];
    int resSize = 0;

    EXPECT_TRUE(sumSizes(arr, 3, B, res, &resSize));
    EXPECT_EQ(resSize, 0);
}

TEST(sumSizes_BGreaterThanSumOfArray_returnFalse, BGreaterThanArraySum) {
    int arr[] = { 1, 2, 3 };
    int B = 10;
    int res[10];
    int resSize = 0;

    EXPECT_FALSE(sumSizes(arr, 3, B, res, &resSize));
}

TEST(sumSizes_NegativeValueInArray_returnTrue, NegativeValueInArray) {
    int arr[] = { -1, 2, 3 };
    int B = 2;
    int res[10];
    int resSize = 0;

    EXPECT_TRUE(sumSizes(arr, 3, B, res, &resSize));
    EXPECT_EQ(resSize, 1);
    EXPECT_EQ(res[0], 2);
}

TEST(sumSizes_LargeArray_returnTrue, LargeArray) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int B = 15;
    int res[10];
    int resSize = 0;

    EXPECT_TRUE(sumSizes(arr, 10, B, res, &resSize));
    EXPECT_EQ(resSize, 2); 
    EXPECT_TRUE((res[0] == 6 && res[1] == 9) || (res[0] == 5 && res[1] == 10));
}

TEST(sumSizes_EmptyresArray_returnFalse, NoSubsetFound) {
    int arr[] = { 1, 2, 3 };
    int B = 7;
    int res[10];
    int resSize = 0;

    EXPECT_FALSE(sumSizes(arr, 3, B, res, &resSize));
    EXPECT_EQ(resSize, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
