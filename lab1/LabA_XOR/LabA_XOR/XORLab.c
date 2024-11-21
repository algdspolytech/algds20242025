#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "XORLab.h"

Node* XOR(Node* a, Node* b) {
	return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

Node* create_node(const char* data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = _strdup(data);
	new_node->link = NULL;
	return new_node;
}


void add(XORLinkedList* list, const char* data) {
	Node* new_node = create_node(data);
	if (list->head == NULL) {
		list->head = list->tail = new_node;
	}
	else {
		new_node->link = list->tail;
		list->tail->link = XOR(list->tail->link, new_node);
		list->tail = new_node;
	}
}


Node* find(XORLinkedList* list, const char* key) {
	Node* prev = NULL, * curr = list->head;
	while (curr != NULL) {
		if (strcmp(curr->data, key) == 0) {
			return curr;
		}
		Node* next = XOR(prev, curr->link);
		prev = curr;
		curr = next;
	}
	return NULL;
}

void delete_by_address(XORLinkedList* list, Node* node) {
	if (node == NULL) return;

	Node* prev = NULL, * curr = list->head;
	Node* prev_prev = NULL;
	while (curr != NULL) {
		if (curr == node) {
			Node* next = XOR(prev, curr->link);
			if (prev != NULL) {
				prev->link = XOR(prev_prev, next);
			}
			else {
				list->head = next;
			}

			if (next != NULL) {
				next->link = XOR(prev, XOR(curr, next->link));
			}
			else {
				list->tail = prev;
			}
			free(curr->data);
			free(curr);
			return;
		}
		prev_prev = prev;
		prev = curr;
		curr = XOR(prev_prev, curr->link);
	}
}

void delete_by_key(XORLinkedList* list, const char* key) {
	Node* node = find(list, key);
	delete_by_address(list, node);
}


void iterate(XORLinkedList* list) {
	Node* prev = NULL, * curr = list->head;
	while (curr != NULL) {
		printf("%s ", curr->data);
		Node* next = XOR(prev, curr->link);
		prev = curr;
		curr = next;
	}
	printf("\n");
}

void free_list(XORLinkedList* list) {
	if (list == NULL)
		return;
	Node* prev = NULL, * curr = list->head;
	while (curr != NULL) {
		Node* next = XOR(prev, curr->link);
		free(curr->data);
		free(curr);
		prev = curr;
		curr = next;
	}
	list->head = list->tail = NULL;
}