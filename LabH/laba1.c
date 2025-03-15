#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include"laba1.h"

Node* Create_node(int key)
{
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL)
	{
		printf("Memory allocation error.\n");
		return;
	}
	new_node->key = key;
	new_node->priority = rand();
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

Node* Merge(Node* A, Node* B)
{
	if (A == NULL) return B;
	if (B == NULL) return A;

	if (A->priority > B->priority)
	{
		A->right = Merge(A->right, B);
		return A;
	}
	else
	{
		B->left = Merge(A, B->left);
		return B;
	}
}

void Split(Node* n, int key, Node** A, Node** B)
{
	if (n == NULL)
	{
		*A = NULL;
		*B = NULL;
	}
	else if (n->key < key)
	{
		Split(n->right, key, &n->right, B);
		*A = n;
	}
	else
	{
		Split(n->left, key, A, &n->left);
		*B = n;
	}
}


Node* Insert(int key, Node* root)
{
	Node* new_node = Create_node(key);
	Node* less = NULL;
	Node* greater = NULL; 

	Split(root, key, &less, &greater);

	return Merge(Merge(less, new_node), greater);
}

bool contains(Node* root, int key) 
{
	if (root == NULL) 
	{
		return false; 
	}
	if (root->key == key) 
	{
		return true; 
	}
	if (key < root->key) 
	{
		return contains(root->left, key); 
	}
	else 
	{
		return contains(root->right, key); 
	}
}

Node* Erase(int key, Node* root)
{
	if (contains(root, key) == false)
		return;
	Node* less;
	Node* greater;
	Node* equal;

	Split(root, key, &less, &greater);
	Split(greater, key + 1, &equal, &greater);
	Node* new_root = Merge(less, greater);

	return new_root;
}

int main()
{
	srand(time(NULL));

	RunTests();

	return 0;
}

