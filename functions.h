#include "tests.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;

struct BinTree {
    int data;
    BinTree* left;
    BinTree* right;
};

BinTree* insert(BinTree* root, int value);
void inorderTraversal(BinTree* root);
BinTree* search(BinTree* root, int value);
BinTree* remove(BinTree* root, int value);
void destroyTree(BinTree* root);

struct AVLTree {
    int data;
    int height;
    AVLTree* left;
    AVLTree* right;
};

AVLTree* insert(AVLTree* root, int value);
AVLTree* remove(AVLTree* root, int value);
void inorderTraversal(AVLTree* root);
int getHeight(AVLTree* node);
int getBalanceFactor(AVLTree* node);
AVLTree* rotateRight(AVLTree* y);
AVLTree* rotateLeft(AVLTree* x);
AVLTree* rotateLeftRight(AVLTree* node);
AVLTree* rotateRightLeft(AVLTree* node);
AVLTree* search(AVLTree* root, int value);

void testBinaryTree(int cnt);
void testAVLTree(int cnt);