#define _CRT_SECURE_NO_WARNINGS

#include "structs.h"
#include "funcs.h"
#include "tests.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");

    RBTree S1 = { NULL }, S2 = { NULL };
    insert(&S1, 10);
    insert(&S1, 5);
    insert(&S1, 15);
    insert(&S2, 20);
    insert(&S2, 25);
    insert(&S2, 30);

    int x = 18;
    RBTree* result = unionRBTree(&S1, x, &S2);
    printf("Объединенное дерево (по порядку): ");
    inorder(result->root);
    printf("\n");

    test_insert_and_search_No1();
    test_union_No2();
    test_inorder_traversal_No3();
    test_balance_No4();
    test_min_element_No5();
    test_max_element_No6();
    test_empty_tree_No7();
    test_duplicate_insert_No8();
    test_node_colors_No9();
    test_merge_trees_No10();

    return 0;
}
