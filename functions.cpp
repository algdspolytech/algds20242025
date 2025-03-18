#include "tests.h"
#include "functions.h"

BinTree* insert(BinTree* root, int value) {
    if (!root) {
        root = new BinTree{ value, nullptr, nullptr };
        return root;
    }
    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    return root;
}

void inorderTraversal(BinTree* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

BinTree* search(BinTree* root, int value) {
    if (!root || root->data == value)
        return root;
    if (value < root->data)
        return search(root->left, value);
    return search(root->right, value);
}

BinTree* findMin(BinTree* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

BinTree* remove(BinTree* root, int value) {
    if (!root) return root;
    if (value < root->data)
        root->left = remove(root->left, value);
    else if (value > root->data)
        root->right = remove(root->right, value);
    else {
        if (!root->left) {
            BinTree* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            BinTree* temp = root->left;
            delete root;
            return temp;
        }
        BinTree* temp = findMin(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data);
    }
    return root;
}

void destroyTree(BinTree* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}


int getHeight(AVLTree* node) {
    return node ? node->height : 0;
}

int getBalanceFactor(AVLTree* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLTree* rotateRight(AVLTree* y) {
    AVLTree* x = y->left;
    AVLTree* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLTree* rotateLeft(AVLTree* x) {
    AVLTree* y = x->right;
    AVLTree* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLTree* rotateLeftRight(AVLTree* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVLTree* rotateRightLeft(AVLTree* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

AVLTree* insert(AVLTree* root, int value) {
    if (!root) return new AVLTree{ value, 1, nullptr, nullptr };
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else return root;
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalanceFactor(root);
    if (balance > 1 && value < root->left->data)
        return rotateRight(root);
    if (balance < -1 && value > root->right->data)
        return rotateLeft(root);
    if (balance > 1 && value > root->left->data)
        return rotateLeftRight(root);
    if (balance < -1 && value < root->right->data)
        return rotateRightLeft(root);

    return root;
}

AVLTree* remove(AVLTree* root, int value) {
    if (!root) return root;
    if (value < root->data)
        root->left = remove(root->left, value);
    else if (value > root->data)
        root->right = remove(root->right, value);
    else {
        if (!root->left || !root->right) {
            AVLTree* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            }
            else *root = *temp;
            delete temp;
        }
        else {
            AVLTree* temp = root->right;
            while (temp->left) temp = temp->left;
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    if (!root) return root;
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0)
        return rotateLeftRight(root);
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0)
        return rotateRightLeft(root);
    return root;
}

void inorderTraversal(AVLTree* root) {
    if (!root) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

AVLTree* search(AVLTree* root, int value) {
    if (root == nullptr || root->data == value)
        return root;
    if (value < root->data)
        return search(root->left, value);
    return search(root->right, value);
}

void testBinaryTree(int cnt) {
    BinTree* root = nullptr;
    auto start_insert = high_resolution_clock::now();
    for (int i = 1; i <= cnt; ++i) {
        root = insert(root, i);
    }
    auto stop_insert = high_resolution_clock::now();
    auto duration_insert = duration_cast<microseconds>(stop_insert - start_insert);
    auto start_search = high_resolution_clock::now();
    for (int i = 1; i <= cnt; ++i) {
        search(root, i);
    }
    auto stop_search = high_resolution_clock::now();
    auto duration_search = duration_cast<microseconds>(stop_search - start_search);
    auto start_remove = high_resolution_clock::now();
    for (int i = 1; i <= cnt; ++i) {
        root = remove(root, i);
    }
    auto stop_remove = high_resolution_clock::now();
    auto duration_remove = duration_cast<microseconds>(stop_remove - start_remove);
    cout << "Binary Tree Insert Time: " << duration_insert.count() << " microseconds" << endl;
    cout << "Binary Tree Remove Time: " << duration_remove.count() << " microseconds" << endl;
    cout << "Binary Tree Search Time: " << duration_search.count() << " microseconds" << endl;
}

void testAVLTree(int cnt) {
    AVLTree* rootAVL = nullptr;
    auto start_insert = high_resolution_clock::now();
    for (int i = 1; i <= cnt; ++i) {
        rootAVL = insert(rootAVL, i);
    }
    auto stop_insert = high_resolution_clock::now();
    auto duration_insert = duration_cast<microseconds>(stop_insert - start_insert);
    auto start_search = high_resolution_clock::now();
    for (int i = 1; i <= cnt; ++i) {
        search(rootAVL, i);
    }
    auto stop_search = high_resolution_clock::now();
    auto duration_search = duration_cast<microseconds>(stop_search - start_search);
    auto start_remove = high_resolution_clock::now();
    for (int i = 1; i <= cnt; ++i) {
        rootAVL = remove(rootAVL, i);
    }
    auto stop_remove = high_resolution_clock::now();
    auto duration_remove = duration_cast<microseconds>(stop_remove - start_remove);
    cout << "AVL Tree Insert Time: " << duration_insert.count() << " microseconds" << endl;
    cout << "AVL Tree Remove Time: " << duration_remove.count() << " microseconds" << endl;
    cout << "AVL Tree Search Time: " << duration_search.count() << " microseconds" << endl;
}