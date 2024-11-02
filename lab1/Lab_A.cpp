#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Lab_A.h"


Node* CreateNode(int data) {

	Node* NextNode = (Node*)malloc(sizeof(Node));

	NextNode->data = data;
	NextNode->next = NULL;

	return NextNode;
}


bool CheckElement(Node* head, int data) {

	Node* current = head;

	while (current != NULL) {
		if (current->data == data) {
			return true;
		}
		current = current->next;
	}
	return false;
}






void AddElement(Node** head, int data) {

	if (CheckElement(*head, data)) return;

	Node* newNode = CreateNode(data);

	if (*head == NULL || (*head)->data > data) {
		newNode->next = *head;
		*head = newNode;
		return;
	}

	Node* current = *head;

	while (current->next != NULL && current->next->data < data) {
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;
}



Node* RemoveElement(Node** head, int data) {
	if (*head == NULL) {
		return *head;
	}

	if ((*head)->data == data) {
		Node* temp = *head;
		*head = (*head)->next;
		free(temp);
		return *head;

	}

	Node* current = *head;

	while (current->next != NULL && current->next->data != data) {
		current = current->next;
	}

	if (current->next != NULL) {
		Node* temp = current->next;
		current->next = current->next->next;
		free(temp);
	}
}
// удаление головы
Node* UnionSets(Node* head1, Node* head2) {

	Node* result = NULL;

	Node* current = head1;

	while (current != NULL) {
		AddElement(&result, current->data);
		current = current->next;
	}
	
	current = head2;

	while (current != NULL) {
		AddElement(&result, current->data);
		current = current->next;
	}
	return result;

}


Node* IntersectionSets(Node* head1, Node* head2) {

	Node* result = NULL;

	Node* current = head1;

	while (current != NULL) {

		if (CheckElement(head2, current->data)) {
			AddElement(&result, current->data);

		}
		current = current->next;
	}

	return result;
}


void printSet(Node* head) {

	Node* current = head;
	printf("{ ");

	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}

	printf("}\n");
}





