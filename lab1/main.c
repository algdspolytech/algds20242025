#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"
#include "bstree.h"

int main() {
    RBTree rbTree;
    BSTree bsTree;
    initRBTree(&rbTree);
    initBSTree(&bsTree);

    // Генерация случайных данных
    srand(time(NULL));
    int n = 1000000; // Количество элементов
    int* data = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        data[i] = rand();
    }

    // Вставка в красно-черное дерево
    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        insertRBTree(&rbTree, data[i]);
    }
    clock_t end = clock();
    printf("RBTree Insert Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Вставка в бинарное дерево поиска
    start = clock();
    for (int i = 0; i < n; i++) {
        insertBSTree(&bsTree, data[i]);
    }
    end = clock();
    printf("BSTree Insert Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Поиск в красно-черном дереве
    start = clock();
    for (int i = 0; i < n; i++) {
        searchRBTree(&rbTree, data[i]);
    }
    end = clock();
    printf("RBTree Search Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Поиск в бинарном дереве поиска
    start = clock();
    for (int i = 0; i < n; i++) {
        searchBSTree(&bsTree, data[i]);
    }
    end = clock();
    printf("BSTree Search Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Освобождение памяти
    freeRBTree(&rbTree);
    freeBSTree(&bsTree);
    free(data);

    return 0;
}