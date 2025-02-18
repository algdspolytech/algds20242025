#include "pch.h"
extern "C"
{
#include "LabF.h"
}


TEST(LabF, InsertSingleInterval) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 10, 20);


	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->interval.start, 10);
	EXPECT_EQ(root->interval.end, 20);
	EXPECT_EQ(root->maxEnd, 20);

	freeIntervalTree(root);
}

TEST(LabF, InsertMultipleIntervals) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 15, 20);
	root = insertInterval(root, 10, 30);
	root = insertInterval(root, 5, 10);

	IntervalNode* n1 = findInterval(root, 15, 20);
	IntervalNode* n2 = findInterval(root, 10, 30);
	IntervalNode* n3 = findInterval(root, 5, 10);

	EXPECT_NE(n1, nullptr);
	EXPECT_NE(n2, nullptr);
	EXPECT_NE(n3, nullptr);

	freeIntervalTree(root);
}

TEST(LabF, FindExactInterval) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 10, 30);
	root = insertInterval(root, 15, 20);

	IntervalNode* found = findInterval(root, 15, 20);
	EXPECT_NE(found, nullptr);
	if (found) {
		EXPECT_EQ(found->interval.start, 15);
		EXPECT_EQ(found->interval.end, 20);
	}

	freeIntervalTree(root);
}

TEST(LabF, FindNonExistingInterval) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 10, 20);
	root = insertInterval(root, 5, 15);

	IntervalNode* found = findInterval(root, 7, 7);
	EXPECT_EQ(found, nullptr);

	freeIntervalTree(root);
}

TEST(LabF, FindOverlappingIntervals) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 15, 20);
	root = insertInterval(root, 10, 30);
	root = insertInterval(root, 5, 10);
	root = insertInterval(root, 17, 19);

	testing::internal::CaptureStdout();
	findAllOverlappingIntervals(root, 14, 16);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_TRUE(output.find("[15, 20]") != std::string::npos);
	EXPECT_TRUE(output.find("[10, 30]") != std::string::npos);

	EXPECT_TRUE(output.find("[5, 10]") == std::string::npos);

	freeIntervalTree(root);
}

TEST(LabF, FindOverlappingIntervalsNone) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 1, 2);
	root = insertInterval(root, 3, 4);
	root = insertInterval(root, 10, 20);

	testing::internal::CaptureStdout();
	findAllOverlappingIntervals(root, 5, 6);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_TRUE(output.find("Пересекается:") == std::string::npos);

	freeIntervalTree(root);
}

TEST(LabF, DeleteLeafInterval) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 10, 20);
	root = insertInterval(root, 5, 8);
	root = insertInterval(root, 15, 25);

	root = deleteInterval(root, 5, 8);

	IntervalNode* found = findInterval(root, 5, 8);
	EXPECT_EQ(found, nullptr);

	freeIntervalTree(root);
}

TEST(LabF, DeleteIntervalOneChild) {
	IntervalNode* root = NULL;

	root = insertInterval(root, 10, 20);
	root = insertInterval(root, 5, 10);
	root = insertInterval(root, 6, 7);

	root = deleteInterval(root, 5, 10);

	IntervalNode* found = findInterval(root, 5, 10);
	EXPECT_EQ(found, nullptr);

	found = findInterval(root, 6, 7);
	EXPECT_NE(found, nullptr);

	freeIntervalTree(root);
}

TEST(LabF, DeleteIntervalTwoChildren) {
	IntervalNode* root = NULL;

	root = insertInterval(root, 10, 20);
	root = insertInterval(root, 5, 8);
	root = insertInterval(root, 15, 25);
	root = insertInterval(root, 12, 13);
	root = insertInterval(root, 18, 19);

	root = deleteInterval(root, 10, 20);

	IntervalNode* found = findInterval(root, 10, 20);
	EXPECT_EQ(found, nullptr);

	EXPECT_NE(findInterval(root, 5, 8), nullptr);
	EXPECT_NE(findInterval(root, 15, 25), nullptr);

	freeIntervalTree(root);
}

TEST(LabF, CheckMaxEnd) {
	IntervalNode* root = NULL;
	root = insertInterval(root, 10, 20);
	root = insertInterval(root, 5, 30);
	root = insertInterval(root, 15, 25);

	EXPECT_EQ(root->maxEnd, 30);

	root = deleteInterval(root, 5, 30);
	EXPECT_EQ(root->maxEnd, 25);

	freeIntervalTree(root);
}