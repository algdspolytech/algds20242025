#include "functions.h"
#include "tests.h"


int main() {
    test_avl_insert_ascending();
    test_avl_insert_random();
    test_avl_delete_leaf();
    test_avl_delete_node_with_two_children();
    test_avl_search_existing();
    test_avl_search_non_existing();
    test_avl_balance_after_insertions();
    test_avl_duplicate_insert();
    test_avl_complex_operations();

    printf("All tests passed!\n");
    return 0;
}
