#define _CRT_SECURE_NO_WARNINGS

#include "tests.h"

// Тест 1: Проверка вставки и поиска элементов
void test_insert_and_search_No1() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 30);

    assert(tree.root != NULL);
    assert(tree.root->data == 20);  // Должен сбалансироваться

    assert(tree.root->left->data == 10);
    assert(tree.root->right->data == 30);
    printf("Test 1 completed\n");
}

// Тест 2: Проверка объединения двух деревьев
void test_union_No2() {
    RBTree S1 = { NULL }, S2 = { NULL };
    insert(&S1, 5);
    insert(&S1, 10);
    insert(&S2, 15);
    insert(&S2, 20);

    int x = 12;
    RBTree* result = unionRBTree(&S1, x, &S2);

    assert(result != NULL);
    assert(result->root != NULL);
    assert(result->root->data == 10);
    assert(result->root->left->data == 5);
    assert(result->root->right->left->data == 12);
    printf("Test 2 completed\n");
}

// Тест 3: Проверка обхода дерева
void test_inorder_traversal_No3() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);

    printf("Ожидаемый порядок: 5 10 20\n");
    printf("Полученный порядок: ");
    inorder(tree.root);
    printf("\n");
    printf("Test 3 completed\n");
}

// Тест 4: Проверка баланса дерева (корень всегда чёрный)
void test_balance_No4() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 30);
    insert(&tree, 40);
    insert(&tree, 50);

    assert(tree.root->color == BLACK);
    printf("Test 4 completed\n");
}

// Тест 5: Проверка минимального элемента
void test_min_element_No5() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);

    Node* minNode = tree.root;
    while (minNode->left) minNode = minNode->left;

    assert(minNode->data == 5);
    printf("Test 5 completed\n");
}

// Тест 6: Проверка максимального элемента
void test_max_element_No6() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);

    Node* maxNode = tree.root;
    while (maxNode->right) maxNode = maxNode->right;

    assert(maxNode->data == 20);
    printf("Test 6 completed\n");
}

// Тест 7: Проверка работы с пустым деревом
void test_empty_tree_No7() {
    RBTree tree = { NULL };
    assert(tree.root == NULL);
    printf("Test 7 completed\n");
}

// Тест 8: Вставка уже существующего элемента (не должно ломать дерево)
void test_duplicate_insert_No8() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 10);  // Повторный insert

    // Проверяем, что 10 встречается только один раз (дубликаты запрещены)
    Node* node = tree.root;
    int count = 0;
    
    if (node->data == 10) count++;
    if (node->left && node->left->data == 10) count++;
    if (node->right && node->right->data == 10) count++;

    assert(count == 1);
    printf("Test 8 completed\n");
}

// Тест 9: Проверка на правильность цвета узлов
void test_node_colors_No9() {
    RBTree tree = { NULL };
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 30);

    assert(tree.root->color == BLACK);
    if (tree.root->left) assert(tree.root->left->color == RED);
    if (tree.root->right) assert(tree.root->right->color == RED);
    printf("Test 9 completed\n");
}

// Тест 10: Проверка работы `mergeTrees`
void test_merge_trees_No10() {
    RBTree tree = { NULL };
    RBTree tree2 = { NULL };

    insert(&tree, 5);
    insert(&tree, 15);
    insert(&tree2, 10);
    insert(&tree2, 20);

    mergeTrees(&tree, tree2.root);

    assert(tree.root != NULL);
    assert(tree.root->data != 0);
    printf("Test 10 completed\n");
}
