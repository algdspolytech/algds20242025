#include "tests.h"

void runAllTests()
{
    compareDates_FirstBigger_returnMinus1_no1();
    compareDates_FirstSmaller_return1_no2();
    compareDates_EqualDates_return0_no3();

    insertSorted_AddToEmpty_ValidVal_no4();
    insertSorted_InsertTheSmallestValue_NewNodeInTheBeginning_no5();
    insertSorted_InsertMiddleValue_NewNodeInTheModdle_no6();
    insertSorted_InsertTheBiggestValue_NewNodeInTheEnd_no7();

    searchTemperature_EmptyList_returnNULL_no8();
    searchTemperature_NoSuchTemperature_returnNULL_no9();
    searchTemperature_OneSuchTemperatureExist_returnValidNode_no10();
    searchTemperature_TwoSuchTemperaturesExist_returnValidVal_no11();

    printf("Tests ran successfully!\n");

}

void compareDates_FirstBigger_returnMinus1_no1()
{
    int day1 = 1;
    int month1 = 1;
    int year1 = 2;
    int day2 = 1;
    int month2 = 1;
    int year2 = 1;
    assert(compareDates(day1, month1, year1, day2, month2, year2) == -1);
}

void compareDates_FirstSmaller_return1_no2()
{
    int day1 = 1;
    int month1 = 1;
    int year1 = 1;
    int day2 = 1;
    int month2 = 2;
    int year2 = 1;
    assert(compareDates(day1, month1, year1, day2, month2, year2) == 1);
}

void compareDates_EqualDates_return0_no3()
{
    int day1 = 1;
    int month1 = 1;
    int year1 = 1;
    int day2 = 1;
    int month2 = 1;
    int year2 = 1;
    assert(compareDates(day1, month1, year1, day2, month2, year2) == 0);
}

void insertSorted_AddToEmpty_ValidVal_no4()
{
    Node* head = NULL;
    int day = 1;
    int month = 1;
    int year = 1;
    int temperature = 1;
    head = insertSorted(head, day, month, year, temperature);
    assert(head->day == day && head->month == month && head->year == year && head->next == NULL);
}


void insertSorted_InsertTheSmallestValue_NewNodeInTheBeginning_no5()
{
    int day = 1;
    int month = 1;
    int year = 1;
    int temperature = 1;
    Node* A = (Node*)malloc(sizeof(Node));
    Node* B = (Node*)malloc(sizeof(Node));
    A->day = 1;
    A->month = 1;
    A->year = 1;
    A->temperature = 2;
    A->next = B; 
    B->day = 1;
    B->month = 1;
    B->year = 1;
    B->temperature = 3;
    B->next = NULL; 
    Node* head = insertSorted(A, day, month, year, temperature);
    assert(head->day == day && head->month == month && head->year == year && head->next == A);
}

void insertSorted_InsertMiddleValue_NewNodeInTheModdle_no6()
{
    int day = 1;
    int month = 1;
    int year = 1;
    int temperature = 2;
    Node* A = (Node*)malloc(sizeof(Node));
    Node* B = (Node*)malloc(sizeof(Node));
    A->day = 1;
    A->month = 1;
    A->year = 1;
    A->temperature = 1;
    A->next = B; 
    B->day = 1;
    B->month = 1;
    B->year = 1;
    B->temperature = 3;
    B->next = NULL; 
    Node* head = insertSorted(A, day, month, year, temperature);
    Node* C = head->next;
    assert(C->day == day && C->month == month && C->year == year && C->next == B);
}

void insertSorted_InsertTheBiggestValue_NewNodeInTheEnd_no7()
{
    int day = 1;
    int month = 1;
    int year = 1;
    int temperature = 3;
    Node* A = (Node*)malloc(sizeof(Node));
    Node* B = (Node*)malloc(sizeof(Node));
    A->day = 1;
    A->month = 1;
    A->year = 1;
    A->temperature = 1;
    A->next = B; 
    B->day = 1;
    B->month = 1;
    B->year = 1;
    B->temperature = 2;
    B->next = NULL; 
    Node* head = insertSorted(A, day, month, year, temperature);
    Node* C = head->next->next;
    assert(C->day == day && C->month == month && C->year == year && C->next == NULL && B->next == C);
}

void searchTemperature_EmptyList_returnNULL_no8()
{
    Node* head = NULL;
    Node* result = NULL;
    int temperature = 1;
    result = searchTemperature(head, temperature);
    assert(result == NULL);
}

void searchTemperature_NoSuchTemperature_returnNULL_no9()
{
    Node* A = (Node*)malloc(sizeof(Node));
    Node* B = (Node*)malloc(sizeof(Node));
    A->day = 1;
    A->month = 1;
    A->year = 1;
    A->temperature = 1;
    A->next = B; 
    B->day = 1;
    B->month = 1;
    B->year = 1;
    B->temperature = 2;
    B->next = NULL; 
    Node* result = NULL;
    int temperature = 3;
    result = searchTemperature(A, temperature);
    assert(result == NULL);
}

void searchTemperature_OneSuchTemperatureExist_returnValidNode_no10()
{
    Node* A = (Node*)malloc(sizeof(Node));
    Node* B = (Node*)malloc(sizeof(Node));
    A->day = 1;
    A->month = 1;
    A->year = 1;
    A->temperature = 1;
    A->next = B; 
    B->day = 1;
    B->month = 1;
    B->year = 1;
    B->temperature = 2;
    B->next = NULL; 
    Node* result = NULL;
    int temperature = 2;
    result = searchTemperature(A, temperature);
    assert(result->next == B->next && result->day == B->day && result->month == B->month && result->year == B->year);
}

void searchTemperature_TwoSuchTemperaturesExist_returnValidVal_no11()
{
    Node* A = (Node*)malloc(sizeof(Node));
    Node* B = (Node*)malloc(sizeof(Node));
    A->day = 1;
    A->month = 1;
    A->year = 1;
    A->temperature = 1;
    A->next = B; 
    B->day = 1;
    B->month = 1;
    B->year = 1;
    B->temperature = 1;
    B->next = NULL; 
    Node* result = NULL;
    int temperature = 1;
    result = searchTemperature(A, temperature);
    assert((result->day == A->day && result->month == A->month && result->year == A->year) && (result->next->day == B->day && result->next->month == B->month && result->next->year == B->year));
}