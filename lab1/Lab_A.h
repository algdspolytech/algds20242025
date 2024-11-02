#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
}Node;

Node* CreateNode(int data);
bool CheckElement(Node* head, int data);
void AddElement(Node** head, int data);
Node* RemoveElement(Node** head, int data);
Node* UnionSets(Node* head1, Node* head2);
Node* IntersectionSets(Node* head1, Node* head2);
void printSet(Node* head);

