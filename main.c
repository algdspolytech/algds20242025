#include "main.h"

int main() {
	srand(time(NULL));
	Node* root = NULL;

	root = insert(root, 1, 10);
	root = insert(root, 3, 20);
	root = insert(root, 5, 15);
	root = insert(root, 7, 30);
	root = insert(root, 9, 25);

	int x = -1, y = 7;
	int max_c = findMax(root, x, y);
	printf("%d", max_c);

	return 0;
}