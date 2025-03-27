#include <iostream>
#include <algorithm>
using namespace std;

struct ListNode {
    int value;
    int height;
    int subtreeSize;
    ListNode* left;
    ListNode* right;
};

int getHeight(ListNode* node) {
    if (node == nullptr) {
        return 0;
    }
    else {
        return node->height;
    }
}

int getSize(ListNode* node) {
    if (node == nullptr) {
        return 0;
    }
    else {
        return node->subtreeSize;
    }
}

void updateNode(ListNode* node) {
    if (node != nullptr) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + max(leftHeight, rightHeight);

        int leftSize = getSize(node->left);
        int rightSize = getSize(node->right);
        node->subtreeSize = 1 + leftSize + rightSize;
    }
}

ListNode* rotateRight(ListNode* root) {
    ListNode* pivot = root->left;
    ListNode* temp = pivot->right;

    pivot->right = root;
    root->left = temp;

    updateNode(root);
    updateNode(pivot);

    return pivot;
}

ListNode* rotateLeft(ListNode* root) {
    ListNode* pivot = root->right;
    ListNode* temp = pivot->left;

    pivot->left = root;
    root->right = temp;

    updateNode(root);
    updateNode(pivot);

    return pivot;
}

int computeBalance(ListNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

ListNode* rebalanceNode(ListNode* node) {
    updateNode(node);
    int balance = computeBalance(node);

    if (balance > 1) {
        if (computeBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (balance < -1) {
        if (computeBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

ListNode* newNode(int value) {
    ListNode* temp = new ListNode;
    temp->value = value;
    temp->height = 1;
    temp->subtreeSize = 1;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

ListNode* insertAtPosition(ListNode* root, int value, int pos) {
    if (root == nullptr) {
        return newNode(value);
    }

    int leftCount = getSize(root->left);
    if (pos <= leftCount) {
        root->left = insertAtPosition(root->left, value, pos);
    }
    else {
        root->right = insertAtPosition(root->right, value, pos - leftCount - 1);
    }

    return rebalanceNode(root);
}

ListNode* findMinNode(ListNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

ListNode* removeByValue(ListNode* root, int value) {
    if (root == nullptr) {
        return nullptr;
    }

    if (value < root->value) {
        root->left = removeByValue(root->left, value);
    }
    else if (value > root->value) {
        root->right = removeByValue(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            return root->right;
        }
        if (root->right == nullptr) {
            return root->left;
        }
        ListNode* successor = findMinNode(root->right);
        root->value = successor->value;
        root->right = removeByValue(root->right, successor->value);
    }

    return rebalanceNode(root);
}

ListNode* removeAtIndex(ListNode* root, int index) {
    if (root == nullptr) {
        return nullptr;
    }

    int leftCount = getSize(root->left);
    if (index < leftCount) {
        root->left = removeAtIndex(root->left, index);
    }
    else if (index > leftCount) {
        root->right = removeAtIndex(root->right, index - leftCount - 1);
    }
    else {
        if (root->left == nullptr) {
            return root->right;
        }
        if (root->right == nullptr) {
            return root->left;
        }
        ListNode* successor = findMinNode(root->right);
        root->value = successor->value;
        root->right = removeAtIndex(root->right, 0);
    }
    return rebalanceNode(root);
}

ListNode* getNodeByIndex(ListNode* root, int index) {
    if (root == nullptr) {
        return nullptr;
    }

    int leftCount = getSize(root->left);
    if (index < leftCount) {
        return getNodeByIndex(root->left, index);
    }
    else if (index > leftCount) {
        return getNodeByIndex(root->right, index - leftCount - 1);
    }
    else {
        return root;
    }
}

ListNode* findByKey(ListNode* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->value == key) {
        return root;
    }
    else if (key < root->value) {
        return findByKey(root->left, key);
    }
    else {
        return findByKey(root->right, key);
    }
}

ListNode* mergeTrees(ListNode* treeA, ListNode* treeB) {
    if (treeA == nullptr) {
        return treeB;
    }
    if (treeB == nullptr) {
        return treeA;
    }

    if (getHeight(treeA) > getHeight(treeB)) {
        treeA->right = mergeTrees(treeA->right, treeB);
        return rebalanceNode(treeA);
    }
    else {
        treeB->left = mergeTrees(treeA, treeB->left);
        return rebalanceNode(treeB);
    }
}

void inOrderPrint(ListNode* root) {
    if (root != nullptr) {
        inOrderPrint(root->left);
        cout << root->value << " ";
        inOrderPrint(root->right);
    }
}

void freeTree(ListNode* root) {
    if (root != nullptr) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}