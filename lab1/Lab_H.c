#include <stdio.h>
#include <stdlib.h>

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
            result = current; // Çàïîìèíàåì ìàêñèìóì
        }

        current = current->right;
        i++;
    }
    return result;
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
            result = current; // Çàïîìèíàåì ìàêñèìóì
        }

        current = current->left;
        i++;
    }
    return result;
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

    // Chekking matches

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
        // Node* temp = T1;
        // T1 = T2;
        // T2 = temp;

        // int tempBh = bh1;
        // bh1 = bh2;
        // bh2 = tempBh;

        Node* y = findBlHeightRight(T1, bh2);

        /*Node* match = checkMatchLeft(T2, x);
        if (match) {
            T2->parent = y->parent;
            T2->
        }*/

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

void printTree(Node* root, int level) {
    if (root == NULL) {
        return;
    }

    // Ñíà÷àëà âûâîäèì ïðàâîå ïîääåðåâî (äëÿ îòîáðàæåíèÿ ñïðàâà íàëåâî)
    printTree(root->right, level + 1);

    // Ïå÷àòàåì îòñòóïû äëÿ òåêóùåãî óðîâíÿ
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Ïå÷àòàåì ñàì óçåë
    if (level == 0) {
        printf("ROOT--> ");
    }
    else {
        printf("|-- ");
    }
    printf("%d (%s)\n", root->key, root->color == RED ? "RED" : "BLACK");

    // Òåïåðü âûâîäèì ëåâîå ïîääåðåâî
    printTree(root->left, level + 1);
}

// void test() {
//     Node* T1 = createNode(10, BLACK);
//     T1->right = createNode(20, RED);
//     T1->right->parent = T1;
//
//     Node* T2 = createNode(30, BLACK);
//     T2->right = createNode(40, RED);
//     T2->right->parent = T2;
//
//     printf("Black Height T1: %d\n", blackHeight(T1));
//     printf("Black Height T2: %d\n", blackHeight(T2));
//
//     Node* maxNode = findMaxBlackHeight(T1, blackHeight(T1));
//     printf("Max node in T1 with required black height: %d\n", maxNode->key);
//
//     Node* root = NULL;
//     root = rbUnion(&root, T1, T2, 25);
//
//     printf("Inorder traversal of resulting tree: ");
//     inorderTraversal(root);
//     printf("\n");
// }

//int main() {
//    Node* T1 = createNode(10, BLACK);
//    T1->right = createNode(20, RED);
//    T1->right->parent = T1;
//    T1->left = createNode(5, BLACK);
//    T1->left->parent = T1;
//    T1->right->right = createNode(21, BLACK);
//    T1->right->right->parent = T1->right;
//    T1->left->right = createNode(8, RED);
//    T1->left->right->parent = T1->left;
//
//    /*Node* T2 = createNode(30, BLACK);
//    T2->right = createNode(40, RED);
//    T2->right->parent = T2;
//
//    Node* root = NULL;
//    root = rbUnion(&root, T1, T2, 25);*/
//
//    insert(&T1, 25);
//
//    printf("Inorder traversal of resulting tree: ");
//    printf("\n");
//    inorderTraversal(T1);
//    printf("\n");
//
//    // printTree(root, 0);
//
//    return 0;
//}