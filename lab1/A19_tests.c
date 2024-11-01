#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "header_A19.h"

void utest_Standard() {
    list_t* myList = CreateList();
    AddToList(myList, "abcd");
    AddToList(myList, "bcdef");
    AddToList(myList, "cdefg");

    printf("\nBefore sorting 1:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_Numeric() {
    list_t* myList = CreateList();
    AddToList(myList, " 12");
    AddToList(myList, "12345");
    AddToList(myList, "1234");

    printf("\nBefore sorting 2:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_Numeric_Standard() {
    list_t* myList = CreateList();
    AddToList(myList, "1");
    AddToList(myList, "mmm");
    AddToList(myList, "123");

    printf("\nBefore sorting 3:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_SpecialCharacter_Numeric() {
    list_t* myList = CreateList();
    AddToList(myList, "!!!");
    AddToList(myList, "1");
    AddToList(myList, "0");

    printf("\nBefore sorting 4:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}


void utest_Numeric_mixed_Standard() {
    list_t* myList = CreateList();
    AddToList(myList, "1 2 3");
    AddToList(myList, "a 3 4 5");
    AddToList(myList, "a b c d");

    printf("\nBefore sorting 5:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_Space_Numeric() {
    list_t* myList = CreateList();
    AddToList(myList, "1      2");
    AddToList(myList, "13");
    AddToList(myList, "123");

    printf("\nBefore sorting 6:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}


void utest_SpecialCharacter_Standard() {
    list_t* myList = CreateList();
    AddToList(myList, "how are % ");
    AddToList(myList, "are");
    AddToList(myList, "how are");

    printf("\nBefore sorting 7:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_Low_Upper_case() {
    list_t* myList = CreateList();
    AddToList(myList, "ABC");
    AddToList(myList, "aaa");
    AddToList(myList, "abc");

    printf("\nBefore sorting 8:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}


void utest_Numeric_Standard_Special() {
    list_t* myList = CreateList();
    AddToList(myList, "###0123");
    AddToList(myList, "##abcd");
    AddToList(myList, "ABCD");

    printf("\nBefore sorting 9:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

void utest_different_Length() {
    list_t* myList = CreateList();
    AddToList(myList, "aaaaaaa");
    AddToList(myList, "a");
    AddToList(myList, "aaa");

    printf("\nBefore sorting 10:\n");
    PrintList(myList);

    SortList(myList);

    printf("\nAfter sorting:\n");
    PrintList(myList);

    DestroyList(myList);
}

int main() {
    utest_Standard();
    utest_Numeric();
    utest_Numeric_Standard();
    utest_SpecialCharacter_Numeric();
    utest_Numeric_mixed_Standard();
    utest_Space_Numeric();
    utest_SpecialCharacter_Standard();
    utest_Low_Upper_case();
    utest_Numeric_Standard_Special();
    utest_different_Length();
    return 0;
}
