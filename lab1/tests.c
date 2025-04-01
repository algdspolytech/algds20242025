#include "gtest/gtest.h"
#include "RandomBinaryTree.h"

// Тест: добавление множества узлов и проверка их наличия
TEST(RandomBinaryTreeTests, AddManyNodes) {
    Node* tree = nullptr;
    const int n = 98765;

    for (int i = 1; i <= n; ++i) {
        tree = add(tree, i, i * 1.0);
    }

    int counter = 0;
    for (int i = 1; i <= n; ++i) {
        if (get(tree, i) == i * 1.0) {
            counter++;
        }
    }

    EXPECT_EQ(counter, n);
}

// Тест: проверка размера дерева после добавления узлов
TEST(RandomBinaryTreeTests, SizeAfterAddingNodes) {
    Node* tree = nullptr;
    const int n = 23451;

    for (int i = 1; i <= n; ++i) {
        tree = add(tree, i, i * 1.0);
    }

    EXPECT_EQ(size(tree), n);
}

// Тест: проверка высоты дерева
TEST(RandomBinaryTreeTests, TreeHeight) {
    Node* tree = nullptr;
    const int n = 34213;

    for (int i = 1; i <= n; ++i) {
        tree = add(tree, i, i * 1.0);
    }

    EXPECT_GT(100, height(tree)); // Высота должна быть меньше 100 для сбалансированного дерева
}

// Тест: удаление узлов из дерева
TEST(RandomBinaryTreeTests, RemoveManyNodes) {
    Node* tree = nullptr;
    const int n = 23451;
    const int k = 2132;

    for (int i = 1; i <= n; ++i) {
        tree = add(tree, i, i * 1.0);
    }

    for (int i = 1; i <= k; ++i) {
        tree = remove(tree, i);
    }

    EXPECT_EQ(size(tree), n - k);
}

// Тест: получение значений из дерева
TEST(RandomBinaryTreeTests, GetValuesFromTree) {
    Node* tree = nullptr;
    const int n = 12342;

    for (int i = 1; i <= n; ++i) {
        tree = add(tree, i, i * 1.0);
    }

    int counter = 0;
    for (int i = 1; i <= n; ++i) {
        if (get(tree, i) == i * 1.0) {
            counter++;
        }
    }

    EXPECT_EQ(counter, n);
}

// Тест: получение значения из пустого дерева
TEST(RandomBinaryTreeTests, GetFromEmptyTree) {
    Node* tree = nullptr;
    
    double value = get(tree, 7);
    
    EXPECT_EQ(value, 0.0); // Значение по умолчанию для пустого дерева
}

// Тест: размер пустого дерева
TEST(RandomBinaryTreeTests, SizeOfEmptyTree) {
    Node* tree = nullptr;

    EXPECT_EQ(size(tree), 0);
}

// Тест: высота пустого дерева
TEST(RandomBinaryTreeTests, HeightOfEmptyTree) {
    Node* tree = nullptr;

    EXPECT_EQ(height(tree), 0);
}

// Тест: удаление из пустого дерева
TEST(RandomBinaryTreeTests, RemoveFromEmptyTree) {
    Node* tree = nullptr;

    tree = remove(tree, 6);

    EXPECT_EQ(size(tree), 0);
}

// Тест: добавление и удаление всех узлов приводит к пустому дереву
TEST(RandomBinaryTreeTests, AddAndRemoveAllNodes) {
    Node* tree = nullptr;
    const int n = 150;

    for (int i = 1; i <= n; ++i) {
        tree = add(tree, i, i * 1.0);
    }

    for (int i = 1; i <= n; ++i) {
        tree = remove(tree, i);
    }

    EXPECT_EQ(size(tree), 0); // После удаления всех узлов дерево должно быть пустым
}
