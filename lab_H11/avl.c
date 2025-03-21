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

    // Обновление высоты и размера
    updateHeightAndSize(y);
    updateHeightAndSize(x);

    return x;
}

// Левый поворот
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Выполнение поворота
    y->left = x;
    x->right = T2;

    // Обновление высоты и размера
    updateHeightAndSize(x);
    updateHeightAndSize(y);

    return y;
}

// Поиск узла по ключу
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Поиск k-го элемента в отсортированном порядке
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

// Вставка нового узла в дерево по ключу
Node* insertByKey(Node* node, int key, int value) {
    // Стандартная вставка в BST
    if (node == NULL)
        return createNode(key, value);

    if (key < node->key)
        node->left = insertByKey(node->left, key, value);
    else if (key > node->key)
        node->right = insertByKey(node->right, key, value);
    else {
        // Ключ уже существует, обновляем значение
        node->value = value;
        return node;
    }

    // Обновление высоты и размера текущего узла
    updateHeightAndSize(node);

    // Получение баланс-фактора для проверки балансировки
    int balance = getBalance(node);

    // Случаи несбалансированности
    // Левый-левый случай
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Правый-правый случай
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Левый-правый случай
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Правый-левый случай
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Вставка элемента на позицию k
Node* insertAtPosition(Node* root, int k, int key, int value) {
    if (k < 1 || k > size(root) + 1) {
        printf("Недопустимая позиция для вставки\n");
        return root;
    }

    // Находим узел на позиции k-1
    Node* prev = k > 1 ? findKthElement(root, k - 1) : NULL;
    
    // Находим узел на позиции k
    Node* next = k <= size(root) ? findKthElement(root, k) : NULL;
    
    // Выбираем ключ для нового узла, который будет между prev и next
    int newKey;
    if (prev == NULL && next == NULL) {
        newKey = key; // первый узел в дереве
    } else if (prev == NULL) {
        newKey = next->key - 1;
    } else if (next == NULL) {
        newKey = prev->key + 1;
    } else {
        newKey = prev->key + (next->key - prev->key) / 2;
        
        // Если не можем найти промежуточный ключ, нужно перебалансировать ключи
        if (newKey == prev->key) {
            // В реальном случае здесь должна быть перебалансировка ключей,
            // но для простоты примера используем переданный ключ
            newKey = key;
        }
    }

    // Вставляем новый узел
    return insertByKey(root, newKey, value);
}

// Найти узел с минимальным ключом
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Удаление узла с заданным ключом
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    // Стандартное удаление из BST
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Узел с одним или без дочерних узлов
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Узел с двумя дочерними узлами
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
    }

    // Если дерево имеет только один узел
    if (root == NULL)
        return root;

    // Обновление высоты и размера
    updateHeightAndSize(root);

    // Проверка баланса
    int balance = getBalance(root);

    // Случаи несбалансированности
    // Левый-левый случай
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Левый-правый случай
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Правый-правый случай
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Правый-левый случай
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Удаление элемента по позиции
Node* deleteAtPosition(Node* root, int k) {
    if (k < 1 || k > size(root)) {
        printf("Недопустимая позиция для удаления\n");
        return root;
    }

    // Находим узел для удаления
    Node* nodeToDelete = findKthElement(root, k);
    if (nodeToDelete == NULL)
        return root;

    // Удаляем узел по ключу
    return deleteNode(root, nodeToDelete->key);
}

// Слияние двух деревьев
Node* mergeTrees(Node* root1, Node* root2) {
    if (root1 == NULL) return root2;
    if (root2 == NULL) return root1;
    
    // Преобразуем оба дерева в отсортированные массивы
    int size1 = size(root1);
    int size2 = size(root2);
    int totalSize = size1 + size2;
    
    // Создаем массивы для хранения ключей и значений
    int* keys = (int*)malloc(totalSize * sizeof(int));
    int* values = (int*)malloc(totalSize * sizeof(int));
    
    // Заполняем массивы из первого дерева
    int index = 0;
    fillArrayInOrder(root1, keys, values, &index);
    
    // Заполняем массивы из второго дерева
    fillArrayInOrder(root2, keys, values, &index);
    
    // Сортируем массивы по ключам
    for (int i = 0; i < totalSize - 1; i++) {
        for (int j = 0; j < totalSize - i - 1; j++) {
            if (keys[j] > keys[j+1]) {
                // Обмен ключами
                int tempKey = keys[j];
                keys[j] = keys[j+1];
                keys[j+1] = tempKey;
                
                // Обмен значениями
                int tempValue = values[j];
                values[j] = values[j+1];
                values[j+1] = tempValue;
            }
        }
    }
    
    // Удаляем дубликаты ключей (оставляем последнее значение для каждого ключа)
    int uniqueCount = totalSize > 0 ? 1 : 0;
    for (int i = 1; i < totalSize; i++) {
        if (keys[i] != keys[uniqueCount-1]) {
            keys[uniqueCount] = keys[i];
            values[uniqueCount] = values[i];
            uniqueCount++;
        } else {
            // Если ключ дубликат, обновляем значение
            values[uniqueCount-1] = values[i];
        }
    }
    
    // Создаем новое сбалансированное дерево из отсортированного массива
    Node* result = buildBalancedTree(keys, values, 0, uniqueCount - 1);
    
    // Освобождаем память
    free(keys);
    free(values);
    
    return result;
}

// Заполнить массив ключами и значениями из дерева в порядке возрастания
void fillArrayInOrder(Node* root, int* keys, int* values, int* index) {
    if (root == NULL) return;
    
    fillArrayInOrder(root->left, keys, values, index);
    
    keys[*index] = root->key;
    values[*index] = root->value;
    (*index)++;
    
    fillArrayInOrder(root->right, keys, values, index);
}

// Создание сбалансированного дерева из отсортированного массива
Node* buildBalancedTree(int* keys, int* values, int start, int end) {
    if (start > end) return NULL;
    
    int mid = start + (end - start) / 2;
    
    // Создаем корень с средним элементом
    Node* root = createNode(keys[mid], values[mid]);
    
    // Рекурсивно строим левое и правое поддеревья
    root->left = buildBalancedTree(keys, values, start, mid - 1);
    root->right = buildBalancedTree(keys, values, mid + 1, end);
    
    // Обновляем высоту и размер
    updateHeightAndSize(root);
    
    return root;
}

// Печать дерева в порядке обхода (для тестирования)
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Ключ: %d, Значение: %d (Размер: %d)\n", root->key, root->value, root->size);
        inOrder(root->right);
    }
}

// Освобождение памяти, занятой деревом
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}




// Тесты для AVL-дерева

// Тест 1
void createNode_NewNode_returnValidVal() {
    // Создаём новый узел
    Node* node = createNode(5, 50);
    
    // Проверяем, что узел создан правильно
    assert(node != NULL);
    assert(node->key == 5);
    assert(node->value == 50);
    assert(node->height == 1);
    assert(node->size == 1);
    assert(node->left == NULL);
    assert(node->right == NULL);
    
    free(node);
    printf("createNode_NewNode_returnValidVal: PASSED\n");
}

// Тест 2
void search_ExistingKey_returnValidVal() {
    // Создаём дерево с одним узлом
    Node* root = createNode(10, 100);
    
    // Ищем существующий ключ
    Node* result = search(root, 10);
    
    // Проверяем результат
    assert(result != NULL);
    assert(result->key == 10);
    assert(result->value == 100);
    
    free(root);
    printf("search_ExistingKey_returnValidVal: PASSED\n");
}

// Тест 3
void search_NonExistingKey_returnNull() {
    // Создаём дерево с одним узлом
    Node* root = createNode(10, 100);
    
    // Ищем несуществующий ключ
    Node* result = search(root, 20);
    
    // Проверяем результат
    assert(result == NULL);
    
    free(root);
    printf("search_NonExistingKey_returnNull: PASSED\n");
}

// Тест 4
void insertByKey_EmptyTree_returnValidVal() {
    // Вставляем узел в пустое дерево
    Node* root = NULL;
    root = insertByKey(root, 10, 100);
    
    // Проверяем результат
    assert(root != NULL);
    assert(root->key == 10);
    assert(root->value == 100);
    assert(root->height == 1);
    assert(root->size == 1);
    
    free(root);
    printf("insertByKey_EmptyTree_returnValidVal: PASSED\n");
}

// Тест 5
void rightRotate_LeftHeavyTree_returnBalancedTree() {
    // Создаём левонаклонённое дерево
    Node* z = createNode(30, 300);
    Node* y = createNode(20, 200);
    Node* x = createNode(10, 100);
    
    z->left = y;
    y->left = x;
    
    updateHeightAndSize(y);
    updateHeightAndSize(z);
    
    // Выполняем правый поворот
    Node* newRoot = rightRotate(z);
    
    // Проверяем новую структуру дерева
    assert(newRoot == y);
    assert(newRoot->key == 20);
    assert(newRoot->left == x);
    assert(newRoot->right == z);
    assert(z->left == NULL);
    
    // Проверяем высоты и размеры
    assert(newRoot->height == 2);
    assert(newRoot->size == 3);
    assert(x->height == 1);
    assert(x->size == 1);
    assert(z->height == 1);
    assert(z->size == 1);
    
    // Освобождаем память
    free(x);
    free(z);
    free(y);
    printf("rightRotate_LeftHeavyTree_returnBalancedTree: PASSED\n");
}

// Тест 6
void findKthElement_ValidPosition_returnValidVal() {
    // Создаем дерево из 3 элементов
    Node* root = NULL;
    root = insertByKey(root, 20, 200);
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    // Находим 2-й элемент (корень)
    Node* result = findKthElement(root, 2);
    
    // Проверяем результат
    assert(result != NULL);
    assert(result->key == 20);
    assert(result->value == 200);
    
    // Освобождаем память
    freeTree(root);
    printf("findKthElement_ValidPosition_returnValidVal: PASSED\n");
}

// Тест 7
void deleteNode_LeafNode_returnValidTree() {
    // Создаем дерево из 3 элементов
    Node* root = NULL;
    root = insertByKey(root, 20, 200);
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    // Удаляем листовой узел
    root = deleteNode(root, 10);
    
    // Проверяем результат
    assert(root != NULL);
    assert(root->key == 20);
    assert(root->size == 2);
    assert(root->left == NULL);
    assert(root->right != NULL);
    assert(root->right->key == 30);
    
    // Освобождаем память
    freeTree(root);
    printf("deleteNode_LeafNode_returnValidTree: PASSED\n");
}

// Тест 8
void insertAtPosition_MiddlePosition_returnValidTree() {
    // Создаем дерево из 2 элементов
    Node* root = NULL;
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    // Вставляем элемент посередине
    root = insertAtPosition(root, 2, 20, 200);
    
    // Проверяем результат
    assert(root != NULL);
    assert(root->size == 3);
    
    // Находим вставленный элемент
    Node* middle = findKthElement(root, 2);
    assert(middle != NULL);
    assert(middle->value == 200);
    
    // Освобождаем память
    freeTree(root);
    printf("insertAtPosition_MiddlePosition_returnValidTree: PASSED\n");
}

// Тест 9
void deleteAtPosition_MiddlePosition_returnValidTree() {
    // Создаем дерево из 3 элементов
    Node* root = NULL;
    root = insertByKey(root, 20, 200);
    root = insertByKey(root, 10, 100);
    root = insertByKey(root, 30, 300);
    
    // Удаляем средний элемент (корень)
    root = deleteAtPosition(root, 2);
    
    // Проверяем результат
    assert(root != NULL);
    assert(root->size == 2);
    
    // Проверяем, что средний элемент удален
    Node* first = findKthElement(root, 1);
    Node* second = findKthElement(root, 2);
    assert(first != NULL);
    assert(second != NULL);
    assert(first->key == 10);
    assert(second->key == 30);
    
    // Освобождаем память
    freeTree(root);
    printf("deleteAtPosition_MiddlePosition_returnValidTree: PASSED\n");
}

// Тест 10
void mergeTrees_TwoNonEmptyTrees_returnValidTree() {
    // Создаем первое дерево
    Node* root1 = NULL;
    root1 = insertByKey(root1, 10, 100);
    root1 = insertByKey(root1, 30, 300);
    
    // Создаем второе дерево
    Node* root2 = NULL;
    root2 = insertByKey(root2, 20, 200);
    root2 = insertByKey(root2, 40, 400);
    
    // Объединяем деревья
    Node* merged = mergeTrees(root1, root2);
    
    // Проверяем результат
    assert(merged != NULL);
    assert(merged->size == 4);
    
    // Проверяем порядок элементов
    Node* first = findKthElement(merged, 1);
    Node* second = findKthElement(merged, 2);
    Node* third = findKthElement(merged, 3);
    Node* fourth = findKthElement(merged, 4);
    
    assert(first->key == 10);
    assert(second->key == 20);
    assert(third->key == 30);
    assert(fourth->key == 40);
    
    // Освобождаем память
    freeTree(root1);
    freeTree(root2);
    freeTree(merged);
    printf("mergeTrees_TwoNonEmptyTrees_returnValidTree: PASSED\n");
}

// Главная функция для запуска всех тестов
int main() {
    printf("Запуск тестов для AVL-дерева\n");
    
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
    
    printf("\nВсе тесты пройдены успешно!\n");
    return 0;
}
