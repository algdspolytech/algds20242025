#ifndef TESTS_H
#define TESTS_H
#include "lib.h"
#include <assert.h>

void runAllTests();

void compareDates_FirstBigger_returnMinus1_no1();
void compareDates_FirstSmaller_return1_no2();
void compareDates_EqualDates_return0_no3();

void insertSorted_AddToEmpty_ValidVal_no4();
void insertSorted_InsertTheSmallestValue_NewNodeInTheBeginning_no5();
void insertSorted_InsertMiddleValue_NewNodeInTheModdle_no6();
void insertSorted_InsertTheBiggestValue_NewNodeInTheEnd_no7();

void searchTemperature_EmptyList_returnNULL_no8();
void searchTemperature_NoSuchTemperature_returnNULL_no9();
void searchTemperature_OneSuchTemperatureExist_returnValidNode_no10();
void searchTemperature_TwoSuchTemperaturesExist_returnValidVal_no11();

#endif