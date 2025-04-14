#include <stdio.h>
#include <stdlib.h>
#include "RBtree.h"

int main() {
    RBTree *tree = createRBTree();

    // Вставка элементов в дерево
    insert(tree, 20);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 10);
    insert(tree, 30);

    printf("Дерево после вставки элементов:\n");
    printTree(tree->root, tree->TNULL, 0);

    // Поиск элемента
    int key = 15;
    Node *foundNode = search(tree, key);
    if (foundNode != tree->TNULL) {
        printf("\nЭлемент %d найден в дереве.\n", key);
    } else {
        printf("\nЭлемент %d не найден в дереве.\n", key);
    }

    // Удаление элемента
    delete(tree, 15);
    printf("\nДерево после удаления элемента 15:\n");
    printTree(tree->root, tree->TNULL, 0);

    // Удаление элемента, который не существует
    delete(tree, 100);
    printf("\nДерево после попытки удаления несуществующего элемента 100:\n");
    printTree(tree->root, tree->TNULL, 0);

    return 0;
}