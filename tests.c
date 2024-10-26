#include "tests.h"

void runAllTests() {

    insertElement_EmptyList_NewNode_no1();
    insertElement_FullNode_NewNode_no2();

    findIndexByKey_ExistingKey_returnValidVal_no3();
    findIndexByKey_NonExistingKey_returnMinus1_no4();

    findValByIndex_ValidIndex_returnValidVal_no5();
    findValByIndex_InvalidIndex_returnMinus1_no6();

    removeElement_FromBeginningOfNode_UpdatesList_no7();
    removeElement_FromEndOfNode_UpdatesList_no8();
    removeElement_FromMiddleOfNode_UpdatesList_no9();
    removeElement_FromSingleElementList_SetHeadToNull_no10();
    removeElement_FromEmptytList_PrintErrorMessage_no11();
    removeElement_InvaldIndex_PrintErrorMessage_no12();

    length_MultipleNodes_returnValidVal_no13();
    length_EmptyList_return0_no14();
    length_AfterDeletingElement_returnValidVal_no15();

    iterateList_EmptyList_returnMinus1_no16();
    iterateList_NonEmptyList_returnValidVal_no17();

    printf("\nTests ran successfully!\n");
}


void insertElement_EmptyList_NewNode_no1() {
    ull* list = new_unrolled_list();
    insertElement_unrolled_list(list, 1);

    assert(list->head != NULL && list->head->elements[0] == 1 && list->head->next == NULL && list->head->numElements == 1);
    delete_unrolled_list(list);
}

void insertElement_FullNode_NewNode_no2() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 1;
    list->head->elements[2] = 1; list->head->elements[3] = 1;
    list->head->numElements = 4;
    insertElement_unrolled_list(list, 2);
    assert(list->head->next->elements[0] == 2 && list->head->next->numElements == 1);
    delete_unrolled_list(list);
}

void findIndexByKey_ExistingKey_returnValidVal_no3() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    list->head->next = new_node();
    list->head->next->elements[0] = 5; list->head->next->elements[1] = 6;
    list->head->next->numElements = 2;
    
    assert(findIndexByKey_unrolled_list(list, 1) == 0 && findIndexByKey_unrolled_list(list, 4) == 3 && findIndexByKey_unrolled_list(list, 6) == 5);
    delete_unrolled_list(list);
}

void findIndexByKey_NonExistingKey_returnMinus1_no4() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    list->head->next = new_node();
    list->head->next->elements[0] = 5; list->head->next->elements[1] = 6;
    list->head->next->numElements = 2;

    printf("findIndexByKey_NonExistingKey_returnMinus1_no4():");
    assert(findIndexByKey_unrolled_list(list, 11) == -1);
    delete_unrolled_list(list);
}

void findValByIndex_ValidIndex_returnValidVal_no5() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    list->head->next = new_node();
    list->head->next->elements[0] = 5; list->head->next->elements[1] = 6;
    list->head->next->numElements = 2;
    
    assert(findValByIndex_unrolled_list(list, 0) == 1 && findValByIndex_unrolled_list(list, 5) == 6);
    delete_unrolled_list(list);
}

void findValByIndex_InvalidIndex_returnMinus1_no6() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    list->head->next = new_node();
    list->head->next->elements[0] = 5; list->head->next->elements[1] = 6;
    list->head->next->numElements = 2;

    printf("\nfindValByIndex_InvalidIndex_returnMinus1_no6():");
    
    assert(findValByIndex_unrolled_list(list, 8) == -1);
}

void removeElement_FromBeginningOfNode_UpdatesList_no7() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    removeElement_unrolled_list(list, 0);
    
    assert(list->head->elements[0] != 1 && list->head->numElements == 3);
    
    delete_unrolled_list(list);
}

void removeElement_FromEndOfNode_UpdatesList_no8() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    removeElement_unrolled_list(list, 3);
   
    assert(list->head->numElements == 3);

    delete_unrolled_list(list);
}

void removeElement_FromMiddleOfNode_UpdatesList_no9() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    removeElement_unrolled_list(list, 2);

    assert(list->head->elements[2] != 3 && list->head->numElements == 3);
    
    delete_unrolled_list(list);
}

void removeElement_FromSingleElementList_SetHeadToNull_no10() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1;
    list->head->numElements = 1;
    removeElement_unrolled_list(list, 0);

    assert(list->head == NULL);
    
    delete_unrolled_list(list);
}

void removeElement_FromEmptytList_PrintErrorMessage_no11() {
    ull* list = new_unrolled_list();
   
    printf("\nremoveElement_FromEmptytList_PrintErrorMessage_no11():");
    
    removeElement_unrolled_list(list, 0);

    delete_unrolled_list(list);
}

void removeElement_InvaldIndex_PrintErrorMessage_no12() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;

    printf("\nremoveElement_InvaldIndex_PrintErrorMessage_no12():");
    removeElement_unrolled_list(list, 6);
    delete_unrolled_list(list);
}

void length_MultipleNodes_returnValidVal_no13() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    list->head->next = new_node();
    list->head->next->elements[0] = 5; list->head->next->elements[1] = 6;
    list->head->next->numElements = 2;

    assert(length_unrolled_list(list) == 6);
    delete_unrolled_list(list);
}

void length_EmptyList_return0_no14() {
    ull* list = new_unrolled_list();
    assert(length_unrolled_list(list) == 0);
    delete_unrolled_list(list);
}

void length_AfterDeletingElement_returnValidVal_no15() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;
    removeElement_unrolled_list(list, 0);

    assert(length_unrolled_list(list) == list->head->numElements);
}

void iterateList_EmptyList_returnMinus1_no16() {
    ull* list = new_unrolled_list();
    
    assert(iterate_unrolled_list(list, 1) == -1);
}

void iterateList_NonEmptyList_returnValidVal_no17() {
    ull* list = new_unrolled_list();
    list->head = new_node();
    list->head->elements[0] = 1; list->head->elements[1] = 2;
    list->head->elements[2] = 3; list->head->elements[3] = 4;
    list->head->numElements = 4;

    assert(iterate_unrolled_list(list, 1) == 3);
    delete_unrolled_list(list);
}
