#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "lab_a.h"


Node* CreateNode(int data) {

	Node* NextNode = (Node*)malloc(sizeof(Node));

	NextNode->data = data;
	NextNode->next = NULL;

	return NextNode;
}


bool CheckElem(Node* head, int data) {

	Node* cur = head;

	while (cur != NULL) {
		if (cur->data == data) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}






void AddElem(Node** head, int data) {

	if (CheckElem(*head, data)) return;

	Node* newNode = CreateNode(data);

	if (*head == NULL || (*head)->data > data) {
		newNode->next = *head;
		*head = newNode;
		return;
	}

	Node* cur = *head;

	while (cur->next != NULL && cur->next->data < data) {
		cur = cur->next;
	}

	newNode->next = cur->next;
	cur->next = newNode;
}



Node* RemoveElem(Node** head, int data) {
	if (*head == NULL) {
		return *head;
	}

	if ((*head)->data == data) {
		Node* temp = *head;
		*head = (*head)->next;
		free(temp);
		return *head;

	}

	Node* cur = *head;

	while (cur->next != NULL && cur->next->data != data) {
		cur = cur->next;
	}

	if (cur->next != NULL) {
		Node* temp = cur->next;
		cur->next = cur->next->next;
		free(temp);
	}
}

Node* UnionSets(Node* head1, Node* head2) {

	Node* res = NULL;

	Node* cur = head1;

	while (cur != NULL) {
		AddElem(&res, cur->data);
		cur = cur->next;
	}
	
	cur = head2;

	while (cur != NULL) {
		AddElem(&res, cur->data);
		cur = cur->next;
	}
	return res;

}


Node* IntersectionSets(Node* head1, Node* head2) {

	Node* res = NULL;

	Node* cur = head1;

	while (cur != NULL) {

		if (CheckElem(head2, cur->data)) {
			AddElem(&res, cur->data);

		}
		cur = cur->next;
	}

	return res;
}


void printSet(Node* head) {

	Node* cur = head;
	printf("{ ");

	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}

	printf("}\n");
}