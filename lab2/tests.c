#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "struct.h"
#include "funcs.h"

Node* root = NULL;

void Test_Inserting_an_element_no1() {
        root = insert(root, 10);
        assert(root->key == 10);
}

void Test_Inserting_another_element_no2() {
    root = insert(root, 20);
    assert(root->key == 20);
}

void Test_Finding_an_existing_element_no3() {
    root = search(root, 10);
    assert(root->key == 10);
}

void Test_Find_the_missing_element_with_remaining_no4() {
    root = search(root, 30);
    assert(root->key == 20);
}

void Test_Delete_elemen10_no5() {
    root = delete(root, 10);
    assert(root->key != 10);
}

void Test_Delete_elemen20_no6() {
    root = delete(root, 20);
    assert(root == NULL);
}

void Test_Inserting_multiple_elements_and_deleting_the_root_no7() {
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 60);
    root = delete(root, 50);
    assert(root->key != 50);
}

void Test_Checking_that_search_works_correctly_after_deletion_no8() {
    root = search(root, 70);
    assert(root->key == 70);
}

void Test_Attempt_to_delete_nonexistent_element_no9() {
    root = delete(root, 100);
    assert(root != NULL);
}

void Test_Remove_all_elements_and_check_for_empty_tree_no10() {
    root = delete(root, 30);
    root = delete(root, 70);
    root = delete(root, 60);
    assert(root == NULL); 
}
