#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"
#include "funcs.h"
#include "tests.h"

int main() {

    setlocale(LC_ALL, "Rus");

    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Обход дерева (inorder): ");
    inorder(root);
    printf("\n");

    root = search(root, 30);
    printf("После поиска 30 (корень: %d)\n", root->key);

    root = delete(root, 30);
    printf("После удаления 30:\n");
    inorder(root);
    printf("\n");

    Test_Inserting_an_element_no1();
    Test_Inserting_another_element_no2();
    Test_Finding_an_existing_element_no3();
    Test_Find_the_missing_element_with_remaining_no4();
    Test_Delete_elemen10_no5();
    Test_Delete_elemen20_no6();
    Test_Inserting_multiple_elements_and_deleting_the_root_no7();
    Test_Checking_that_search_works_correctly_after_deletion_no8();
    Test_Attempt_to_delete_nonexistent_element_no9();
    Test_Remove_all_elements_and_check_for_empty_tree_no10();

    return 0;
}