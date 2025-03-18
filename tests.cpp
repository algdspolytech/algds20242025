#include <assert.h>
#include <iostream>
#include <sstream> 
#include "tests.h"
#include "functions.h"

void testInsertBinTree() {
    BinTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    assert(root->data == 10);
    assert(root->left->data == 5);
    assert(root->right->data == 15);
}

void testInorderTraversalBinTree() {
    BinTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    std::stringstream ss;
    std::streambuf* old_cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
    inorderTraversal(root);
    std::cout.rdbuf(old_cout_buffer);
    std::string output = ss.str();
    assert(output == "5 10 15 ");
}

void testSearchBinTree() {
    BinTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    BinTree* foundNode = search(root, 5);
    assert(foundNode != nullptr);
    assert(foundNode->data == 5);
    foundNode = search(root, 20);
    assert(foundNode == nullptr);
}

void testRemoveBinTree() {
    BinTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = remove(root, 10);
    assert(root->data == 15);
    assert(root->left->data == 5);
}

void testInsertAVLTree() {
    AVLTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    assert(root->data == 10);
    assert(root->left->data == 5);
    assert(root->right->data == 15);
}

void testRotateLeftRight() {
    AVLTree* root = nullptr;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 25);
    assert(root->data == 25);
    assert(root->left->data == 20);
    assert(root->right->data == 30);
}

void testRotateRightLeft() {
    AVLTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 15);
    assert(root->data == 15);
    assert(root->left->data == 10);
    assert(root->right->data == 20);
}

void testRemoveAVLTree() {
    AVLTree* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = remove(root, 10);
    assert(root->data == 15);
    assert(root->left->data == 5);
}

void TESTS() {
    void testInsertBinTree();
    void testInorderTraversalBinTree();
    void testSearchBinTree();
    void testRemoveBinTree();
    void testInsertAVLTree();
    void testRotateLeftRight();
    void testRotateRightLeft();
    void testRemoveAVLTree();
    cout << "All tests passed." << endl;
}