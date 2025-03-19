#include "main.h"
#include <gtest/gtest.h>
#include <vector>

// Вспомогательная функция для in-order обхода с записью ключей в std::vector
void inorderVector(RBNode* root, std::vector<int>& vec) {
    if (root == NULL) return;
    inorderVector(root->left, vec);
    vec.push_back(root->key);
    inorderVector(root->right, vec);
}

// Тест 1: S1 = NULL, S2 = NULL
TEST(RBTreeTest, Test1) {
    RBNode *S1 = NULL;
    RBNode *S2 = NULL;
    RBNode *x = new_node(42, RED);
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    ASSERT_EQ(root->key, 42);
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->right, nullptr);
    free_tree(root);
}

// Тест 2: S1 = NULL, S2 = одноэлементное дерево (ключ 10)
TEST(RBTreeTest, Test2) {
    RBNode *S1 = NULL;
    RBNode *S2 = new_node(10, BLACK);
    RBNode *x = new_node(5, RED); // 5 <= 10
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    int arr[2];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    ASSERT_EQ(idx, 2);
    ASSERT_EQ(arr[0], 5);
    ASSERT_EQ(arr[1], 10);
    free_tree(root);
}

// Тест 3: S1 = одноэлементное дерево (ключ 10), S2 = NULL
TEST(RBTreeTest, Test3) {
    RBNode *S1 = new_node(10, BLACK);
    RBNode *S2 = NULL;
    RBNode *x = new_node(20, RED); // 10 <= 20
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    int arr[2];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    ASSERT_EQ(idx, 2);
    ASSERT_EQ(arr[0], 10);
    ASSERT_EQ(arr[1], 20);
    free_tree(root);
}

// Тест 4: S1 и S2 с равными черными высотами (оба по одному узлу)
TEST(RBTreeTest, Test4) {
    RBNode *S1 = new_node(5, BLACK);
    RBNode *S2 = new_node(10, BLACK);
    RBNode *x = new_node(7, RED); // 5 <= 7 <= 10
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    int arr[3];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    ASSERT_EQ(idx, 3);
    ASSERT_EQ(arr[0], 5);
    ASSERT_EQ(arr[1], 7);
    ASSERT_EQ(arr[2], 10);
    free_tree(root);
}

// Тест 5: bh(S1) < bh(S2).
// S1: одноэлементное дерево (ключ 5, BLACK, bh = 2).
// S2: двухуровневое дерево с корнем 10 (BLACK) и левым ребенком 7 (RED), bh = 2.
TEST(RBTreeTest, Test5) {
    RBNode *S1 = new_node(5, BLACK);
    RBNode *S2 = new_node(10, BLACK);
    // Изменили цвет узла 7 на RED, чтобы соблюсти баланс черных высот:
    RBNode *node7 = new_node(7, RED);
    S2->left = node7; 
    node7->parent = S2;
    RBNode *x = new_node(6, RED); // 5 <= 6 <= 7
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    int arr[4];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    ASSERT_EQ(idx, 4);
    ASSERT_EQ(arr[0], 5);
    ASSERT_EQ(arr[1], 6);
    ASSERT_EQ(arr[2], 7);
    ASSERT_EQ(arr[3], 10);
    free_tree(root);
}


// Тест 6: bh(S1) > bh(S2)
// S1: дерево из двух узлов: корень 5 (BLACK) с правым ребенком 7 (BLACK)
// S2: одноэлементное дерево (ключ 10, BLACK)
TEST(RBTreeTest, Test6) {
    RBNode *S1 = new_node(5, BLACK);
    RBNode *node7 = new_node(7, RED);
    S1->right = node7;
    node7->parent = S1;
    RBNode *S2 = new_node(10, BLACK);
    RBNode *x = new_node(8, RED);
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    int arr[4];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    ASSERT_EQ(idx, 4);
    ASSERT_EQ(arr[0], 5);
    ASSERT_EQ(arr[1], 7);
    ASSERT_EQ(arr[2], 8);
    ASSERT_EQ(arr[3], 10);
    free_tree(root);
}

// Тест 7: Объединение деревьев с несколькими узлами.
// S1: красно­черное дерево с ключами {2,4,5}
// S2: красно­черное дерево с ключами {10,12,15}
// x: 7 (2,4,5 <= 7 <= 10)
TEST(RBTreeTest, Test7) {
    // Построение S1 вручную
    RBNode *S1 = new_node(4, BLACK);
    RBNode *n2 = new_node(2, RED);
    RBNode *n5 = new_node(5, RED);
    S1->left = n2; 
    n2->parent = S1;
    S1->right = n5; 
    n5->parent = S1;
    
    // Построение S2 вручную
    RBNode *S2 = new_node(12, BLACK);
    RBNode *n10 = new_node(10, RED);
    RBNode *n15 = new_node(15, RED);
    S2->left = n10; 
    n10->parent = S2;
    S2->right = n15; 
    n15->parent = S2;
    
    RBNode *x = new_node(7, RED); // 5 <= 7 <= 10
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    
    int arr[7];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    int expected[7] = {2,4,5,7,10,12,15};
    ASSERT_EQ(idx, 7);
    for (int i = 0; i < 7; i++)
        ASSERT_EQ(arr[i], expected[i]);
    free_tree(root);
}

// Тест 8: Объединение деревьев с равными высотами и проверка in-order обхода.
// S1: дерево с ключами {3,5,6}
// S2: дерево с ключами {8,10,12}
// x: 7, ожидаем in-order: 3,5,6,7,8,10,12
TEST(RBTreeTest, Test8) {
    RBNode *S1 = new_node(5, BLACK);
    RBNode *n3 = new_node(3, RED);
    RBNode *n6 = new_node(6, RED);
    S1->left = n3; 
    n3->parent = S1;
    S1->right = n6; 
    n6->parent = S1;
    
    RBNode *S2 = new_node(10, BLACK);
    RBNode *n8 = new_node(8, RED);
    RBNode *n12 = new_node(12, RED);
    S2->left = n8; 
    n8->parent = S2;
    S2->right = n12; 
    n12->parent = S2;
    
    RBNode *x = new_node(7, RED);
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    
    int arr[7];
    int idx = 0;
    inorder_traversal(root, arr, &idx);
    int expected[7] = {3,5,6,7,8,10,12};
    ASSERT_EQ(idx, 7);
    for (int i = 0; i < 7; i++)
        ASSERT_EQ(arr[i], expected[i]);
    free_tree(root);
}

// Тест 9: Проверка корректности in-order обхода и инвариантов RB-дерева.
// S1: дерево с ключами {1,2}
// S2: дерево с ключами {4,5}
// x: 3, ожидаем in-order: 1,2,3,4,5
TEST(RBTreeTest, Test9) {
    RBNode *S1 = new_node(1, BLACK);
    RBNode *n2 = new_node(2, RED);
    S1->right = n2; 
    n2->parent = S1;
    
    RBNode *S2 = new_node(5, BLACK);
    RBNode *n4 = new_node(4, RED);
    S2->left = n4; 
    n4->parent = S2;
    
    RBNode *x = new_node(3, RED);
    RBNode *root = rb_join(S1, x, S2);
    validate_rb_tree(root);
    
    std::vector<int> vec;
    inorderVector(root, vec);
    std::vector<int> expected = {1,2,3,4,5};
    ASSERT_EQ(vec.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++)
        ASSERT_EQ(vec[i], expected[i]);
    free_tree(root);
}

// Тест 10: Последовательное объединение (chain join).
// Последовательно объединяем одноэлементные деревья.
TEST(RBTreeTest, Test10) {
    RBNode *tree = NULL;
    int keys[] = {5, 10, 15, 20, 25};
    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        RBNode *x = new_node(keys[i], RED);
        tree = rb_join(tree, x, NULL);
        validate_rb_tree(tree);
    }
    std::vector<int> vec;
    inorderVector(tree, vec);
    std::vector<int> expected = {5, 10, 15, 20, 25};
    ASSERT_EQ(vec.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++)
        ASSERT_EQ(vec[i], expected[i]);
    free_tree(tree);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
