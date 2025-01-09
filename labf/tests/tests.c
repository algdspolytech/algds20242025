#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h" // IWYU pragma: keep
#include "../include/bin_tree.h"
#include <stdio.h>

Test(TreeTests, InsertSingleElement) {
    Node* root = NULL;

    insert(&root, 10);
    cr_assert_not_null(root, "Корень дерева должен быть не NULL после вставки.");
    cr_assert_eq(root->value, 10, "Значение корня дерева должно быть 10.");
    cr_assert_eq(root->count, 1, "Количество узлов в дереве должно быть 1.");

    free(root); // Освобождаем память
}

// Тест: Проверка вставки нескольких элементов
Test(TreeTests, InsertMultipleElements) {
    Node* root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);

    cr_assert_not_null(root->left, "Левый потомок корня должен быть не NULL.");
    cr_assert_eq(root->left->value, 5, "Значение левого потомка должно быть 5.");

    cr_assert_not_null(root->right, "Правый потомок корня должен быть не NULL.");
    cr_assert_eq(root->right->value, 15, "Значение правого потомка должно быть 15.");

    cr_assert_eq(root->count, 3, "Количество узлов в дереве должно быть 3.");

    free(root->left);
    free(root->right);
    free(root);
}

// Тест: Проверка удаления листа
Test(TreeTests, DeleteLeafNode) {
    Node* root = NULL;

    insert(&root, 10);
    insert(&root, 5);

    delete(&root, 5);

    cr_assert_null(root->left, "Левый потомок корня должен быть NULL после удаления.");
    cr_assert_eq(root->count, 1, "Количество узлов в дереве должно быть 1 после удаления.");

    free(root);
}

// Тест: Проверка удаления узла с двумя потомками
Test(TreeTests, DeleteNodeWithTwoChildren) {
    Node* root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);

    delete(&root, 10);

    cr_assert_not_null(root, "Корень дерева должен быть не NULL после удаления.");
    cr_assert_eq(root->value, 15, "Новое значение корня должно быть 15.");
    cr_assert_eq(root->count, 2, "Количество узлов в дереве должно быть 2.");

    free(root->left);
    free(root);
}

// Тест: Удаление несуществующего узла
Test(TreeTests, DeleteNonExistentNode) {
    Node* root = NULL;

    insert(&root, 10);

    delete(&root, 20); // Удаляем несуществующий узел

    cr_assert_not_null(root, "Корень дерева должен быть не NULL.");
    cr_assert_eq(root->value, 10, "Значение корня дерева должно остаться 10.");
    cr_assert_eq(root->count, 1, "Количество узлов в дереве должно остаться 1.");

    free(root);
}
