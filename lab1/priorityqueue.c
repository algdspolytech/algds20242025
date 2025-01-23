#include <malloc.h>
#include <stdio.h>
#include "priorityqueue.h"

struct PriorityQueue* PrQcreate(int data, int key) { //Создать новую очередь. Сложность - O(1)
	struct PriorityQueue* ans = malloc(sizeof(struct PriorityQueue));
	ans->data = data;
	ans->key = key;
	ans->next = NULL;
	return ans;
}

void PrQclear (struct PriorityQueue* q) {//Удалить существующую очередь. Сложность - O(n)
	if (q!=NULL) {
		if (q->next == NULL) {
			free(q);
		}
		else {
			PrQclear(q->next);
			free(q);
		}
	}
}

struct PriorityQueue* PrQinsert(struct PriorityQueue* q, int data, int key) {//Добавить элемент. Сложность - O(n)
	if (q != NULL) {
		struct PriorityQueue* temp = PrQcreate(data, key);
		if (q->key >= key) {
			temp->next = q;
			return temp;
		}
		else {
			struct PriorityQueue* cur = q;
			while ((int)cur->next != NULL && cur->next->key <= key) {
				cur = cur->next;
			}
			temp->next = cur->next;
			cur->next = temp;
			return q;
		}
	}
	else {
		return PrQcreate(data, key);
	}
}

int PrQextractMinimum(struct PriorityQueue* q) {//Взять элемент с минимальным приоритетом. Сложность - O(1)
	if (q != NULL) {
		int ans = q->data;
		if (q->next != NULL) {
			struct PriorityQueue* temp = q->next;
			q->data = temp->data;
			q->key = temp->key;
			q->next = temp->next;
			free(temp);
			return ans;
		}
		else {
			free(q);
			return ans;
		}
	}
	else {
		return NULL;
	}
}