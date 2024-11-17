#include "pch.h"
#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>
#define TS "TestString"

extern "C" {
#include "..\XOR_list\xorlist.h"
}


TEST(XORlistTest, StrEqual_EqualStrings_ReturnOne) 
{ 
	ASSERT_EQ(1, StrEqual(TS, TS));
}

TEST(XORlistTest, StrEqual_DiffStr_ReturnZero) 
{ 
	ASSERT_EQ(0, StrEqual(TS, "abc"));
}

TEST(XORlistTest, StrEqual_NullStr_ReturnZero) 
{ 
	ASSERT_EQ(0, StrEqual(TS, NULL));
}

TEST(XORlistTest, StrLength_Normal_ReturnOne)
{ 
	ASSERT_EQ(10, StrLength(TS));
}

TEST(XORlistTest, StrLength_NULL_ReturnZero)
{
	ASSERT_EQ(0, StrLength(NULL));
}

/*
ListElem(list_t* list, int num); 
ListCreate(char* string)
ListAdd(list_t* list, char* string); 
FindElem(list_t* list, char* string, int* pindex); 
DeleteElem(list_t* list, char* string, int delindex); 
*/


TEST(XORlistTest, ListCreate_ValidVal_ReturnValidVal)
{
	list_t* list = ListCreate(TS);
	char* string = list ->Plist->str;
	EXPECT_TRUE(StrEqual(string,  TS) && list->size == 1);
}

TEST(XORlistTest, ListCreate_NULL_ReturnNULL)
{
	EXPECT_EQ(NULL, ListCreate(NULL));
}

TEST(XORlistTest, ListAdd_NULL_ReturnNULL)
{
	list_t* list = ListCreate("1");
	ListAdd(list, NULL);
	EXPECT_TRUE(StrEqual(list->Plist->str, "1") && (list->Plist-> xor == (elem_t*)0xcdcdcdcdcdcdcdcd) && list->size == 1);
}

TEST(XORlistTest, ListAdd_ValidVal_ReturnValidVal)
{
	list_t* list = ListCreate("1");
	ListAdd(list, "2");
	EXPECT_TRUE(StrEqual(list->Plist->str, "1") && StrEqual(list->Plist-> xor ->str, "2") && list->size == 2);
}

TEST(XORlistTest, ListElem_ValidVal_ReturnValidVal)
{
	list_t* list = ListCreate("1");
	ListAdd(list, "2");
	ListAdd(list, "3");
	EXPECT_TRUE(StrEqual(ListElem(list, 0)->str, "1") && StrEqual(ListElem(list, 1)->str, "2") && StrEqual(ListElem(list, 2)->str, "3"));
}

TEST(XORlistTest, ListElem_InvalidVal_ReturnNULL)
{
	list_t* list = ListCreate(TS);
	ListAdd(list, TS);
	ListAdd(list, TS);
	EXPECT_TRUE(ListElem(list, -1) == NULL && ListElem(list, 3) == NULL);
}

TEST(XORlistTest, FindElem_ValidVal_ReturnValidVal)
{
	list_t* list = ListCreate("1");
	ListAdd(list, "2");
	ListAdd(list, "3");
	int pindex = 0;
	EXPECT_TRUE(StrEqual(FindElem(list,"3",&pindex)->str,"3") && pindex == 2);
}

TEST(XORlistTest, FindElem_NoStringInList_ReturnNULL)
{
	list_t* list = ListCreate(TS);
	ListAdd(list, TS);
	ListAdd(list, TS);
	int pindex = -1;
	EXPECT_TRUE(FindElem(list, "3", &pindex) == NULL && pindex == -1);
}

TEST(XORlistTest, DeleteElem_ValidString_Return)
{
	list_t* list = ListCreate("1");
	ListAdd(list, "2");
	ListAdd(list, "3");
	DeleteElem(list, "3", NULL);
	EXPECT_TRUE(ListElem(list, 1)-> xor == ListElem(list, 0) && ListElem(list, 1)->xor == ListElem(list, 0) && StrEqual(ListElem(list, 0)->str, "1") && StrEqual(ListElem(list, 1)->str, "2"));
}

TEST(XORlistTest, DeleteElem_ValidIndex_Return)
{
	list_t* list = ListCreate("1");
	ListAdd(list, "2");
	ListAdd(list, "3");
	DeleteElem(list, NULL, 1);
	EXPECT_TRUE(ListElem(list, 1)-> xor == ListElem(list, 0) && ListElem(list, 1)-> xor == ListElem(list, 0) && StrEqual(ListElem(list, 0)->str, "1") && StrEqual(ListElem(list, 1)->str, "3"));
}

TEST(XORlistTest, DeleteElem_NULL_Return)
{
	list_t* list = ListCreate("1");
	ListAdd(list, "2");
	ListAdd(list, "3");
	DeleteElem(list, NULL, NULL);
	EXPECT_TRUE(StrEqual(ListElem(list, 0)->str, "1") && StrEqual(ListElem(list, 1)->str, "2") && StrEqual(ListElem(list, 2)->str, "3") && list->size == 3);
}


