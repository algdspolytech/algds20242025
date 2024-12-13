//
//  main.c
//  LAB_F
//
//  Created by Фёдор Филь on 11.12.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "tests.h"


int main(void) {
    Node* root = NULL;
    int intervals[][2] = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}};

    for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); ++i) {
        root = insert(root, intervals[i][0], intervals[i][1]);
    }

    int intervalToFind[] = {16, 21};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    printf("Пересекающиеся интервалы:\n");
    for (int i = 0; i < count; ++i) {
        printf("[%d, %d]\n", result[i]->low, result[i]->high);
    }

    // Удаление интервала
    int deleteInterval[] = {10, 30};
    root = deleteNode(root, deleteInterval[0]);

    printf("\nПосле удаления [%d, %d]: \n", deleteInterval[0], deleteInterval[1]);
    count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    printf("Пересекающиеся интервалы:\n");
    for (int i = 0; i < count; ++i) {
        printf("[%d, %d]\n", result[i]->low, result[i]->high);
    }
    
    test_insert_and_find_no1();
    test_delete_and_find_no2();
    test_empty_tree_no3();
    test_single_element_tree_no4();
    test_no_overlap_no5();
    test_exact_match_no6();
    test_multiple_overlaps_no7();
    test_left_edge_case_no8();
    test_right_edge_case_no9();
    test_boundary_cases_no10();
    
    printf("Все тесты пройдены успешно!\n");
    return 0;

    return 0;
}

