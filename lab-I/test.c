#include "gtest/gtest.h"
#include "rbtree.h"
#include "bstree.h"



// 1. Добавление элемента в пустое дерево
TEST(RBTreeTest, AddToEmptyTree_no1) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    EXPECT_NE(tree.root, tree.nil); // Проверяем, что корень не равен nil
    EXPECT_EQ(tree.root->data, 10); // Проверяем, что корень содержит добавленный элемент
    EXPECT_EQ(tree.root->color, BLACK); // Корень всегда черный

    freeRBTree(&tree);
}

// 2. Добавление нескольких элементов
TEST(RBTreeTest, AddMultipleElements_no2) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    insertRBTree(&tree, 20);
    insertRBTree(&tree, 5);

    EXPECT_EQ(tree.root->data, 10); // Корень
    EXPECT_EQ(tree.root->left->data, 5); // Левый потомок
    EXPECT_EQ(tree.root->right->data, 20); // Правый потомок

    freeRBTree(&tree);
}

// 3. Поиск элемента в дереве
TEST(RBTreeTest, SearchElement_no3) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    insertRBTree(&tree, 20);
    insertRBTree(&tree, 5);

    RBTreeNode* node = searchRBTree(&tree, 20);
    EXPECT_NE(node, tree.nil); // Элемент найден
    EXPECT_EQ(node->data, 20);

    node = searchRBTree(&tree, 100);
    EXPECT_EQ(node, tree.nil); // Элемент не найден

    freeRBTree(&tree);
}

// 4. Удаление элемента из дерева
TEST(RBTreeTest, DeleteElement_no4) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    insertRBTree(&tree, 20);
    insertRBTree(&tree, 5);

    deleteRBTree(&tree, 20);
    RBTreeNode* node = searchRBTree(&tree, 20);
    EXPECT_EQ(node, tree.nil); // Элемент удален

    freeRBTree(&tree);
}

// 5. Удаление элемента из пустого дерева
TEST(RBTreeTest, DeleteFromEmptyTree_no5) {
    RBTree tree;
    initRBTree(&tree);

    deleteRBTree(&tree, 10); // Попытка удалить из пустого дерева
    EXPECT_EQ(tree.root, tree.nil); // Дерево остается пустым

    freeRBTree(&tree);
}

// 6. Добавление дубликатов
TEST(RBTreeTest, AddDuplicates_no6) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    insertRBTree(&tree, 10); // Дубликат

    EXPECT_EQ(tree.root->data, 10);
    EXPECT_EQ(tree.root->left, tree.nil); // Левый потомок должен быть nil
    EXPECT_EQ(tree.root->right, tree.nil); // Правый потомок должен быть nil

    freeRBTree(&tree);
}

// 7. Поиск в пустом дереве
TEST(RBTreeTest, SearchInEmptyTree_no7) {
    RBTree tree;
    initRBTree(&tree);

    RBTreeNode* node = searchRBTree(&tree, 10);
    EXPECT_EQ(node, tree.nil); // Элемент не найден

    freeRBTree(&tree);
}

// 8. Удаление корневого элемента
TEST(RBTreeTest, DeleteRootElement_no8) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    deleteRBTree(&tree, 10);

    EXPECT_EQ(tree.root, tree.nil); // Дерево должно быть пустым

    freeRBTree(&tree);
}

// 9. Добавление элементов в порядке убывания
TEST(RBTreeTest, AddDescendingOrder_no9) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 30);
    insertRBTree(&tree, 20);
    insertRBTree(&tree, 10);

    EXPECT_EQ(tree.root->data, 20); // Корень
    EXPECT_EQ(tree.root->left->data, 10); // Левый потомок
    EXPECT_EQ(tree.root->right->data, 30); // Правый потомок

    freeRBTree(&tree);
}

// 10. Удаление несуществующего элемента
TEST(RBTreeTest, DeleteNonExistentElement_no10) {
    RBTree tree;
    initRBTree(&tree);

    insertRBTree(&tree, 10);
    deleteRBTree(&tree, 20); // Попытка удалить несуществующий элемент

    EXPECT_NE(tree.root, tree.nil); // Дерево не должно быть пустым
    EXPECT_EQ(tree.root->data, 10); // Корень остается неизменным

    freeRBTree(&tree);
}