#include "../avl_tree.h"
#include "../bst_tree.h"
#include <gtest/gtest.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

using namespace std::chrono;

TEST(TreeTests, InsertSearchDeleteEdgeCases) {
    AVLTree avl;
    BSTree bst;

    std::vector<int> keys = {1, 1000000, -1000000, 0, 500, -500, 999999, -999999, INT32_MAX, INT32_MIN};

    for (int key : keys) {
        avl.insert(key);
        bst.insert(key);
    }
    

    // SEARCH existing
    for (int key : keys) {
        EXPECT_TRUE(avl.search(key));
        EXPECT_TRUE(bst.search(key));
    }

    // SEARCH non-existing
    EXPECT_FALSE(avl.search(1234567));
    EXPECT_FALSE(bst.search(1234567));

    // DELETE edge keys
    for (int key : keys) {
        avl.remove(key);
        bst.remove(key);
        EXPECT_FALSE(avl.search(key));
        EXPECT_FALSE(bst.search(key));
    }
}

TEST(TreeTests, RandomizedInsertSearch) {
    AVLTree avl;
    BSTree bst;

    std::vector<int> data(10000);
    std::iota(data.begin(), data.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    // INSERT random
    for (int key : data) {
        avl.insert(key);
        bst.insert(key);
    }

    // SEARCH random
    for (int i = 0; i < 1000; i++) {
        int random_index = rand() % data.size();
        int key = data[random_index];
        EXPECT_TRUE(avl.search(key));
        EXPECT_TRUE(bst.search(key));
    }
}
TEST(TreeTests, PerformanceComparison) {
    AVLTree avl;
    BSTree bst;

    std::vector<int> data(100000);
    std::iota(data.begin(), data.end(), 0);
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});

    // INSERT
    auto start = high_resolution_clock::now();
    for (int key : data) avl.insert(key);
    auto end = high_resolution_clock::now();
    std::cout << "AVL вставка: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int key : data) bst.insert(key);
    end = high_resolution_clock::now();
    std::cout << "BST вставка: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // SEARCH
    start = high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) avl.search(data[i]);
    end = high_resolution_clock::now();
    std::cout << "AVL Поиск 10k запросов: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) bst.search(data[i]);
    end = high_resolution_clock::now();
    std::cout << "BST Поиск 10k запросов: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // DELETE
    start = high_resolution_clock::now();
    for (int i = 0; i < 5000; ++i) avl.remove(data[i]);
    end = high_resolution_clock::now();
    std::cout << "AVL Удаление 5k: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int i = 0; i < 5000; ++i) bst.remove(data[i]);
    end = high_resolution_clock::now();
    std::cout << "BST Удаление 5k: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

TEST(TreeTests, DegenerateCase) {
    AVLTree avl;
    BSTree bst;

    for (int i = 0; i < 10000; ++i) {
        avl.insert(i);
        bst.insert(i);
    }
    EXPECT_TRUE(avl.search(9999));
    EXPECT_TRUE(bst.search(9999));
}

TEST(TreeTests, RandomDeletions) {
    AVLTree avl;
    BSTree bst;

    std::vector<int> data(1000);
    std::iota(data.begin(), data.end(), 0);
    std::shuffle(data.begin(), data.end(), std::mt19937(std::random_device()()));

    for (int key : data) {
        avl.insert(key);
        bst.insert(key);
    }

    // Перемешиваем ещё раз для удаления
    std::shuffle(data.begin(), data.end(), std::mt19937(std::random_device()()));

    for (int key : data) {
        avl.remove(key);
        bst.remove(key);
        EXPECT_FALSE(avl.search(key));
        EXPECT_FALSE(bst.search(key));
    }
}

TEST(TreeTests, DuplicateInsertions) {
    AVLTree avl;
    BSTree bst;

    avl.insert(42);
    avl.insert(42);
    bst.insert(42);
    bst.insert(42);


    EXPECT_TRUE(avl.search(42));
    EXPECT_TRUE(bst.search(42));

    avl.remove(42);
    bst.remove(42);

    EXPECT_FALSE(avl.search(42));
    EXPECT_FALSE(bst.search(42));
}
