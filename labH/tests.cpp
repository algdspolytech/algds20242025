#include "avl_list.h"
#include <assert.h>
#include <stdio.h>

// Тест 1. Вставка в пустое дерево
void test_insert_to_empty_tree(Node** root) {
    *root = insert(*root, 10, 0);
    assert(*root != NULL && (*root)->key == 10);
    printf("TestInsertToEmptyTree_HappyPath_no1 passed\n");
}

// Тест 2. Вставка в начало
void test_insert_at_beginning(Node** root) {
    *root = insert(*root, 5, 0);
    assert(*root != NULL && (*root)->left != NULL && (*root)->left->key == 5);
    printf("TestInsertAtBeginning_HappyPath_no2 passed\n");
}

// Тест 3. Вставка в конец
void test_insert_at_end(Node** root) {
    *root = insert(*root, 15, 2);
    assert(*root != NULL && (*root)->right != NULL && (*root)->right->key == 15);
    printf("TestInsertAtEnd_HappyPath_no3 passed\n");
}

// Тест 4. Вставка в середину
void test_insert_in_middle(Node** root) {
    *root = insert(*root, 12, 2);
    assert(*root != NULL && (*root)->right->left != NULL && (*root)->right->left->key == 12);
    printf("TestInsertInMiddle_HappyPath_no4 passed\n");
}

// Тест 5. Поиск существующего элемента
void test_search_existing_key(Node* root) {
    assert(root != NULL && search(root, 10) != NULL);
    printf("TestSearchExistingKey_HappyPath_no5 passed\n");
}

// Тест 6. Поиск отсутствующего элемента
void test_search_non_existing_key(Node* root) {
    assert(root != NULL && search(root, 100) == NULL);
    printf("TestSearchNonExistingKey_HappyPath_no6 passed\n");
}

// Тест 7. Поиск минимального элемента
void test_find_min_element(Node* root) {
    assert(root != NULL && findKth(root, 0)->key == 5);
    printf("TestFindMinElement_HappyPath_no7 passed\n");
}

// Тест 8. Поиск максимального элемента
void test_find_max_element(Node* root) {
    assert(root != NULL && findKth(root, size(root) - 1)->key == 15);
    printf("TestFindMaxElement_HappyPath_no8 passed\n");
}

// Тест 9. Поиск k-го элемента (не существующего)
void test_find_kth_element_not_found(Node* root) {
    assert(root != NULL && findKth(root, 10) == NULL);
    printf("TestFindKthElementNotFound_EdgeCase_no9 passed\n");
}

// Тест 10. Вставка и балансировка (левый поворот)
void test_left_rotation(Node** root) {
    *root = insert(*root, 20, 4);
    *root = insert(*root, 25, 5);
    assert(*root != NULL && (*root)->right->key == 20);
    printf("TestLeftRotation_HappyPath_no10 passed\n");
}

// Тест 11. Слияние с пустым деревом
void test_merge_with_empty_tree(Node** root) {
    *root = mergeTrees(*root, NULL);
    assert(*root != NULL && search(*root, 10) != NULL);
    printf("TestMergeWithEmptyTree_HappyPath_no11 passed\n");
}

// Тест 12. Балансировка после серии вставок
void test_tree_balance_after_insertions(Node** root) {
    *root = insert(*root, 50, 9);
    *root = insert(*root, 60, 10);
    assert(*root != NULL && getBalance(*root) >= -1 && getBalance(*root) <= 1);
    printf("TestTreeBalance_AfterInsertions_no12 passed\n");
}

// Тест 13. Вставка в AVL со многими элементами
void test_insert_many_elements(Node** root) {
    for (int i = 100; i < 110; i++) {
        *root = insert(*root, i, size(*root));
    }
    assert(*root != NULL && size(*root) == 18);
    printf("TestInsertManyElements_HappyPath_no13 passed\n");
}

// Тест 14. Проверка поиска в пустом дереве
void test_search_in_empty_tree() {
    assert(search(NULL, 10) == NULL);
    printf("TestSearchInEmptyTree_EdgeCase_no14 passed\n");
}

// Тест 15. Проверка k-го элемента в пустом дереве
void test_find_kth_in_empty_tree() {
    assert(findKth(NULL, 0) == NULL);
    printf("TestFindKthInEmptyTree_EdgeCase_no15 passed\n");
}

int main() {
    Node* root = NULL;
    // Запускаем все тесты
    test_insert_to_empty_tree(&root);
    test_insert_at_beginning(&root);
    test_insert_at_end(&root);
    test_insert_in_middle(&root);
    test_search_existing_key(root);
    test_search_non_existing_key(root);
    test_find_min_element(root);
    test_find_max_element(root);
    test_find_kth_element_not_found(root);
    test_left_rotation(&root);
    test_merge_with_empty_tree(&root);
    test_tree_balance_after_insertions(&root);
    test_insert_many_elements(&root);
    test_search_in_empty_tree();
    test_find_kth_in_empty_tree();

    return 0;
}
