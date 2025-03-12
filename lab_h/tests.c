#include <stdio.h>
#include <assert.h>
#include "functions.h"

#include <assert.h>

void test_search_non_existent_element_avl_1() {
    Node* avl = NULL;
    avl = insertAVL(avl, 10);
    avl = insertAVL(avl, 20);
    avl = insertAVL(avl, 30);

    Node* result = search(avl, 40); 
    assert(result == NULL);

    printf("test_search_non_existent_element_avl passed.\n");
}

void test_search_existent_element_avl_2() {
    Node* avl = NULL;
    avl = insertAVL(avl, 10);
    avl = insertAVL(avl, 20);
    avl = insertAVL(avl, 30);

    assert(getBalance(avl) >= -1 && getBalance(avl) <= 1);

    Node* result = search(avl, 20);
    assert(result != NULL);
    assert(result->key == 20);

    printf("test_search_existent_element_avl passed.\n");
}


void test_delete_from_empty_tree_avl_3() {
    Node* avl = NULL;
    avl = deleteAVL(avl, 10); 
    assert(avl == NULL);

    printf("test_delete_from_empty_tree_avl passed.\n");
}

void test_insert_duplicate_value_avl_4() {
    Node* avl = NULL;
    avl = insertAVL(avl, 10);
    avl = insertAVL(avl, 10); 

    Node* result = search(avl, 10);
    assert(result != NULL && result->key == 10);

    printf("test_insert_duplicate_value_avl passed.\n");
}

void test_insert_and_search_multiple_elements_avl_5() {
    Node* avl = NULL;
    avl = insertAVL(avl, 50);
    avl = insertAVL(avl, 30);
    avl = insertAVL(avl, 70);
    avl = insertAVL(avl, 20);
    avl = insertAVL(avl, 40);
    avl = insertAVL(avl, 60);
    avl = insertAVL(avl, 80);

    assert(search(avl, 20) != NULL);
    assert(search(avl, 40) != NULL);
    assert(search(avl, 60) != NULL);
    assert(search(avl, 80) != NULL);
    assert(search(avl, 100) == NULL); 

    printf("test_insert_and_search_multiple_elements_avl passed.\n");
}

void test_delete_leaf_node_avl_6() {
    Node* avl = NULL;
    avl = insertAVL(avl, 50);
    avl = insertAVL(avl, 30);
    avl = insertAVL(avl, 70);

    avl = deleteAVL(avl, 30); 
    assert(search(avl, 30) == NULL);
    assert(search(avl, 50) != NULL);
    assert(search(avl, 70) != NULL);

    printf("test_delete_leaf_node_avl passed.\n");
}

void test_delete_node_with_one_child_avl_7() {
    Node* avl = NULL;
    avl = insertAVL(avl, 50);
    avl = insertAVL(avl, 30);
    avl = insertAVL(avl, 70);
    avl = insertAVL(avl, 60);

    avl = deleteAVL(avl, 70);
    assert(search(avl, 70) == NULL);
    assert(search(avl, 60) != NULL);

    printf("test_delete_node_with_one_child_avl passed.\n");
}

void test_delete_node_with_two_children_avl_8() {
    Node* avl = NULL;
    avl = insertAVL(avl, 50);
    avl = insertAVL(avl, 30);
    avl = insertAVL(avl, 70);
    avl = insertAVL(avl, 60);
    avl = insertAVL(avl, 80);

    avl = deleteAVL(avl, 70);
    assert(search(avl, 70) == NULL);
    assert(search(avl, 60) != NULL);
    assert(search(avl, 80) != NULL);

    printf("test_delete_node_with_two_children_avl passed.\n");
}

void test_avl_balance_after_insertions_9() {
    Node* avl = NULL;
    avl = insertAVL(avl, 10);
    avl = insertAVL(avl, 20);
    avl = insertAVL(avl, 30); 

    assert(getBalance(avl) >= -1 && getBalance(avl) <= 1);
    assert(search(avl, 10) != NULL);
    assert(search(avl, 20) != NULL);
    assert(search(avl, 30) != NULL);

    printf("test_avl_balance_after_insertions passed.\n");
}

void test_avl_balance_after_deletions_10() {
    Node* avl = NULL;
    avl = insertAVL(avl, 50);
    avl = insertAVL(avl, 30);
    avl = insertAVL(avl, 70);
    avl = insertAVL(avl, 20);
    avl = insertAVL(avl, 40);
    avl = insertAVL(avl, 60);
    avl = insertAVL(avl, 80);

    avl = deleteAVL(avl, 20);
    avl = deleteAVL(avl, 40); 

    assert(getBalance(avl) >= -1 && getBalance(avl) <= 1); 
    assert(search(avl, 20) == NULL);
    assert(search(avl, 40) == NULL);

    printf("test_avl_balance_after_deletions passed.\n");
}

int main() {
    test_search_non_existent_element_avl_1();
    test_search_existent_element_avl_2();
    test_delete_from_empty_tree_avl_3();
    test_insert_duplicate_value_avl_4();
    test_insert_and_search_multiple_elements_avl_5();
    test_delete_leaf_node_avl_6();
    test_delete_node_with_one_child_avl_7();
    test_delete_node_with_two_children_avl_8();
    test_avl_balance_after_insertions_9();
    test_avl_balance_after_deletions_10();
   


    printf("All AVL tests passed!\n");
    return 0;
}