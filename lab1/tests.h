#ifndef TESTS_H
#define TESTS_H
#include "lib.h"
#include <assert.h>

void test_newNode_ValidValue_returnValidVal_no1();
void test_createRBTree_EmptyTree_returnValidVal_no2();
void test_insert_SingleNode_TreeRootSet_no3();
void test_insert_MultipleNodes_TreeStructureValid_no4();
void test_search_ExistingElement_returnValidNode_no5();
void test_search_NonExistingElement_returnNull_no6();
void test_insert_DuplicateElement_TreeStructureUnchanged_no7();
void test_fixViolation_ColorsAdjustedAfterInsert_no8();
void test_leftRotate_ValidLeftRotation_no9();
void test_rightRotate_ValidRightRotation_no10();
void test_search_EmptyTree_returnNull_no11();

#endif