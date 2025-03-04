#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#include "AVL.h"


// Функция создания нового узла.
Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1; // Лист имеет высоту 1.
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

// Возвращает высоту узла (0, если узел равен NULL).
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Возвращает размер поддерева (0, если узел равен NULL).
int getSize(Node* node) {
    return node ? node->size : 0;
}

// Обновление высоты и размера узла на основе его потомков.
void update(Node* node) {
    if (node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }
}

// Правый поворот вокруг узла y.
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

// Левый поворот вокруг узла x.
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

// Получение балансирующего фактора узла.
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Балансировка узла AVL-дерева.
Node* balance(Node* node) {
    if (!node) return node;
    update(node);
    int b = getBalance(node);
    if (b > 1) {
        if (getBalance(node->left) < 0)
            node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (b < -1) {
        if (getBalance(node->right) > 0)
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

/*
  Поиск k-го элемента в списке (1-based нумерация).
  Использует поле size, что позволяет за O(log n) находить нужный узел.
*/
Node* find_kth(Node* root, int k) {
    if (!root || k <= 0 || k > getSize(root))
        return NULL;
    int leftSize = getSize(root->left);
    if (k == leftSize + 1)
        return root;
    else if (k <= leftSize)
        return find_kth(root->left, k);
    else
        return find_kth(root->right, k - leftSize - 1);
}

/*
  Поиск элемента по значению key.
  Так как дерево не упорядочено по значению, поиск выполняется полным обходом – O(n).
*/
Node* search_by_key(Node* root, int key) {
    if (!root)
        return NULL;
    if (root->key == key)
        return root;
    Node* found = search_by_key(root->left, key);
    if (found)
        return found;
    return search_by_key(root->right, key);
}

/*
  Вставка элемента со значением key в позицию pos (0-based индекс).
  Благодаря полю size операция выполняется за O(log n).
*/
Node* insert_at(Node* root, int pos, int key) {
    if (!root)
        return create_node(key);
    int leftSize = getSize(root->left);
    if (pos <= leftSize)
        root->left = insert_at(root->left, pos, key);
    else
        root->right = insert_at(root->right, pos - leftSize - 1, key);
    return balance(root);
}

/*
  Удаление элемента, занимающего позицию pos (0-based индекс).
  Операция выполняется за O(log n).
*/
Node* delete_at(Node* root, int pos) {
    if (!root)
        return NULL;
    int leftSize = getSize(root->left);
    if (pos < leftSize) {
        root->left = delete_at(root->left, pos);
    }
    else if (pos > leftSize) {
        root->right = delete_at(root->right, pos - leftSize - 1);
    }
    else {
        // Удаляем текущий узел.
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else {
            // Находим минимальный узел в правом поддереве (in-order преемник).
            Node* temp = root->right;
            while (temp->left)
                temp = temp->left;
            root->key = temp->key;
            // Удаляем преемника.
            root->right = delete_at(root->right, 0);
        }
    }
    return balance(root);
}

/*
  Функция extract_max извлекает (удаляет) максимальный элемент (правый крайний узел)
  из дерева и передает его через параметр max_node.
*/
Node* extract_max(Node* root, Node** max_node) {
    if (!root->right) {
        *max_node = root;
        return root->left;
    }
    else {
        root->right = extract_max(root->right, max_node);
        return balance(root);
    }
}

/*
  Операция сцепления двух списков, представленных AVL-деревьями.
  Предполагается, что все элементы первого списка идут перед элементами второго.
  Сложность: O(log n)
*/
Node* join_trees(Node* t1, Node* t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    if (getHeight(t1) > getHeight(t2) + 1) {
        t1->right = join_trees(t1->right, t2);
        return balance(t1);
    }
    else if (getHeight(t2) > getHeight(t1) + 1) {
        t2->left = join_trees(t1, t2->left);
        return balance(t2);
    }
    else {
        Node* max = NULL;
        t1 = extract_max(t1, &max);
        max->left = t1;
        max->right = t2;
        return balance(max);
    }
}

// Функция in-order обхода для вывода элементов дерева в виде списка.
void inorder_print(Node* root) {
    if (!root) return;
    inorder_print(root->left);
    printf("%d ", root->key);
    inorder_print(root->right);
}

int main(void) {
    setlocale(LC_CTYPE, "Russian");
    Node* list = NULL;

    // Вставляем элементы в список.
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 2, 30);
    list = insert_at(list, 1, 15); // Вставляем 15 на позицию 1.

    printf("Список после вставок (inorder): ");
    inorder_print(list);
    printf("\n");

    // Поиск 3-го элемента (1-based нумерация).
    Node* kth = find_kth(list, 3);
    if (kth)
        printf("3-й элемент: %d\n", kth->key);

    // Поиск элемента по значению.
    Node* found = search_by_key(list, 20);
    if (found)
        printf("Элемент со значением 20 найден.\n");

    // Удаляем второй элемент (позиция 1, 0-based).
    list = delete_at(list, 1);
    printf("Список после удаления второго элемента: ");
    inorder_print(list);
    printf("\n");

    // Создаем второй список.
    Node* list2 = NULL;
    list2 = insert_at(list2, 0, 40);
    list2 = insert_at(list2, 1, 50);

    // Сцепляем два списка: элементы первого списка идут перед элементами второго.
    Node* joined = join_trees(list, list2);
    printf("Сцеплённый список: ");
    inorder_print(joined);
    printf("\n");

    return 0;
}
