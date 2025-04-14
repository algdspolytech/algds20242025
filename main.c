#include "tree.h"
#include <stdio.h>
Node* build_test_tree_1_empty();
Node* build_test_tree_2_single_node();
Node* build_test_tree_3_root_two_leaves();
Node* build_test_tree_4_left_skewed();
Node* build_test_tree_5_right_skewed();
Node* build_test_tree_6_full_binary();
Node* build_test_tree_7_incomplete_last_level();
Node* build_test_tree_8_zigzag();
Node* build_test_tree_9_internal_one_child();
Node* build_test_tree_10_complex();
void run_test(int test_num, Node* (*build_func)(), const char* description);


int main() {
    printf("test...\n");

    run_test(1, build_test_tree_1_empty, "empty tree");
    run_test(2, build_test_tree_2_single_node, "tree 1 uzel");
    run_test(3, build_test_tree_3_root_two_leaves, "koren and 2 list");
    run_test(4, build_test_tree_4_left_skewed, "left tree");
    run_test(5, build_test_tree_5_right_skewed, "right tree");
    run_test(6, build_test_tree_6_full_binary, "full 0 1 tree");
    run_test(7, build_test_tree_7_incomplete_last_level, "not full end level");
    run_test(8, build_test_tree_8_zigzag, "zig zag tree");
    run_test(9, build_test_tree_9_internal_one_child, "uzl with one potomok");
    run_test(10, build_test_tree_10_complex, "hard tree");

    printf("\nAll tests end.\n");

    return 0;
}