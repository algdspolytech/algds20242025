extern "C" {
    #include "../avl_tree.h"
    #include "../bst_tree.h"
}

#include <gtest/gtest.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#include <numeric>

using namespace std::chrono;

TEST(TreeTests, InsertSearchDeleteEdgeCases) {
    AVLTree avl;
    BSTree bst;
    AVLTree_init(&avl);
    BSTree_init(&bst);

    std::vector<int> keys = {1, 1000000, -1000000, 0, 500, -500, 999999, -999999, INT32_MAX, INT32_MIN};

    for (int key : keys) {
        AVLTree_insert(&avl, key);
        BSTree_insert(&bst, key);
    }

    for (int key : keys) {
        EXPECT_TRUE(AVLTree_search(&avl, key));
        EXPECT_TRUE(BSTree_search(&bst, key));
    }

    EXPECT_FALSE(AVLTree_search(&avl, 1234567));
    EXPECT_FALSE(BSTree_search(&bst, 1234567));

    for (int key : keys) {
        AVLTree_remove(&avl, key);
        BSTree_remove(&bst, key);
        EXPECT_FALSE(AVLTree_search(&avl, key));
        EXPECT_FALSE(BSTree_search(&bst, key));
    }

    AVLTree_free(&avl);
    BSTree_free(&bst);
}

TEST(TreeTests, RandomizedInsertSearch) {
    AVLTree avl;
    BSTree bst;
    AVLTree_init(&avl);
    BSTree_init(&bst);

    std::vector<int> data(10000);
    std::iota(data.begin(), data.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    for (int key : data) {
        AVLTree_insert(&avl, key);
        BSTree_insert(&bst, key);
    }

    for (int i = 0; i < 1000; i++) {
        int random_index = rand() % data.size();
        int key = data[random_index];
        EXPECT_TRUE(AVLTree_search(&avl, key));
        EXPECT_TRUE(BSTree_search(&bst, key));
    }

    AVLTree_free(&avl);
    BSTree_free(&bst);
}

TEST(TreeTests, PerformanceComparison) {
    AVLTree avl;
    BSTree bst;
    AVLTree_init(&avl);
    BSTree_init(&bst);

    std::vector<int> data(100000);
    std::iota(data.begin(), data.end(), 0);
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});

    auto start = high_resolution_clock::now();
    for (int key : data) AVLTree_insert(&avl, key);
    auto end = high_resolution_clock::now();
    std::cout << "AVL вставка: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int key : data) BSTree_insert(&bst, key);
    end = high_resolution_clock::now();
    std::cout << "BST вставка: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) AVLTree_search(&avl, data[i]);
    end = high_resolution_clock::now();
    std::cout << "AVL Поиск 10k запросов: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) BSTree_search(&bst, data[i]);
    end = high_resolution_clock::now();
    std::cout << "BST Поиск 10k запросов: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < 5000; ++i) AVLTree_remove(&avl, data[i]);
    end = high_resolution_clock::now();
    std::cout << "AVL Удаление 5k: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < 5000; ++i) BSTree_remove(&bst, data[i]);
    end = high_resolution_clock::now();
    std::cout << "BST Удаление 5k: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    AVLTree_free(&avl);
    BSTree_free(&bst);
}