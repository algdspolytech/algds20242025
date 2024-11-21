#include "gtest/gtest.h"
#include <locale.h>

extern "C"
{
#include "XORLab.h"
}

TEST(XORLinkedListTest, AddSingleElement_no1) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Привет");

	EXPECT_EQ(strcmp(list.head->data, "Привет"), 0);
	EXPECT_EQ(strcmp(list.tail->data, "Привет"), 0);
	EXPECT_EQ(list.head, list.tail);
}

TEST(XORLinkedListTest, AddMultipleElements_no2) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");

	EXPECT_EQ(strcmp(list.head->data, "Первый"), 0);
	EXPECT_EQ(strcmp(list.tail->data, "Второй"), 0);
}

TEST(XORLinkedListTest, DeleteByKey_no3) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");
	add(&list, "Третий");

	delete_by_key(&list, "Третий");

	Node* node = find(&list, "Третий");
	EXPECT_EQ(node, nullptr);
	EXPECT_EQ(strcmp(list.head->data, "Первый"), 0);
	EXPECT_EQ(strcmp(list.tail->data, "Второй"), 0);
}

TEST(XORLinkedListTest, DeleteByNode_no4) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");

	Node* nodeToDelete = list.head;
	delete_by_address(&list, nodeToDelete);

	Node* node = find(&list, "Первый");
	EXPECT_EQ(node, nullptr);
	EXPECT_EQ(strcmp(list.head->data, "Второй"), 0);
}

TEST(XORLinkedListTest, FindElementByKey_no5) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");

	Node* node = find(&list, "Второй");
	EXPECT_NE(node, nullptr);
	EXPECT_EQ(strcmp(node->data, "Второй"), 0);
}

TEST(XORLinkedListTest, FindNonExistentElement_no6) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");

	Node* node = find(&list, "Третий");
	EXPECT_EQ(node, nullptr);
}

TEST(XORLinkedListTest, IterateList_no7) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");

	testing::internal::CaptureStdout();
	iterate(&list);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Первый Второй \n");
}

TEST(XORLinkedListTest, ClearList_no8) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");

	free_list(&list);

	Node* node = find(&list, "Первый");
	EXPECT_EQ(node, nullptr);
	node = find(&list, "Второй");
	EXPECT_EQ(node, nullptr);
}

TEST(XORLinkedListTest, DeleteElementFromEmptyList_no9) {
	XORLinkedList list = { NULL, NULL };

	delete_by_key(&list, "Не существует");

	EXPECT_EQ(list.head, nullptr);
	EXPECT_EQ(list.tail, nullptr);
}

TEST(XORLinkedListTest, DeleteByKeyMiddle_no10) {
	XORLinkedList list = { NULL, NULL };

	add(&list, "Первый");
	add(&list, "Второй");
	add(&list, "Третий");

	delete_by_key(&list, "Второй");

	Node* nodefirst = find(&list, "Первый");
	Node* nodesecond = find(&list, "Третий");
	Node* nodedel = find(&list, "Второй");
	EXPECT_EQ(nodedel, nullptr);
	EXPECT_EQ(strcmp(list.head->data, "Первый"), 0);
	EXPECT_EQ(XOR(NULL, nodesecond), nodefirst->link, 0);
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUS");
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}