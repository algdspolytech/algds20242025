#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "UnrolledLinkedList.h"
#include "C:\Users\nasty\source\repos\Lab_1\UnrolledLinkedList\UnrolledLinkedList.c"

TEST(AddTest, add_to_empty_no1) {
	ULList_t A;
	A.count = 0;
	A.next = NULL;
	Add(&A, 1);
	EXPECT_EQ(A.data[0], 1);
}

TEST(AddTest, add_to_full_no2) {
	int data[4] = { 1, 2, 3, 4 };
	ULList_t A = Create(4, data, NULL);
	Add(&A, 5);
	EXPECT_EQ(A.next->data[0], 5);
}

TEST(AddTest, normal_no3) {
	int data[3] = { 1, 2, 3 };
	ULList_t A = Create(3, data, NULL);
	Add(&A, 4);
	EXPECT_EQ(A.data[3], 4);
}

TEST(IndexTest, element_found_no4) {
	int dataB[1] = { 3 };
	int dataA[2] = { 1, 2 };
	ULList_t B = Create(1, dataB, NULL);
	ULList_t A = Create(2, dataA, &B);
	EXPECT_EQ(Index(&A, 3), 2);
}

TEST(IndexTest, element_not_found_no5) {
	int dataB[1] = { 3 };
	int dataA[2] = { 1, 2 };
	ULList_t B = Create(1, dataB, NULL);
	ULList_t A = Create(2, dataA, &B);
	EXPECT_EQ(Index(&A, 10), -1);
}

TEST(ElementTest, index_in_range_no6) {
	int dataB[3] = { 3, 4, 5 };
	int dataA[2] = { 1, 2 };
	ULList_t B = Create(3, dataB, NULL);
	ULList_t A = Create(2, dataA, &B);
	Element_t elem = Element(&A, 3);
	EXPECT_EQ(elem.list->data[elem.index], 4);
}

TEST(ElementTest, index_out_of_range_no7) {
	int dataB[3] = { 3, 4, 5 };
	int dataA[2] = { 1, 2 };
	ULList_t B = Create(3, dataB, NULL);
	ULList_t A = Create(2, dataA, &B);
	Element_t elem = Element(&A, 10);
	EXPECT_EQ(elem.list, (ULList_t*)NULL);
	EXPECT_EQ(elem.index, -1);
}

TEST(DeleteTest, index_in_range_no8) {
	int dataA[4] = { 1, 2, 3, 4 };
	ULList_t A = Create(4, dataA, NULL);
	Delete(&A, 1);
	int arr[3] = { 1, 3, 4 };
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(A.data[i], arr[i]);
	}
}

TEST(DeleteTest, index_out_of_range_no9) {
	int dataA[4] = { 1, 2, 3, 4 };
	ULList_t A = Create(4, dataA, NULL);
	Delete(&A, 8);
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(A.data[i], i + 1);
	}
}

TEST(ElementCountTest, normal_no10) {
	int dataB[3] = { 3, 4, 5 };
	int dataA[2] = { 1, 2 };
	ULList_t B = Create(3, dataB, NULL);
	ULList_t A = Create(2, dataA, &B);
	EXPECT_EQ(ElementCount(&A), 5);
}

TEST(ElementCountTest, empty_ullist_no11) {
	ULList_t A;
	A.count = 0;
	A.next = NULL;
	EXPECT_EQ(ElementCount(&A), 0);
}

TEST(NextTest, normal_no12) {
	int dataA[4] = { 1, 2, 3, 4 };
	ULList_t A = Create(4, dataA, NULL);
	Element_t elem = { &A, 1 };
	Element_t next = Next(elem);
	EXPECT_EQ(next.list, elem.list);
	EXPECT_EQ(next.list->data[next.index], 3);
}

TEST(NextTest, next_element_is_in_next_block_no13) {
	int dataB[3] = { 3, 4, 5 };
	int dataA[2] = { 1, 2 };
	ULList_t B = Create(3, dataB, NULL);
	ULList_t A = Create(2, dataA, &B);
	Element_t elem = { &A, 1 };
	Element_t next = Next(elem);
	EXPECT_EQ(next.list, elem.list->next);
	EXPECT_EQ(next.list->data[next.index], 3);
}

TEST(NextTest, next_element_does_not_exist_no14) {
	int dataA[3] = { 1, 2, 3 };
	ULList_t A = Create(3, dataA, NULL);
	Element_t elem = { &A, 2 };
	Element_t next = Next(elem);
	EXPECT_EQ(next.list, (ULList_t*)NULL);
	EXPECT_EQ(next.index, -1);
}