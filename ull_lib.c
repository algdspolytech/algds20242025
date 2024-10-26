#include "ull_lib.h"
#include <stdio.h>
#include <stdlib.h>
#define NODE_CAPACITY 4

node* new_node() {
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL) {
		printf("\nmemory allocation failed!\n");
		exit(1);
	}
	newNode->next = NULL;
	newNode->numElements = 0;

	return newNode;
}

ull* new_unrolled_list() {
	ull* list = (ull*)malloc(sizeof(ull));
	if (list == NULL) {
		printf("\nmemory allocation failed!\n");
		exit(1);
	}

	list->head = NULL;

	return list;
}

int findIndexByKey_unrolled_list(ull* list, int key) {
	node* current = list->head;
	int index = 0;

	while (current != NULL) {
		for (int i = 0; i < current->numElements; i++) {
			if (current->elements[i] == key) {
				return index;
			}
			index++;
		}
		current = current->next;
	}

	printf("\nItem %d not found!\n", key);
	return -1;
}

int findValByIndex_unrolled_list(ull* list, int index) {
	node* current = list->head;
	int count = 0;

	while (current != NULL) {
		for (int i = 0; i < current->numElements; i++) {
			if (count == index) {
				return current->elements[i];
			}
			count++;
		}
		current = current->next;
	}

	printf("\nItem number out of range, item not found!\n");
	return -1;
}

void insertElement_unrolled_list(ull* list, int value) {
	node* newNode = new_node();

	if (list->head == NULL) {
		list->head = newNode;
		newNode->numElements = 1;
		newNode->elements[0] = value;
		newNode->next = NULL;
	}
	else {
		node* current = list->head;
		while (current->next != NULL) {
			current = current->next;
		}

		if (current->numElements < NODE_CAPACITY / 2) {
			current->elements[current->numElements] = value;
			current->numElements++;
		}
		else {
			newNode->numElements = 1;
			newNode->elements[0] = value;
			newNode->next = NULL;
			current->next = newNode;
		}
	}
}

void removeElement_unrolled_list(ull* list, int index) {
	if (list == NULL || list->head == NULL || index < 0) {
		printf("\nInvalid item number or empty list!\n");
		return;
	}

	node* current = list->head;
	int count = 0;

	while (current != NULL) {
		if (count + current->numElements > index) {
			break;
		}
		count += current->numElements;
		current = current->next;
	}

	if (current == NULL) {
		printf("\nItem with number %d does not exist in the list!\n", index);
		return;
	}

	for (int i = index - count; i < current->numElements - 1; i++) {
		current->elements[i] = current->elements[i + 1];
	}
	current->numElements--;

	if (current->numElements == 0) {
		if (current == list->head) {
			list->head = current->next;
		}
		else {
			node* prev = list->head;
			while (prev->next != current) {
				prev = prev->next;
			}
			prev->next = current->next;
		}
		free(current);
		return;
	}

	while (current->numElements < (NODE_CAPACITY / 2) && current->next) {
		if (current->next && current->next->numElements < (NODE_CAPACITY / 2)) {
			for (int k = 0; k < current->next->numElements; k++) {
				current->elements[current->numElements++] = current->next->elements[k];
			}

			node* deletedNode = current->next;
			current->next = current->next->next;
			free(deletedNode);
			break;
		}
		else {
			current->elements[current->numElements++] = current->next->elements[0];
			current->next->numElements--;
			for (int k = 0; k < current->next->numElements; k++) {
				current->next->elements[k] = current->next->elements[k + 1];
			}
		}
	}
}

int length_unrolled_list(ull* list) {
	node* current = list->head;
	int length = 0;

	while (current != NULL) {
		length += current->numElements;
		current = current->next;
	}

	return length;
}

int iterate_unrolled_list(ull* list, int index) {
	node* current = list->head;
	int current_index = 0;

	while (current != NULL) {
		for (int i = 0; i < current->numElements; i++) {
			if (current_index == index) {
				if (i == current->numElements - 1) {
					if (current->next != NULL) {
						return current->next->elements[0];
					}
					else {
						return -1;
					}
				}
				else {
					return current->elements[i + 1];
				}
			}
			current_index++;
		}
		current = current->next;
	}

	return -1;
}

void print_unrolled_list(ull* list) {
	node* current = list->head;
	while (current != NULL) {
		for (int i = 0; i < current->numElements; i++) {
			printf("%d ", current->elements[i]);
		}
		printf("\n");
		current = current->next;
	}
	printf("\n");
}

void delete_unrolled_list(ull* list) {
	node* current = list->head;
	while (current != NULL) {
		node* temp = current;
		current = current->next;
		free(temp);
	}
	free(list);
}