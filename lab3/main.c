#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    Node* root = NULL;
    
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 18);

    int K;
    printf("Введите значение K: ");
    scanf("%d", &K);

    int count = 0;
    int kthElement = kthSmallest(root, K, &count);

    if (kthElement != -1) {
        printf("K-й наименьший элемент: %d\n", kthElement);
        if (kthElement % 2 == 0) {
            printf("Элементы с порядковыми номерами меньше K: ");
            printElementsLessThanK(root, K);
            printf("\n");
        }
    } else {
        printf("Дерево пусто или K больше количества узлов в дереве.\n");
    }

    return 0;
}