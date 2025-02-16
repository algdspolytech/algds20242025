#include "pch.h"
extern "C"
{
#include "LabD.h"
}


TEST(SubsetSumTest, ExampleCase) {
	int B = 10;
	int A[] = { 2, 3, 4, 5, 9 };
	int N = 5;
	int dp[5] = { 0 };
	int res[5];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	int sum = 0;
	for (int i = 0; i < resSize; i++) sum += res[i];
	EXPECT_TRUE(flag == 1 && sum == B);
}

TEST(SubsetSumTest, NoSolution) {
	int B = 100;
	int A[] = { 1, 2, 3 };
	int N = 3;
	int dp[3] = { 0 };
	int res[3];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	EXPECT_TRUE(flag == 0);
}

TEST(SubsetSumTest, SingleElementSolution) {
	int B = 7;
	int A[] = { 1, 7, 8, 10 };
	int N = 4;
	int dp[4] = { 0 };
	int res[4];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	EXPECT_TRUE(flag == 1 && resSize == 1 && res[0] == 7);
}

TEST(SubsetSumTest, MultipleElementsSolution) {
	int B = 15;
	int A[] = { 1, 3, 5, 7, 9 };
	int N = 5;
	int dp[5] = { 0 };
	int res[5];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	int sum = 0;
	for (int i = 0; i < resSize; i++) sum += res[i];
	EXPECT_TRUE(flag == 1 && sum == B);
}

TEST(SubsetSumTest, LargeNumbers) {
	int B = 32256;
	int A[] = { 16384, 8192, 4096, 2048, 1024, 512 };
	int N = 6;
	int dp[6] = { 0 };
	int res[6];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	int sum = 0;
	for (int i = 0; i < resSize; i++) sum += res[i];
	EXPECT_TRUE(flag == 1 && sum == B);
}

TEST(SubsetSumTest, AllElementsUsed) {
	int B = 18;
	int A[] = { 2, 4, 6, 6 };
	int N = 4;
	int dp[4] = { 0 };
	int res[4];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	int sum = 0;
	for (int i = 0; i < resSize; i++) sum += res[i];
	EXPECT_TRUE(flag == 1 && sum == B);
}

TEST(SubsetSumTest, SingleLargeElement) {
	int B = 50;
	int A[] = { 50, 20, 30, 10 };
	int N = 4;
	int dp[4] = { 0 };
	int res[4];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	EXPECT_TRUE(flag == 1 && resSize == 1 && res[0] == 50);
}

TEST(SubsetSumTest, SmallNumbers) {
	int B = 6;
	int A[] = { 1, 2, 3 };
	int N = 3;
	int dp[3] = { 0 };
	int res[3];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	int sum = 0;
	for (int i = 0; i < resSize; i++) sum += res[i];
	EXPECT_TRUE(flag == 1 && sum == B);
}

TEST(SubsetSumTest, LargeSet) {
	int B = 55;
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int N = 10;
	int dp[10] = { 0 };
	int res[10];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	int sum = 0;
	for (int i = 0; i < resSize; i++) sum += res[i];
	EXPECT_TRUE(flag == 1 && sum == B);
}

TEST(SubsetSumTest, EdgeCase_MinimalInput) {
	int B = 1;
	int A[] = { 1 };
	int N = 1;
	int dp[1] = { 0 };
	int res[1];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	EXPECT_TRUE(flag == 1 && resSize == 1 && res[0] == 1);
}

TEST(SubsetSumTest, EdgeCase_LargeImpossibleSum) {
	int B = 1000;
	int A[] = { 1, 2, 3, 4, 5 };
	int N = 5;
	int dp[5] = { 0 };
	int res[5];
	int resSize = 0;
	int flag = 0;
	sum_size(&B, &N, A, dp, 0, &flag, res, &resSize);
	EXPECT_TRUE(flag == 0);
}
