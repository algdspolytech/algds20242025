#include <stdio.h>
#include <tree.c>

int main(){
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    addNode(&root, 0);
    printTree(root);
    printf("\n");
    deleteSubtree(&root,0);
    printTree(root);
    return 0;
}
