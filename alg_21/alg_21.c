#include "Header.h"
#include <stdio.h>
#include <stdlib.h>


// Функция для получения размера поддерева
int get_size(struct Node* node) {
    return node ? node->size : 0;
}

// Функция для обновления размера поддерева
void update_size(struct Node* node) {
    if (node) {
        node->size = get_size(node->left) + get_size(node->right) + 1;
    }
}

// Функция для создания нового узла
struct Node* new_node(int x, int c) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));  // Выделение памяти для нового узла
    if (!node) {  // Проверка, не равен ли указатель NULL
        printf("Error allocating memory for new node.\n");
        exit(1);  // Завершаем программу с ошибкой, если не удалось выделить память
    }
    node->x = x;
    node->c = c;
    node->priority = rand();  // случайный приоритет для кучи
    node->left = node->right = NULL;
    node->size = 1;
    return node;
}

// Функция для выполнения поворота вправо
struct Node* rotate_right(struct Node* node) {
    if (!node || !node->left) return node;  // Проверка на NULL

    struct Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    update_size(node);
    update_size(new_root);
    return new_root;
}

// Функция для выполнения поворота влево
struct Node* rotate_left(struct Node* node) {
    if (!node || !node->right) return node;  // Проверка на NULL

    struct Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    update_size(node);
    update_size(new_root);
    return new_root;
}

// Функция для вставки узла в декартово дерево
struct Node* insert(struct Node* root, int x, int c) {
    if (!root) {
        return new_node(x, c);
    }

    if (x < root->x) {
        root->left = insert(root->left, x, c);
        if (root->left && root->left->priority > root->priority)
            root = rotate_right(root);
    }
    else {
        root->right = insert(root->right, x, c);
        if (root->right && root->right->priority > root->priority)
            root = rotate_left(root);
    }
    update_size(root);
    return root;
}



// Функция для поиска максимума на интервале [x, y)
int find_max(struct Node* root, int x, int y) {
    if (!root) return -1;  // Пустое поддерево

    
    // Если текущий узел выходит за пределы диапазона
    if (root->x >= y) 
        return find_max(root->left, x, y);  // Левое поддерево
    if (root->x < x) 
        return find_max(root->right, x, y);  // Правое поддерево

    // Корень в пределах интервала
    int left_max = find_max(root->left, x, y);
    int right_max = find_max(root->right, x, y);
    int result = root->c;

    // Если найден максимум в поддеревьях, обновляем результат
    if (left_max > result) result = left_max;
    if (right_max > result) result = right_max;

    return result;
}





//int main() {
//    struct Node* root = NULL;
//
//    // Пример пар (x, c)
//    int arr[][2] = { {1, 5}, {3, 7}, {2, 6}, {4, 8} };
//    int n = 4;
//
//    // Вставляем все пары в декартово дерево
//    for (int i = 0; i < n; i++) {
//        root = insert(root, arr[i][0], arr[i][1]);
//    }
//
//    // Пример запроса для интервала [2, 4)
//    printf("Max value in range [2, 4): %d\n", find_max(root, 2, 4));
//
//    return 0;
//}
