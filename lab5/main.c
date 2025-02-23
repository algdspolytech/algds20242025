#include "tree.h"

int main() {
    Node* root = NULL;
    int values[] = {10, 5, 15, 2, 7, 12, 18, 19};
    for (int i = 0; i < (int)sizeof(values)/(int)sizeof(values[0]); i++)
        root = insert(root, values[i]);
    
    updateBalances(root);
    printTree(root, 0);
    freeTree(root);
    return 0;
}