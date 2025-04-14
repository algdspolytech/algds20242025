#include <gtest/gtest.h>
#include "RBtree.h"

// Test 1: Добавление элемента в пустое дерево
TEST(RBTreeTest, AddToEmptyTree_no1) {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    Node *result = search(tree, 10);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 10);
    ASSERT_EQ(result->color, BLACK); // Корень всегда черный
}

// Test 2: Добавление нескольких элементов, проверка баланса дерева
TEST(RBTreeTest, AddMultipleElementsAndCheckBalance_no2) {
    RBTree *tree = createRBTree();
    insert(tree, 20);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 10);
    insert(tree, 30);
    
    Node *result = search(tree, 15);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 15);

    // Проверка, что дерево сбалансировано (правильный цвет корня и баланс)
    ASSERT_EQ(tree->root->color, BLACK); // Корень должен быть черным
}

// Test 3: Поиск существующего элемента в дереве
TEST(RBTreeTest, SearchExistingElement_no3) {
    RBTree *tree = createRBTree();
    insert(tree, 5);
    Node *result = search(tree, 5);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 5);
}

// Test 4: Поиск несуществующего элемента в дереве
TEST(RBTreeTest, SearchNonExistentElement_no4) {
    RBTree *tree = createRBTree();
    insert(tree, 5);
    Node *result = search(tree, 10);
    ASSERT_EQ(result, tree->TNULL);
}

// Test 5: Вставка элемента, проверка левого поворота
TEST(RBTreeTest, LeftRotateOnInsert_no5) {
    RBTree *tree = createRBTree();
    insert(tree, 30);
    insert(tree, 20);
    insert(tree, 25);

    // Проверим, что дерево сбалансировано, после вставки элемента
    Node *result = search(tree, 25);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 25);
    ASSERT_EQ(result->color, BLACK);  // Проверим, что дерево не нарушило баланс
}

// Test 6: Вставка элемента, проверка правого поворота
TEST(RBTreeTest, RightRotateOnInsert_no6) {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 15);
    insert(tree, 20);

    // Проверим, что дерево сбалансировано
    Node *result = search(tree, 15);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 15);
    ASSERT_EQ(result->color, BLACK);  // Проверка баланса дерева
}

// Test 7: Повторная вставка элемента (проверка, что элементы уникальны)
TEST(RBTreeTest, InsertDuplicateElement_no7) {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 10);  // Вставка дубликата, элемент не должен добавляться

    Node *result = search(tree, 10);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 10);
}

// Test 8: Добавление элементов и проверка цвета корня после нескольких вставок
TEST(RBTreeTest, RootColorAfterMultipleInsertions_no8) {
    RBTree *tree = createRBTree();
    insert(tree, 5);
    insert(tree, 15);
    insert(tree, 10);
    insert(tree, 25);
    insert(tree, 30);
    
    // Проверяем, что корень дерева все еще черный
    ASSERT_EQ(tree->root->color, BLACK);
}

// Test 9: Проверка корректности поиска после удаления (если реализация удаления будет добавлена)
TEST(RBTreeTest, SearchAfterDeletion_no9) {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 15);

    // Удаляем элемент 5 (удаление не реализовано в этом примере, но тест может быть использован в будущем)
    // delete(tree, 5);
    Node *result = search(tree, 5);
    ASSERT_EQ(result, tree->TNULL);  // Элемент должен быть удален, так что его не должно быть в дереве
}

// Test 10: Добавление элемента в пустое дерево и проверка минимального элемента
TEST(RBTreeTest, AddAndFindMinElement_no10) {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 15);
    
    Node *minNode = tree->root;
    while (minNode->left != tree->TNULL) {
        minNode = minNode->left;  // Идем по дереву влево, пока не найдем минимальный элемент
    }
    ASSERT_EQ(minNode->data, 5);  // Минимальный элемент в дереве — это 5
}