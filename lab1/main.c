#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"
#include "tests.h"
#include "funcs.h"

#pragma warning(disable : 4996)

int main() {
    setlocale(LC_ALL, "Rus");
    Node* root = NULL;
    int n, k;

    printf("Введите количество элементов в дереве: ");
    scanf("%d", &n);

    int* elements = (int*)malloc(n * sizeof(int));

    printf("Введите %d элементов: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
        root = insert(root, elements[i]);
    }

    printf("Введите K: ");
    scanf("%d", &k);
    n = sizeof(elements) / sizeof(elements[0]);

    processKthSmallest(root, k);

    testСreateNode_no1();
    testInsert_no2();
    testFindKthSmallestBasic_no3();
    testFindKthSmallestEdge_no4();
    testFindKthSmallestOutOfBounds_no5();
    testFindKthSmallestSingleElement_no6();
    testFindKthSmallestTwoElements_no7();
    testFindKthSmallestLargeTree_no8();
    testFindKthSmallestRepeatedValues_no9();
    testFindKthSmallestRightSkewedTree_no10();


    printf("Все тесты пройдены успешно!\n");
    return 0;
}