#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "functions.h"


int main() {

    test_create_node_zero_interval_return0();
    test_create_node_normal_interval_return0();
    test_insert_new_node_return0();
    test_insert_some_nodes_left_return0();
    test_insert_some_nodes_right_return0();
    test_insert_lots_nodes_return0();
    test_find_min_node_return0();
    test_find_intersections_with_intersections_return0();
    test_find_intersections_without_intersections_return0();
    test_delete_node_return0();

    printf("All tests passed!\n");

    return 0;
}