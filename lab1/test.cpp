#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../algosi1/head.h"
}

TEST(CreateNodeTest, Success) {
	Temperature data = { 16, 6, 2019, 28 };

	Node* head = CreateNode(data);

	ASSERT_NE(head, nullptr);

	ASSERT_EQ(head->data.day, 16);
	ASSERT_EQ(head->data.month, 6);
	ASSERT_EQ(head->data.year, 2019);
	ASSERT_EQ(head->data.temp, 28);
	ASSERT_EQ(head->next, nullptr);
}

TEST(AddDataTest, EmptyFile) {
	FILE* fp = tmpfile();

	Node* head = AddData(fp);

	ASSERT_EQ(head, nullptr);

	fclose(fp);
}

TEST(AddDataTest, ValidData) {

	FILE* fp = tmpfile();
	fprintf(fp, "10.01.2024 15\n");
	fprintf(fp, "15.02.2016 -18\n");
	rewind(fp);
	head = AddData(fp);

	ASSERT_NE(head, nullptr);
	ASSERT_NE(head->next, nullptr);

	ASSERT_EQ(head->data.day, 15);
	ASSERT_EQ(head->data.month, 2);
	ASSERT_EQ(head->data.year, 2016);
	ASSERT_EQ(head->data.temp, -18);

	ASSERT_EQ(head->next->data.day, 10);
	ASSERT_EQ(head->next->data.month, 1);
	ASSERT_EQ(head->next->data.year, 2024);
	ASSERT_EQ(head->next->data.temp, 15);

	fclose(fp);
}

TEST(AddNodeTest, EmptyList) {
	Temperature data = {};
	Node* head = nullptr;
	Node* newHead = AddNode(head, data);
	ASSERT_EQ(head, nullptr);
}

TEST(AddNodeTest, AddAtBeginning) {
	Temperature data1 = { 15, 10, 2021, 18 };
	Temperature data2 = { 6, 4, 2021, -5 };

	Node* head = CreateNode(data1);
	Node* newHead = AddNode(head, data2);

	ASSERT_NE(newHead, nullptr);
	ASSERT_EQ(newHead->data.day, 6);
	ASSERT_EQ(newHead->data.month, 4);
	ASSERT_EQ(newHead->data.year, 2021);
	ASSERT_EQ(newHead->data.temp, -5);

	ASSERT_EQ(newHead->next->data.day, 15);
	ASSERT_EQ(newHead->next->data.month, 10);
	ASSERT_EQ(newHead->next->data.year, 2021);
	ASSERT_EQ(newHead->next->data.temp, 18);
	ASSERT_EQ(newHead->next->next, nullptr);
}

TEST(AddNodeTest, AddInTheMiddle) {

	Temperature data1 = { 18, 9, 2024, 8 };
	Temperature data2 = { 20, 7, 2024, 30 };
	Temperature data3 = { 29, 6, 2024, 12 };

	Node* head = CreateNode(data1);
	head = AddNode(head, data2);
	Node* newHead = AddNode(head, data3);

	ASSERT_NE(newHead, nullptr);

	ASSERT_EQ(newHead->data.day, 18);
	ASSERT_EQ(newHead->data.month, 9);
	ASSERT_EQ(newHead->data.year, 2024);
	ASSERT_EQ(newHead->data.temp, 8);

	ASSERT_EQ(newHead->next->data.day, 29);
	ASSERT_EQ(newHead->next->data.month, 6);
	ASSERT_EQ(newHead->next->data.year, 2024);
	ASSERT_EQ(newHead->next->data.temp, 12);

	ASSERT_EQ(newHead->next->next->data.day, 20);
	ASSERT_EQ(newHead->next->next->data.month, 7);
	ASSERT_EQ(newHead->next->next->data.year, 2024);
	ASSERT_EQ(newHead->next->next->data.temp, 30);

	ASSERT_EQ(newHead->next->next->next, nullptr);
}

TEST(AddNodeTest, AddAtTheEnd) {
	Temperature data1 = { 29, 6, 2024, 12 };
	Temperature data2 = { 18, 9, 2024, 8 };
	Temperature data3 = { 20, 7, 2024, 30 };

	Node* head = CreateNode(data1);
	head = AddNode(head, data2);
	Node* newHead = AddNode(head, data3);

	ASSERT_NE(newHead, nullptr);

	ASSERT_EQ(newHead->data.day, 18);
	ASSERT_EQ(newHead->data.month, 9);
	ASSERT_EQ(newHead->data.year, 2024);
	ASSERT_EQ(newHead->data.temp, 8);

	ASSERT_EQ(newHead->next->data.day, 29);
	ASSERT_EQ(newHead->next->data.month, 6);
	ASSERT_EQ(newHead->next->data.year, 2024);
	ASSERT_EQ(newHead->next->data.temp, 12);

	ASSERT_EQ(newHead->next->next->data.day, 20);
	ASSERT_EQ(newHead->next->next->data.month, 7);
	ASSERT_EQ(newHead->next->next->data.year, 2024);
	ASSERT_EQ(newHead->next->next->data.temp, 30);

	ASSERT_EQ(newHead->next->next->next, nullptr);
}

TEST(AddModeTest, SameTemperature) {
	Temperature data1 = { 30, 6, 2024, 12 };
	Temperature data2 = { 29, 6, 2024, 12 };

	Node* head = CreateNode(data1);
	Node* newHead = AddNode(head, data2);

	ASSERT_NE(newHead, nullptr);

	ASSERT_EQ(newHead->data.day, 29);
	ASSERT_EQ(newHead->data.month, 6);
	ASSERT_EQ(newHead->data.year, 2024);
	ASSERT_EQ(newHead->data.temp, 12);

	ASSERT_EQ(newHead->next->data.day, 30);
	ASSERT_EQ(newHead->next->data.month, 6);
	ASSERT_EQ(newHead->next->data.year, 2024);
	ASSERT_EQ(newHead->next->data.temp, 12);
}

TEST(FindTempTest, NotFound) {
	Temperature data1 = { 30, 6, 2024, 12 };
	Temperature data2 = { 29, 6, 2024, 12 };

	Node* head = CreateNode(data1);
	head = AddNode(head, data2);
	int findTemp = 6;
	int found = FindTemp(head, findTemp);

	ASSERT_EQ(found, 0);
}

TEST(FindTempTest, RightTemperature) {
	Temperature data1 = { 30, 6, 2024, 12 };
	Temperature data2 = { 29, 6, 2024, 12 };

	Node* head = CreateNode(data1);
	head = AddNode(head, data2);
	int findTemp = 12;
	int found = FindTemp(head, findTemp);

	ASSERT_EQ(found, 2);
}