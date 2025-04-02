#include <gtest/gtest.h>
#include "avl_list.h" 

TEST(Insert_NonEmptyList_ElementAdded) {
	AVLList list;
	list.insert(0, 10);
	list.insert(0, 20);
	EXPECT_EQ(list.size(), 2);
}

TEST(Insert_EmptyList_ElementAdded) {
	AVLList list;
	list.insert(0, 10);
	EXPECT_EQ(list.size(), 1);
}

TEST(Get_ValidIndex_ReturnsValue) {
	AVLList list;
	list.insert(0, 10);
	list.insert(0, 20);
	EXPECT_EQ(list.get(0), 20);
	EXPECT_EQ(list.get(1), 10);
}

TEST(Get_InvalidIndex_ThrowsException) {
	AVLList list;
	EXPECT_THROW(list.get(0), std::out_of_range);
	list.insert(0, 10);
	EXPECT_THROW(list.get(1), std::out_of_range);
}

TEST(Search_ExistingElement_ReturnsTrue) {
	AVLList list;
	list.insert(0, 10);
	list.insert(0, 20);
	EXPECT_TRUE(list.search(10));
	EXPECT_TRUE(list.search(20));
}

TEST(Search_NonExistingElement_ReturnsFalse) {
	AVLList list;
	list.insert(0, 10);
	EXPECT_FALSE(list.search(20));
}

TEST(Remove_ValidIndex_ElementRemoved) {
	AVLList list;
	list.insert(0, 10);
	list.insert(0, 20);
	list.remove(0);
	EXPECT_EQ(list.size(), 1);
	EXPECT_FALSE(list.search(20));
}

TEST(Remove_InvalidIndex_ThrowsException) {
	AVLList list;
	EXPECT_THROW(list.remove(0), std::out_of_range);
	list.insert(0, 10);
	EXPECT_THROW(list.remove(1), std::out_of_range);
}

TEST(Concatenate_TwoNonEmptyLists_ListsMerged) {
	AVLList list1;
	list1.insert(0, 10);
	list1.insert(0, 20);

	AVLList list2;
	list2.insert(0, 30);
	list2.insert(0, 40);

	list1.concatenate(list2);
	EXPECT_EQ(list1.size(), 4);
	EXPECT_EQ(list2.size(), 0);
}

TEST(Concatenate_EmptyAndNonEmptyList_ListMerged) {
	AVLList list1;
	AVLList list2;
	list2.insert(0, 10);

	list1.concatenate(list2);
	EXPECT_EQ(list1.size(), 1);
	EXPECT_EQ(list2.size(), 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}