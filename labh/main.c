//
//  main.c
//  LabH
//
//  Created by Фёдор Филь on 22.03.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcs.h"
#include "tests.h"


int main(void) {
    Node* root = NULL;
    
    root = insert(root, 5, 10);
    root = insert(root, 7, 20);
    root = insert(root, 12, 30);
    root = insert(root, 15, 40);
    

    printf("Сумма на интервале [6, 13]: %ld\n", rangeSum(root, 6, 13));
    printf("Сумма на интервале [4, 16]: %ld\n", rangeSum(root, 4, 16));
    test_newNode_key_value_no1();
    test_newNode_left_right_null_no2();
    test_newNode_negative_values_no3();
    test_insert_first_element_no4();
    test_insert_left_child_no5();
    test_insert_right_child_no6();
    test_rangeSum_empty_tree_no7();
    test_rangeSum_single_node_inside_range_no8();
    test_rangeSum_multiple_nodes_inside_range_no9();
    test_rangeSum_out_of_range_no10();
    puts("Все тесты пройдены успешно!");
    
    return 0;
}
