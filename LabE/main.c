#include <LabE.c>
#include <stdio.h>

int main(){
    Node* root = initNode(1);
    addNode(&root, 6);
    addNode(&root, 0);
    addNode(&root, -6);
    addNode(&root, 0);
    printTree(root);
    deleteSubtree(&root,0);
    printTree(root);
    return 0;
}
