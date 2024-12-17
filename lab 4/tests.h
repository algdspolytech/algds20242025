#ifndef TESTS_H
#define TESTS_H
#include "lib.h"
#include <assert.h>

void createNode_init_nodeCreated_no1();

void insert_emptyTree_treeWithOneElem_no2();

void insert_oneElement_returnVaildVal_no3();

void insert_multipleElements_returnValidVal_no4();

void printInOrder_printing_noErrors_no5();

void freeTree_freeing_noErrors_no6();

void insert_duplicates_returnValidVal_no7();
 
void insert_rightBranch_returnValidVal_no8();

void insert_leftBranch_retuenValidVal_no9();

void free_nodeWithData_returnValidVal_no10();

void runAllTests();

#endif