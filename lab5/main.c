#include "BSearchTree.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    BinaryTreeNode* root = NULL;

    int values[] = { 141, 56, 98, 3, 20, 48, 930, 0, 8 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {

        root = Insert(root, values[i]);
    }
    Print(root);
    printf("\n");
    int key = 98;
    int K = 4;

    BinaryTreeNode* result = FindElemNumMinusK(root, key, K);

    if (result) {
        printf("Элемент, порядок которого на %d единиц меньше %d: %d\n", K, key, result->key);
    }
    else {
        printf("Не найден элемент, порядок которого на %d единиц меньше %d.\n", K, key);
    }

    Free(root);
    return 0;
}           
