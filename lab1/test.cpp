#include "gtest/gtest.h"
#include "priorityqueue.h"

TEST(CreateTest, EqualsManualCreate) {
	struct PriorityQueue manual = {1, 1, NULL};
	struct PriorityQueue* test = PrQcreate(1,1);
	EXPECT_EQ(test->data, manual.data);
	PrQclear(test);
}

TEST(ClearTest, HandlesNullQueue) {
	EXPECT_NO_THROW(PrQclear(NULL));
}

TEST(ClearTest, HandlesQueueLength1) {
	struct PriorityQueue* test = PrQcreate(1, 1);
	EXPECT_NO_THROW(PrQclear(test));
}

TEST(ClearTest, HandlesQueueLengthMoreThan1) {
	struct PriorityQueue* test = PrQcreate(1, 1);
	test = PrQinsert(test,2,2);
	EXPECT_NO_THROW(PrQclear(test));
}

TEST(InsertTest, HandlesFirst) {
	struct PriorityQueue* test = PrQcreate(2,2);
	test = PrQinsert(test, 1, 1);
	EXPECT_EQ(test->data, 1);
	ASSERT_NE((int)test->next, NULL);
	EXPECT_EQ(test->next->data, 2);
	EXPECT_EQ((int)test->next->next, NULL);
	PrQclear(test);
}

TEST(InsertTest, HandlesLast) {
	struct PriorityQueue* test = PrQcreate(1, 1);
	test = PrQinsert(test, 2, 2);
	EXPECT_EQ(test->data, 1);
	ASSERT_NE((int)test->next, NULL);
	EXPECT_EQ(test->next->data, 2);
	EXPECT_EQ((int)test->next->next, NULL);
	PrQclear(test);
}

TEST(InsertTest, HandlesMiddle) {
	struct PriorityQueue* test = PrQcreate(3, 3);
	test = PrQinsert(test, 1, 1);
	test = PrQinsert(test, 2, 2);
	EXPECT_EQ(test->data, 1);
	ASSERT_NE((int)test->next, NULL);
	EXPECT_EQ(test->next->data, 2);
	ASSERT_NE((int)test->next->next, NULL);
	EXPECT_EQ(test->next->next->data, 3);
	EXPECT_EQ((int)test->next->next->next, NULL);
	PrQclear(test);
}

TEST(InsertTest, HandlesNullQueue) {
	struct PriorityQueue* test = PrQinsert(NULL, 1, 1);
	EXPECT_EQ(test->data, 1);
	PrQclear(test);
}

TEST(ExtractTest, HandlesNullQueue) {
	EXPECT_EQ(PrQextractMinimum(NULL), NULL);
}

TEST(ExtractTest, HandlesQueueLength1) {
	struct PriorityQueue* test = PrQcreate( 1, 1);
	EXPECT_EQ(PrQextractMinimum(test), 1);
}

TEST(ExtractTest, HandlesQueueLengthMoreThan1) {
	struct PriorityQueue* test = PrQcreate(1, 1);
	test = PrQinsert(test, 2, 2);
	EXPECT_EQ(PrQextractMinimum(test), 1);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}