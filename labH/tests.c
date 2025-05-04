#include <check.h>
#include "treap.h"  

Node* test_root = NULL;

void setup(void) {
    test_root = NULL;
    test_root = insert(test_root, 50, 10);
    test_root = insert(test_root, 30, 5);
    test_root = insert(test_root, 70, 20);
}

void teardown(void) {
    free_tree(test_root);
    test_root = NULL;
}


int is_treap_valid(Node* root) {
    if (!root) return 1;
    int valid = 1;
    if (root->left) {
        valid &= (root->left->key <= root->key);
        valid &= (root->left->priority <= root->priority);
    }
    if (root->right) {
        valid &= (root->right->key >= root->key);
        valid &= (root->right->priority <= root->priority);
    }
    return valid && is_treap_valid(root->left) && is_treap_valid(root->right);
}

// Тест 1: Вставка одного элемента
START_TEST(test_insert_single) {
    Node* root = NULL;
    root = insert(root, 42, 100);
    ck_assert_ptr_nonnull(root);
    ck_assert_int_eq(root->key, 42);
    ck_assert_int_eq(root->priority, 100);
    free_tree(root);
}
END_TEST

// Тест 2: Проверка свойства Treap после вставки
START_TEST(test_treap_property_after_insert) {
    ck_assert_int_eq(is_treap_valid(test_root), 1);
}
END_TEST

// Тест 3: Удаление существующего элемента
START_TEST(test_delete_existing) {
    test_root = remove(test_root, 30);
    ck_assert_ptr_null(test_root->left); 
    ck_assert_int_eq(is_treap_valid(test_root), 1);
}
END_TEST

// Тест 4: Удаление несуществующего элемента
START_TEST(test_delete_non_existing) {
    Node* original = test_root;
    test_root = remove(test_root, 999);
    ck_assert_ptr_eq(test_root, original); 
}
END_TEST

// Тест 5: Расщепление по существующему ключу
START_TEST(test_split_valid_key) {
    Node *left = NULL, *right = NULL;
    split(test_root, 50, &left, &right);
    ck_assert_ptr_nonnull(left);
    ck_assert_ptr_nonnull(right);
    ck_assert_int_eq(left->key, 50);
    ck_assert_int_eq(right->key, 70);
    free_tree(left);
    free_tree(right);
}
END_TEST

// Тест 6: Слияние двух деревьев
START_TEST(test_merge_trees) {
    Node *left = NULL, *right = NULL;
    split(test_root, 50, &left, &right);
    Node* merged = merge(left, right);
    ck_assert_int_eq(is_treap_valid(merged), 1);
    free_tree(merged);
}
END_TEST

// Тест 7: Проверка in-order обхода
START_TEST(test_inorder_traversal) {
    int expected[] = {30, 50, 70};
    int index = 0;
    Node* current = test_root;
    ck_assert_int_eq(test_root->key, 50);
    ck_assert_int_eq(test_root->left->key, 30);
    ck_assert_int_eq(test_root->right->key, 70);
}
END_TEST

// Тест 8: Расщепление по ключу больше всех элементов
START_TEST(test_split_at_max_key) {
    Node *left = NULL, *right = NULL;
    split(test_root, 100, &left, &right);
    ck_assert_ptr_nonnull(left);
    ck_assert_ptr_null(right);
    free_tree(left);
}
END_TEST

// Тест 9: Слияние с пустым деревом
START_TEST(test_merge_with_empty) {
    Node* empty = NULL;
    Node* merged = merge(test_root, empty);
    ck_assert_ptr_eq(merged, test_root);
    merged = merge(empty, test_root);
    ck_assert_ptr_eq(merged, test_root);
}
END_TEST

// Тест 10
START_TEST(test_complex_operations) {
    test_root = insert(test_root, 20, 2);
    test_root = insert(test_root, 60, 15);
    test_root = remove(test_root, 30);
    
    Node *left = NULL, *right = NULL;
    split(test_root, 50, &left, &right);
    ck_assert_int_eq(left->key, 50);
    ck_assert_int_eq(right->key, 70);
    
    Node* merged = merge(left, right);
    ck_assert_int_eq(is_treap_valid(merged), 1);
    free_tree(merged);
}
END_TEST

Suite* treap_suite(void) {
    Suite* s = suite_create("Treap");
    TCase* tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_insert_single);
    tcase_add_test(tc_core, test_treap_property_after_insert);
    tcase_add_test(tc_core, test_delete_existing);
    tcase_add_test(tc_core, test_delete_non_existing);
    tcase_add_test(tc_core, test_split_valid_key);
    tcase_add_test(tc_core, test_merge_trees);
    tcase_add_test(tc_core, test_inorder_traversal);
    tcase_add_test(tc_core, test_split_at_max_key);
    tcase_add_test(tc_core, test_merge_with_empty);
    tcase_add_test(tc_core, test_complex_operations);
    
    tcase_set_timeout(tc_core, 0);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite* s = treap_suite();
    SRunner* sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}