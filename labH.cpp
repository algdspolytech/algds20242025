#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { BLACK, RED } Color;

typedef struct Node {
    int key;
    struct Node* left, * right, * parent;
    Color color;
} Node;

Node* createNode(int key, Color color) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    node->color = color;
    return node;
}

int blackHeight(Node* node) {
    int bh = 0;
    int i = 0;
    while (node) {
        if (node->color == BLACK && i != 0)
            bh++;
        node = node->left;
        i++;
    }
    return bh + 1;
}

Node* findBlHeightLeft(Node* root, int bh) {
    Node* current = root;
    Node* result = NULL;
    int count = blackHeight(root);
    int i = 0;

    while (current) {
        if (current->color == BLACK && i != 0)
            count--;

        if (count < bh) {
            break;
        }

        if (count == bh && (!result || current->key < result->key)) {
            result = current; 
        }

        current = current->left;
        i++;
    }
    return result;
}

Node* findBlHeightRight(Node* root, int bh) {
    Node* current = root;
    Node* result = NULL;
    int count = blackHeight(root);
    int i = 0;

    while (current) {
        if (current->color == BLACK && i != 0)
            count--;

        if (count < bh) {
            break;
        }

        if (count == bh && (!result || current->key > result->key)) {
            result = current;
        }

        current = current->right;
        i++;
    }
    return result;
}

void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void insert(Node** root, int key) {
    Node* z = createNode(key, RED);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = z->right = NULL;
    z->color = RED;

    insertFixup(root, z);
}

void insertFixup(Node** root, Node* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

Node* checkMatchRight(Node* T1, int x) {
    Node* current = T1;
    while (current) {
        if (current->key == x) {
            return current;
        }
        current = current->right;
    }
    return NULL;
}

Node* checkMatchLeft(Node* T1, int x) {
    Node* current = T1;
    while (current) {
        if (current->key == x) {
            return current;
        }
        current = current->left;
    }
    return NULL;
}

Node* rbUnion(Node** root, Node* T1, Node* T2, int x) {
    if (!T1 && !T2) {
        *root = createNode(x, BLACK);
        return *root;
    }
    if (!T1 && T2) {
        if (!checkMatchLeft(T2, x)) {
            insert(&T2, x);
        }
        return T2;
    }
    if (T1 && !T2) {
        if (!checkMatchRight(T1, x)) {
            insert(&T1, x);
        }
        return T1;
    }
    if ((!T1->left && !T1->right) && ((!T2->left && !T2->right))) {
        if (T1->key != T2->key) {
            insert(&T2, T1->key);
        }
        if (T1->key != x && T2->key != x) {
            insert(&T2, x);
        }
        return T2;
    }
    if (!T1->left && !T1->right) {
        if (T1->key != x) {
            if (!checkMatchLeft(T2, T1->key)) {
                insert(&T2, T1->key);
            }
            if (!checkMatchLeft(T2, x)) {
                insert(&T2, x);
            }
        }
        else {
            if (!checkMatchLeft(T2, x)) {
                insert(&T2, x);
            }
        }
        return T2;
    }
    if (!T2->left && !T2->right) {
        if (T2->key != x) {
            if (!checkMatchRight(T1, T2->key)) {
                insert(&T1, T2->key);
            }
            if (!checkMatchRight(T1, x)) {
                insert(&T1, x);
            }
        }
        else {
            if (!checkMatchRight(T1, x)) {
                insert(&T1, x);
            }
        }
        return T1;
    }

    int bh1 = blackHeight(T1);
    int bh2 = blackHeight(T2);

   

    if (bh1 == bh2) {
        Node* newNode = createNode(x, BLACK);
        newNode->right = T2;
        newNode->left = T1;
        T1->parent = newNode;
        T2->parent = newNode;

        *root = newNode;

        return *root;
    }

    if (bh1 > bh2) {
        

        Node* y = findBlHeightRight(T1, bh2);

        

        Node* newNode = createNode(x, RED);
        newNode->right = T2;
        newNode->left = y;
        newNode->parent = y->parent;
        y->parent->right = newNode;
        y->parent = newNode;
        T2->parent = newNode;

        *root = T1;

        insertFixup(root, newNode);
        return *root;
    }
    else {
        Node* y = findBlHeightLeft(T2, bh1);

        Node* newNode = createNode(x, RED);
        newNode->right = y;
        newNode->left = T1;
        newNode->parent = y->parent;
        y->parent->left = newNode;
        y->parent = newNode;
        T1->parent = newNode;

        *root = T2;

        insertFixup(root, newNode);
        return *root;
    }
}

void inorderTraversal(Node* root) {
    if (!root)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->key);
    printf("bh=%d ", blackHeight(root));
    printf("color=%d\n", root->color);
    inorderTraversal(root->right);
}

void test_black_height_balanced_tree() {
    Node* root = createNode(10, BLACK);
    root->left = createNode(5, RED);
    root->right = createNode(15, BLACK);
    root->left->parent = root;
    root->right->parent = root;
    assert(blackHeight(root) == 2);
    printf("test_black_height_balanced_tree passed\n");
}

void test_find_black_height_right() {
    Node* root = createNode(10, BLACK);
    root->right = createNode(20, RED);
    root->right->right = createNode(30, BLACK);
    root->right->parent = root;
    root->right->right->parent = root->right;

    Node* result = findBlHeightRight(root, blackHeight(root));
    assert(result != NULL && result->key == 30);
    printf("test_find_black_height_right passed\n");
}

void test_find_black_height_left() {
    Node* root = createNode(30, BLACK);
    root->left = createNode(20, RED);
    root->left->left = createNode(10, BLACK);
    root->left->parent = root;
    root->left->left->parent = root->left;

    Node* result = findBlHeightLeft(root, blackHeight(root));
    assert(result != NULL && result->key == 10);
    printf("test_find_black_height_left passed\n");
}

void test_insert_fixup_colors() {
    Node* root = NULL;
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 1);
    assert(root->color == BLACK);
    assert(root->left->color == BLACK);
    assert(root->left->left->color == RED);
    printf("test_insert_fixup_colors passed\n");
}

void test_check_match_left() {
    Node* tree = createNode(10, BLACK);
    tree->left = createNode(5, RED);
    tree->left->left = createNode(2, BLACK);
    tree->left->parent = tree;
    tree->left->left->parent = tree->left;

    Node* match = checkMatchLeft(tree, 2);
    assert(match != NULL && match->key == 2);
    printf("test_check_match_left passed\n");
}

void test_check_match_right() {
    Node* tree = createNode(10, BLACK);
    tree->right = createNode(15, RED);
    tree->right->right = createNode(20, BLACK);
    tree->right->parent = tree;
    tree->right->right->parent = tree->right;

    Node* match = checkMatchRight(tree, 20);
    assert(match != NULL && match->key == 20);
    printf("test_check_match_right passed\n");
}

void test_rb_union_empty_trees() {
    Node* root = NULL;
    Node* result = rbUnion(&root, NULL, NULL, 50);
    assert(result != NULL && result->key == 50 && result->color == BLACK);
    printf("test_rb_union_empty_trees passed\n");
}

void test_rb_union_one_empty_tree() {
    Node* T1 = createNode(10, BLACK);
    Node* root = NULL;
    Node* result = rbUnion(&root, T1, NULL, 20);
    Node* node = checkMatchRight(result, 20);
    assert(node != NULL && node->key == 20);
    printf("test_rb_union_one_empty_tree passed\n");
}

void test_rb_union_equal_black_height() {
    Node* T1 = createNode(5, BLACK);
    T1->right = createNode(8, RED);
    T1->right->parent = T1;

    Node* T2 = createNode(15, BLACK);
    T2->left = createNode(12, RED);
    T2->left->parent = T2;

    Node* root = NULL;
    Node* result = rbUnion(&root, T1, T2, 10);
    assert(result != NULL && result->key == 10 && result->color == BLACK);
    printf("test_rb_union_equal_black_height passed\n");
}

void printTree(Node* root, int level) {
    if (root == NULL) {
        return;
    }

    
    printTree(root->right, level + 1);

   
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    
    if (level == 0) {
        printf("ROOT--> ");
    }
    else {
        printf("|-- ");
    }
    printf("%d (%s)\n", root->key, root->color == RED ? "RED" : "BLACK");

    
    printTree(root->left, level + 1);
}

void test_insert_single_node() {
    Node* root = NULL;
    insert(&root, 10);
    assert(root != NULL && root->key == 10 && root->color == BLACK);
    printf("test_insert_single_node passed\n");
}

int main() {
    test_insert_single_node();
    test_black_height_balanced_tree();
    test_find_black_height_right();
    test_find_black_height_left();
    test_insert_fixup_colors();
    test_check_match_left();
    test_check_match_right();
    test_rb_union_empty_trees();
    test_rb_union_one_empty_tree();
    test_rb_union_equal_black_height();

    printf("All tests passed successfully.\n");

    return 0;
}