#ifndef TESTS_H
#define TESTS_H
#include "ull_lib.h"
#include <assert.h>

void runAllTests();

void insertElement_EmptyList_NewNode_no1();
void insertElement_FullNode_NewNode_no2();

void findIndexByKey_ExistingKey_returnValidVal_no3();
void findIndexByKey_NonExistingKey_returnMinus1_no4();

void findValByIndex_ValidIndex_returnValidVal_no5();
void findValByIndex_InvalidIndex_returnMinus1_no6();

void removeElement_FromBeginningOfNode_UpdatesList_no7();
void removeElement_FromEndOfNode_UpdatesList_no8();
void removeElement_FromMiddleOfNode_UpdatesList_no9();
void removeElement_FromSingleElementList_SetHeadToNull_no10();
void removeElement_FromEmptytList_PrintErrorMessage_no11();
void removeElement_InvaldIndex_PrintErrorMessage_no12();

void length_MultipleNodes_returnValidVal_no13();
void length_EmptyList_return0_no14();
void length_AfterDeletingElement_returnValidVal_no15();

void iterateList_EmptyList_returnMinus1_no16();
void iterateList_NonEmptyList_returnValidVal_no17();


#endif
