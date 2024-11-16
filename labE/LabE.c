#include <locale.h>
#include "LabE_lib.h"

int main() {
    setlocale(LC_ALL, "Rus");
    int elements[] = { 10, 5, 15, 3, 7, 12, 18 };
    int size = sizeof(elements) / sizeof(elements[0]);

    TreeNode* root = initialize_tree(elements, size);

    printf("Дерево в обычном виде:\n");
    print_tree(root, 0);

    printf("\nДерево в виде: узел (левое поддерево) (правое поддерево):\n");
    print_compact_tree(root);
    printf("\n");

    free_tree(root);

    return 0;
}