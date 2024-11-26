#include <stdio.h>
#include "bst.h"

int main() {
    Node* root = NULL;

    // ¬ставка элементов в дерево
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("ƒерево по возрастанию (с размером поддерева):\n");
    inorderPrint(root);
    printf("\n");

    int key = 60; // Ёлемент, дл€ которого мы ищем элемент с пор€дком на K меньше
    int k = 2;

    Node* result = findElementMinusK(root, key, k);
    if (result != NULL) {
        printf("Ёлемент с пор€дком на %d меньше элемента %d: %d\n", k, key, result->key);
    }
    else {
        printf("Ёлемент с пор€дком на %d меньше элемента %d не найден.\n", k, key);
    }

    return 0;
}
