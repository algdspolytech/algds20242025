#include <check.h>
#include "bintree.h"


START_TEST(test_init_node) {
    double value = 10.5;
    Node *node = init_node(value);
    ck_assert_ptr_nonnull(node);
    ck_assert_double_eq(node->value, value);
    ck_assert_ptr_null(node->left);
    ck_assert_ptr_null(node->right);
    ck_assert_int_eq(node->min_leaf_height, 0);
    free(node);
}
END_TEST

START_TEST(test_init_tree) {
    double value = 15.0;
    Bin_Tree *tree = init_tree(value);
    ck_assert_ptr_nonnull(tree);
    ck_assert_ptr_nonnull(tree->root);
    ck_assert_double_eq(tree->root->value, value);
    ck_assert_ptr_null(tree->root->left);
    ck_assert_ptr_null(tree->root->right);
    free_tree(tree->root);
    free(tree);
}
END_TEST

START_TEST(test_add_new_node) {
    Bin_Tree *tree = init_tree(20.0);
    add_new_node(tree->root, 10.0);
    add_new_node(tree->root, 30.0);
    ck_assert_ptr_nonnull(tree->root->left);
    ck_assert_ptr_nonnull(tree->root->right);
    ck_assert_double_eq(tree->root->left->value, 10.0);
    ck_assert_double_eq(tree->root->right->value, 30.0);
    ck_assert_int_eq(tree->root->min_leaf_height, 1);
    free_tree(tree->root);
    free(tree);
}
END_TEST

START_TEST(test_calculate_min_leaf_height) {
    Bin_Tree *tree = init_tree(20.0);
    add_new_node(tree->root, 21.0);
    add_new_node(tree->root, 30.0);
    add_new_node(tree->root, 36.0);
    int height = tree->root->min_leaf_height;
    ck_assert_int_eq(height, 3);
    free_tree(tree->root);
    free(tree);
}
END_TEST

START_TEST(test_updatee_heigths) {
    Bin_Tree *tree = init_tree(10.0);
    add_new_node(tree->root, 5.0);
    add_new_node(tree->root, 15.0);
    add_new_node(tree->root, 2.0);
    updatee_heigths(tree->root);
    ck_assert_int_eq(tree->root->min_leaf_height, 1);
    free_tree(tree->root);
    free(tree);
}
END_TEST


Suite *binary_tree_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("BinaryTree");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_init_node);
    tcase_add_test(tc_core, test_init_tree);
    tcase_add_test(tc_core, test_add_new_node);
    tcase_add_test(tc_core, test_calculate_min_leaf_height);
    tcase_add_test(tc_core, test_updatee_heigths);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = binary_tree_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}