#include "main.h"
int main() {
	Tree* tree = createTree();

	insert(tree, 5);
	insert(tree, 3);
	insert(tree, 7);
	insert(tree, 2);
	insert(tree, 4);
	insert(tree, 6);
	insert(tree, 8);

	printf("Tree: ");
	inOrder(tree->root);
	printf("\n");

	deleteNode(tree);
	deleteNode(tree);
	printf("Tree after deleting: ");
	inOrder(tree->root);
	printf("\n");

	return 0;
}