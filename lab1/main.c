#include "xorList.h"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Russian");
	xorList* list = createList();
	add(list, "Hello");
	add(list, "World");
	add(list, "I'm glad");
	iter(list);
	add(list, "\n");
	delByD(list, "World");
	iter(list);

	Node* node = createNode(NULL);
	node = find(list, "Hello");
	printf("%s", node->data);
	return 0;
}