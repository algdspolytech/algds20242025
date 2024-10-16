#include "Header.h"
#pragma warning(disable:4996)

Set* initialization() { //инициализация множества
	Set* init = (Set*)malloc(sizeof(node));
	init->head = NULL;
	return init;
}

bool contains(Set* data, int value) { //проверка на уникальность
	node* iterator = data->head;
	while (iterator != NULL) {
		if (iterator->data == value) {
			return true;
		}
		iterator = iterator->next;
	}
	return false;
}

void add(Set* set, int data) { //добавление элемента в множество
	if (!contains(set, data)) {
		node* ptr = (node*)malloc(sizeof(node));
		ptr->data = data;
		ptr->next = set->head;
		set->head = ptr;
	}
}

bool removee(Set* set, int value) {
	if (set == NULL || set->head == NULL) return false;

	node* current = set->head;
	node* previous = NULL;

	while (current != NULL) {
		if (current->data == value) {
			if (previous == NULL) {
				set->head = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			return true;
		}
		previous = current;
		current = current->next;
	}
	return false;
}


Set* union_sets(Set* s1, Set* s2) {
	Set* res = initialization();
	node* current = s1->head;
	while (current != NULL) {
		add(res, current->data);
		current = current->next;
	}
	current = s2->head;
	while (current != NULL) {
		add(res, current->data);
		current = current->next;
	}
	return res;
}

Set* intersection(Set* s1, Set* s2) {
	Set* res = initialization();
	node* current = s1->head;
	while (current != NULL) {
		if (contains(s2, current->data)) {
			add(res, current->data);
		}
		current = current->next;
	}
	return res;
}

Set* free_set(Set* s) {
	node* current = s->head;
	while (current != NULL) {
		node* tmp = current;
		current = current->next;
		free(tmp);
	}
	free(s);
	free(current);
	return 0;
}

void print_set(Set* set) {
	node* current = set->head;
	printf("{ ");
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("}\n");
	free(current);
}
