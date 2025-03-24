#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Функция, которая создает новый узел скошенного дерева
Node *createNode(int key) {
    Node *newNode;
    newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для правого поворота
Node *rightRotation(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Функция для левого поворота
Node *leftRotation(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Операция splay, которая перемещает узел с ключом key в корень
Node *splay(Node *root, int key) {

    // Если дерево пустое или ключ уже в корне, возвращаем корень
    if (root == NULL || root->key == key) {
        return root;
    }

    Node dummy;// фиктивный узел для упрощения кода
    dummy.left = dummy.right = NULL;
    Node *leftTreeMax = &dummy; // Максимальный элемент левого поддерева
    Node *rightTreeMin = &dummy;// Минимальный элемент правого поддерева

    while (1) {
        if (key < root->key) {
            // Если ключ меньше текущего узла, идем влево
            if (root->left == NULL) {
                break;// Ключ не найден
            }
            if (key < root->left->key) {
                // Zig-Zig (левый-левый случай)
                root = rightRotation(root);
                if (root->left == NULL) {
                    break;
                }
            }
            // Zig-Zag (левый-правый случай)
            rightTreeMin->left = root;
            rightTreeMin = root;
            root = root->left;
        } else if (key > root->key) {
            // Если ключ больше текущего узла, идем вправо
            if (root->right == NULL) {
                break;// Ключ не найден
            }
            if (key > root->right->key) {
                // Zag-Zag (правый-правый случай)
                root = leftRotation(root);
                if (root->right == NULL) {
                    break;
                }
            }
            // Zag-Zig (присоединяем текущий узел к левому поддереву
            leftTreeMax->right = root;
            leftTreeMax = root;
            root = root->right;
        } else {
            // Ключ не найден
            break;
        }
    }

    // Собираем дерево обратно
    leftTreeMax->right = root->left;
    rightTreeMin->left = root->right;
    root->left = dummy.right;
    root->right = dummy.left;

    return root;
}


// Вставка нового ключа в дерево
Node *insert(Node *root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    // Перемещаем узел с ключом key в корень
    root = splay(root, key);

    // Если ключ уже существует, возвращаем дерево
    if (root->key == key) {
        return root;
    }

    // Создаём новый узел
    Node *newNode = createNode(key);

    // Вставляем новый узел в корень
    if (root->key > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    // Возвращаем новый корень
    return newNode;
}

// Поиск ключа в дереве
Node *search(Node *root, int key) {
    return splay(root, key);
}

// Удаление ключа из дерева
Node *delete(Node *root, int key) {
    if (root == NULL) {
        return NULL;
    }

    // Перемещаем узел с ключом key в корень
    root = splay(root, key);

    // Если ключ не найден, возвращаем дерево
    if (root->key != key) {
        return root;
    }

    // Если левое поддерево пустое, возвращаем правое поддерево
    if (root->left == NULL) {
        Node *temp = root;
        root = root->right;
        free(temp);
    }
    // Иначе объединяем левое и правое поддеревья
    else {
        Node *temp = root;
        root = splay(root->left, key);// Перемещаем максимальный элемент левого поддерева в корень
        root->right = temp->right;    // Присоединяем правое поддерево
        free(temp);
    }

    // Возвращаем новый корень
    return root;
}

// Печать дерева (in-order обход)
void printTree(Node *root) {
    if (root != NULL) {
        printTree(root->left);
        printf("%d ", root->key);
        printTree(root->right);
    }
}


// Тест 1. Проверка вставки элемента в пустое дерево
void TestInsert_EmptyTree_HappyPath_no1() {
    Node *root = NULL;
    root = insert(root, 10);
    assert(root != NULL);
    assert(root->key == 10);
    assert(root->left == NULL);
    assert(root->right == NULL);
}

// Тест 2. Проверка вставки элемента, который уже существует в дереве
void TestInsert_ExistingKey_NoChange_no2() {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 10);
    assert(root->key == 10);
    assert(root->left == NULL);
    assert(root->right == NULL);
}

// Тест 3. Проверка вставки элемента в левое поддерево
void TestInsert_LeftSubtree_HappyPath_no3() {
    Node *root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    assert(root->key == 10);
    assert(root->right->key == 20);
}

// Тест 4. Проверка вставки элемента в правое поддерево
void TestInsert_RightSubtree_HappyPath_no4() {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    assert(root->key == 20);
    assert(root->left->key == 10);
}

// Тест 5. Проверка поиска существующего элемента
void TestSearch_ExistingKey_HappyPath_no5() {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = search(root, 10);
    assert(root->key == 10);
}

// Тест 6. Проверка поиска несуществующего элемента
void TestSearch_NonExistingKey_ReturnLastAccessed_no6() {
    Node *root = NULL;
    root = insert(root, 10);// Вставляем 10
    root = insert(root, 20);// Вставляем 20

    // Ищем несуществующий ключ 15
    root = search(root, 15);

    // Проверяем, что корень — это узел, ближайший к 15
    // В данном случае это может быть либо 10, либо 20, в зависимости от реализации splay
    assert(root->key == 10 || root->key == 20);
}

// Тест 7. Проверка удаления существующего элемента
void TestDelete_ExistingKey_HappyPath_no7() {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = delete (root, 10);
    assert(root->key == 20);
    assert(root->left == NULL);
}

// Тест 8. Проверка удаления несуществующего элемента
void TestDelete_NonExistingKey_NoChange_no8() {
    Node *root = NULL;
    root = insert(root, 10);// Вставляем 10
    root = insert(root, 20);// Вставляем 20

    // Удаляем несуществующий ключ 15
    root = delete (root, 15);

    // Проверяем, что корень — это узел, ближайший к 15
    // В данном случае это может быть либо 10, либо 20, в зависимости от реализации splay
    assert(root->key == 10 || root->key == 20);
}

// Тест 9. Проверка корректности структуры дерева после вставки нескольких элементов
void TestInsert_MultipleElements_StructureValid_no9() {
    Node *root = NULL;
    root = insert(root, 30);// Вставляем 30
    root = insert(root, 20);// Вставляем 20
    root = insert(root, 40);// Вставляем 40
    root = insert(root, 10);// Вставляем 10
    root = insert(root, 25);// Вставляем 25

    // Проверяем структуру дерева
    assert(root->key == 25);              // Корень после splay (последний вставленный элемент)
    assert(root->left->key == 20);        // Левый потомок корня
    assert(root->left->left->key == 10);  // Левый потомок узла 20
    assert(root->left->right == NULL);    // Правый потомок узла 20 отсутствует
    assert(root->right->key == 30);       // Правый потомок корня
    assert(root->right->left == NULL);    // Левый потомок узла 30 отсутствует
    assert(root->right->right->key == 40);// Правый потомок узла 30
}

// Тест 10. Проверка операции splay, когда ключ уже в корне
void TestSplay_RootKey_NoChange_no10() {
    Node *root = NULL;
    root = insert(root, 10);
    root = splay(root, 10);
    assert(root->key == 10);
    assert(root->left == NULL);
    assert(root->right == NULL);
}

void RunAllTests() {
    TestInsert_EmptyTree_HappyPath_no1();
    TestInsert_ExistingKey_NoChange_no2();
    TestInsert_LeftSubtree_HappyPath_no3();
    TestInsert_RightSubtree_HappyPath_no4();
    TestSearch_ExistingKey_HappyPath_no5();
    TestSearch_NonExistingKey_ReturnLastAccessed_no6();
    TestDelete_ExistingKey_HappyPath_no7();
    TestDelete_NonExistingKey_NoChange_no8();
    TestInsert_MultipleElements_StructureValid_no9();
    TestSplay_RootKey_NoChange_no10();
    printf("All tests passed successfully!\n");
}

int main() {
    RunAllTests();
    return 0;
}