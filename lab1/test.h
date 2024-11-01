#ifndef TEST_H
#define TEST_H
#include "sort.h"
#include <assert.h>

void runAllTests();

void compareWords_Equal_return0();
void compareWords_LeftBigger_returnMinus1();
void compareWords_LeftLowwer_return1();
void compareWords_LeftEmpty_returnMinus1();

void push_Standart_CorretctInsert();

void pop_Standart_InsertHelloWorld();
void pop_ListWithOnlyHeader_InsertTerminator();

void insertAfter_Standart_CorrectNext();
void insertAfter_Standart_CorrectPrevious();

void merge_Standart_SortedFirstList();
void merge_LeftEmpty_SortedFirstList();

#endif