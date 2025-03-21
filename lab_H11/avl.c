#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int key;          
    int value;        
    int height;       
    int size;        
    struct Node* left;
    struct Node* right;
} Node;


void fillArrayInOrder(Node* root, int* keys, int* values, int* index);
Node* buildBalancedTree(int* keys, int* values, int start, int end);


int height(Node* node) {
    return node ? node->height : 0;
}


int size(Node* node) {
    return node ? node->size : 0;
}


int maxv(int a, int b) {
    return (a > b) ? a : b;
}



Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->key = key;
        newNode->value = value;
        newNode->height = 1;
        newNode->size = 1;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}


int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}


void updateHeightAndSize(Node* node) {
    if (node) {
        node->height = maxv(height(node->left), height(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
    }
}


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;

    
    updateHeightAndSize(y);
    updateHeightAndSize(x);

    return x;
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    updateHeightAndSize(x);
    updateHeightAndSize(y);

    return y;
}


Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}


Node* findKthElement(Node* root, int k) {
    if (root == NULL)
        return NULL;

    int leftSize = size(root->left);

    if (k == leftSize + 1)
        return root;
    else if (k <= leftSize)
        return findKthElement(root->left, k);
    else
        return findKthElement(root->right, k - leftSize - 1);
}


Node* insertByKey(Node* node, int key, int value) {
    
    if (node == NULL)
        return createNode(key, value);

    if (key < node->key)
        node->left = insertByKey(node->left, key, value);
    else if (key > node->key)
        node->right = insertByKey(node->right, key, value);
    else {
        node->value = value;
        return node;
    }

    updateHeightAndSize(node);

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* insertAtPosition(Node* root, int k, int key, int value) {
    if (k < 1 || k > size(root) + 1) {
        printf("Недопустимая позиция для вставки\n");
        return root;
    }

    Node* prev = k > 1 ? findKthElement(root, k - 1) : NULL;
   
    Node* next = k <= size(root) ? findKthElement(root, k) : NULL;
    
    int newKey;
    if (prev == NULL && next == NULL) {
        newKey = key; 
    } else if (prev == NULL) {
        newKey = next->key - 1;
    } else if (next == NULL) {
        newKey = prev->key + 1;
    } else {
        newKey = prev->key + (next->key - prev->key) / 2;
        
        if (newKey == prev->key) {
            newKey = key;
        }
    }

    return insertByKey(root, newKey, value);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
    }

    if (root == NULL)
        return root;

    updateHeightAndSize(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* deleteAtPosition(Node* root, int k) {
    if (k < 1 || k > size(root)) {
        printf("Недопустимая позиция для удаления\n");
        return root;
    }

    Node* nodeToDelete = findKthElement(root, k);
    if (nodeToDelete == NULL)
        return root;

    return deleteNode(root, nodeToDelete->key);
}

Node* mergeTrees(Node* root1, Node* root2) {
    if (root1 == NULL) return root2;
    if (root2 == NULL) return root1;
   
    int size1 = size(root1);
    int size2 = size(root2);
    int totalSize = size1 + size2;
   
    int* keys = (int*)malloc(totalSize * sizeof(int));
    int* values = (int*)malloc(totalSize * sizeof(int));
    
    int index = 0;
    fillArrayInOrder(root1, keys, values, &index);
    
    fillArrayInOrder(root2, keys, values, &index);
    
    for (int i = 0; i < totalSize - 1; i++) {
        for (int j = 0; j < totalSize - i - 1; j++) {
            if (keys[j] > keys[j+1]) {
               
                int tempKey = keys[j];
                keys[j] = keys[j+1];
                keys[j+1] = tempKey;
                
                int tempValue = values[j];
                values[j] = values[j+1];
                values[j+1] = tempValue;
            }
        }
    }
    
    int uniqueCount = totalSize > 0 ? 1 : 0;
    for (int i = 1; i < totalSize; i++) {
        if (keys[i] != keys[uniqueCount-1]) {
            keys[uniqueCount] = keys[i];
            values[uniqueCount] = values[i];
            uniqueCount++;
        } else {
            values[uniqueCount-1] = values[i];
        }
    }
    
    Node* result = buildBalancedTree(keys, values, 0, uniqueCount - 1);
    
    free(keys);
    free(values);
    
    return result;
}

void fillArrayInOrder(Node* root, int* keys, int* values, int* index) {
    if (root == NULL) return;
    
    fillArrayInOrder(root->left, keys, values, index);
    
    keys[*index] = root->key;
    values[*index] = root->value;
    (*index)++;
    
    fillArrayInOrder(root->right, keys, values, index);
}

Node* buildBalancedTree(int* keys, int* values, int start, int end) {
    if (start > end) return NULL;
    
    int mid = start + (end - start) / 2;
    
    Node* root = createNode(keys[mid], values[mid]);
    
    root->left = buildBalancedTree(keys, values, start, mid - 1);
    root->right = buildBalancedTree(keys, values, mid + 1, end);
    
    updateHeightAndSize(root);
    
    return root;
}


void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Тесты 

// Тест 1
void createNode_NewNode_returnValidVal() {
    Node* node = createNode(5, 50);
    
    assert(node != NULL);
    assert(node->key == 5);
    assert(node->value == 50);
    assert(node->height == 1);
    assert(node->size == 1);
    assert(node->left == NULL);
    assert(node->right == NULL);
    
    free(node);
}

// Тест 2
void search_ExistingKey_returnValidVal() {
    Node* root = createNode(10, 100);
   
    Node* result = search(root, 10);
    
    assert(result != NULL);
    assert(result->key == 10);
    assert(result->value == 100);
    
    free(root);
}

// Тест 3
void search_NonExistingKey_returnNull() {
    Node* root = createNode(10, 100);
   
    Node* result = search(root, 20);
    
    assert(result == NULL);
    
    free(root);
}

// Тест 4
void insertByKey_EmptyTree_returnValidVal() {
    Node* root = NULL;
    root = insertByKey(root, 10, 100);
    
    assert(root != NULL);
    assert(root->key == 10);
    assert(root->value == 100);
    assert(root->height == 1);
    assert(root->size == 1);
    
    free(root);
}

// Тест 5
void rightRotate_LeftHeavyTree_returnBalancedTree() {
    Node* z = createNode(30, 300);
    Node* y = createNode(20, 200);
    Node* x = createNode(10, 100);
    
    z->left = y;
    y->left = x;
    
    updateHeightAndSize(y);
    updateHeightAndSize(z);
 
    Node* newRoot = rightRotate(z);
    
    assert(newRoot == y);
    assert(newRoot->key == 20);
    assert(newRoot->left == x);
    assert(newRoot->right == z);
    assert(z->left == NULL);
   
    assert(newRoot->height == 2);
    assert(newRoot->size == 3);
    assert(x->height == 1);
    assert(x->size == 1);
    assert(z->height == 1);
    assert(z->size == 1);
   
    free(x);
    free(z);
    free(y);
}

// Тест 6
void findKthElement_ValidPosition_returnValidVal() {
    Node* root = NULL;
    root = insertByKey(root, 20, 200);
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    Node* result = findKthElement(root, 2);
    
    assert(result != NULL);
    assert(result->key == 20);
    assert(result->value == 200);
    
    freeTree(root);
}

// Тест 7
void deleteNode_LeafNode_returnValidTree() {
    Node* root = NULL;
    root = insertByKey(root, 20, 200);
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    root = deleteNode(root, 10);
    
    assert(root != NULL);
    assert(root->key == 20);
    assert(root->size == 2);
    assert(root->left == NULL);
    assert(root->right != NULL);
    assert(root->right->key == 30);
    
    freeTree(root);
}

// Тест 8
void insertAtPosition_MiddlePosition_returnValidTree() {
    Node* root = NULL;
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    root = insertAtPosition(root, 2, 20, 200);
    
    assert(root != NULL);
    assert(root->size == 3);
    
    Node* middle = findKthElement(root, 2);
    assert(middle != NULL);
    assert(middle->value == 200);
    
    freeTree(root);
}

// Тест 9
void deleteAtPosition_MiddlePosition_returnValidTree() {
    Node* root = NULL;
    root = insertByKey(root, 20, 200);
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    root = deleteAtPosition(root, 2);
    
    assert(root != NULL);
    assert(root->size == 2);
    
    Node* first = findKthElement(root, 1);
    Node* second = findKthElement(root, 2);
    assert(first != NULL);
    assert(second != NULL);
    assert(first->key == 10);
    assert(second->key == 30);
    
    freeTree(root);
}

// Тест 10
void mergeTrees_TwoNonEmptyTrees_returnValidTree() {
    Node* root1 = NULL;
    root1 = insertByKey(root1, 10, 100);
    root1 = insertByKey(root1, 30, 300);
    
    Node* root2 = NULL;
    root2 = insertByKey(root2, 20, 200);
    root2 = insertByKey(root2, 40, 400);
    
    Node* merged = mergeTrees(root1, root2);
    
    assert(merged != NULL);
    assert(merged->size == 4);
    
    Node* first = findKthElement(merged, 1);
    Node* second = findKthElement(merged, 2);
    Node* third = findKthElement(merged, 3);
    Node* fourth = findKthElement(merged, 4);
    
    assert(first->key == 10);
    assert(second->key == 20);
    assert(third->key == 30);
    assert(fourth->key == 40);
    
    freeTree(root1);
    freeTree(root2);
    freeTree(merged);
}

int main() {
    
    createNode_NewNode_returnValidVal();
    search_ExistingKey_returnValidVal();
    search_NonExistingKey_returnNull();
    insertByKey_EmptyTree_returnValidVal();
    rightRotate_LeftHeavyTree_returnBalancedTree();
    findKthElement_ValidPosition_returnValidVal();
    deleteNode_LeafNode_returnValidTree();
    insertAtPosition_MiddlePosition_returnValidTree();
    deleteAtPosition_MiddlePosition_returnValidTree();
    mergeTrees_TwoNonEmptyTrees_returnValidTree();
    
    printf("ok");
    return 0;
}
