#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "HashTable.c"


TEST(HashFuncTest, return_correct_hash_func_value_no1) {
	char* c = "a";
	int index = HashFunc(c, 7);
	EXPECT_EQ(index, 6);
}

TEST(CreateTest, create_empty_hash_table_no2) {
	HashTable_t t = CreateTable(3);
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(t.data[i], nullptr);
	}
}

TEST(QuadraticProbingTest, return_correct_value_no3) {
	int index = QuadraticProbing(1, 7, 3);
	EXPECT_EQ(index, 3);
}

TEST(FindTest, element_is_in_hash_table_return_index_no4) {
	HashTable_t t = CreateTable(7);
	t.data[6] = "a";
	int index = Find("a", t);
	EXPECT_EQ(index, 6);
}

TEST(FindTest, multiple_elements_with_same_value_no5) {
	HashTable_t t = CreateTable(7);
	t.data[6] = "a";
	t.data[7] = "a";
	t.data[3] = "a";
	int index = Find("a", t);
	EXPECT_EQ(index, 6);
}

TEST(FindTest, element_not_in_hash_table_return_minus_one_no6) {
	HashTable_t t = CreateTable(7);
	t.data[6] = "a";
	int index = Find("b", t);
	EXPECT_EQ(index, -1);
}

TEST(InsertTest, first_try_successful_no7) {
	HashTable_t t = CreateTable(7);
	Insert("a", t);
	EXPECT_EQ(t.data[6][0], 'a');
}

TEST(InsertTest, first_try_place_already_occupied_no8) {
	HashTable_t t = CreateTable(7);
	t.data[6] = "a";
	Insert("a", t);
	EXPECT_EQ(t.data[0][0], 'a');
}

TEST(InsertTest, no_space_no9) {
	HashTable_t t = CreateTable(2);
	t.data[0] = "b";
	t.data[1] = "a";
	Insert("c", t);
	EXPECT_EQ(t.data[0][0], 'b');
	EXPECT_EQ(t.data[1][0], 'a');
}

TEST(DeleteTest, element_in_hash_table_no10) {
	HashTable_t t = CreateTable(7);
	Insert("a", t);
	Delete("a", t);
	EXPECT_EQ(t.data[6], nullptr);
}

TEST(DeleteTest, multiple_elements_with_same_value_no11) {
	HashTable_t t = CreateTable(7);
	Insert("a", t);
	Insert("a", t);
	Delete("a", t);
	EXPECT_EQ(t.data[6], nullptr);
	EXPECT_EQ(t.data[0][0], 'a');
}

TEST(DeleteTest, element_not_in_hash_table_no12) {
	HashTable_t t = CreateTable(2);
	Insert("a", t);
	Delete("b", t);
	EXPECT_EQ(t.data[0], nullptr);
	EXPECT_EQ(t.data[1][0], 'a');
}