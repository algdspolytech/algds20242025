#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

int main() {
    RBTree* tree = createTree();
    addNode(tree, 20);
    addNode(tree, 15);
    addNode(tree, 25);
    addNode(tree, 23);

    addNode(tree, 30);

    printf("ƒерево после вставки элементов\n");

    displayTree(tree->root, tree->TNULL, 0);


    int key = 23;

    Node* fNode = findNode(tree, key);
    if (findNode != tree->TNULL) {
        printf("\nЁлемент %d найден в дереве.\n", key);
    }
    else {
        printf("\nЁлемент %d не найден в дереве.\n", key);
    }

    // ”даление элемента
    removeNode(tree, 25);
    printf("\nƒерево после удалени€ элемента 25:\n");
    displayTree(tree->root, tree->TNULL, 0);

    // ”даление элемента, который не существует
    removeNode(tree, 1000);
    printf("\nƒерево после попытки удалени€ несуществующего элемента 1000:\n");
    displayTree(tree->root, tree->TNULL, 0);

    return 0;




}

