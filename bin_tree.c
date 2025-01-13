#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "bin_tree.h"


typedef struct QueueNode {
	Node* treeNode;
	struct QueueNode* next;
} QueueNode;


typedef struct Queue {
	QueueNode* front;
	QueueNode* rear;
} Queue;


typedef struct StackNode {
	Node* treeNode;
	struct StackNode* next;
} StackNode;


typedef struct Stack {
	StackNode* top;
} Stack;


Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return -1;
	}
	q->front = NULL;
	q->rear = NULL;
	return q;
}


void enqueue(Queue* q, Node* tree_node) {
	QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newQueueNode == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return -1;
	}
	newQueueNode->treeNode = tree_node;
	newQueueNode->next = NULL;

	if (q->rear == NULL) {
		q->front = newQueueNode;
		q->rear = newQueueNode;
		return;
	}

	q->rear->next = newQueueNode;
	q->rear = newQueueNode;
}


Node* dequeue(Queue* q) {
	if (q->front == NULL) {
		return NULL;
	}

	QueueNode* temp = q->front;
	Node* treeNode = temp->treeNode;
	q->front = q->front->next;

	if (q->front == NULL) {
		q->rear = NULL;
	}

	free(temp);
	return treeNode;
}


int isEmpty(Queue* q) {
	return q->front == NULL;
}

void freeQueue(Queue* queue) {
	QueueNode* current = queue->front;
	QueueNode* nextNode;

	while (current != NULL) {
		nextNode = current->next;
		free(current);
		current = nextNode;
	}

	free(queue);
}


Node* getParentNode(Node* binary_tree, Node* child_node) {
	if (binary_tree == NULL || child_node == NULL) {
		return NULL;
	}

	Queue* q = createQueue();
	enqueue(q, binary_tree);

	while (!isEmpty(q)) {
		Node* current = dequeue(q);

		if (current->left == child_node || current->right == child_node) {
			freeQueue(q);
			return current;
		}

		if (current->left != NULL) {
			enqueue(q, current->left);
		}
		if (current->right != NULL) {
			enqueue(q, current->right);
		}
	}

	freeQueue(q);
	return NULL;
}


Node* createNode(int node_data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return -1;
	}
	new_node->count = 1;
	new_node->occurence = 1;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = node_data;
	return new_node;
}


Node* findNode(Node* binary_tree, int key) {
	if (binary_tree == NULL) return NULL;
	Queue* q = createQueue();
	enqueue(q, binary_tree);
	while (!isEmpty(q)) {
		Node* current = dequeue(q);
		if (current->data == key) {
			freeQueue(q);
			return current;
		}
		if (current->left) enqueue(q, current->left);
		if (current->right) enqueue(q, current->right);
	}
	freeQueue(q);
	return NULL;
}


Node* addNode(Node* binary_tree, int node_data) {
	if (binary_tree == NULL) {
		return(createNode(node_data)); // если в дереве вообще нет узлов
	}

	Node* temp = findNode(binary_tree, node_data); // провер€ем на дубликаты, если уже есть нод такой, то увеличиваем счЄтчик
	if (temp != NULL) {
		temp->occurence++;
		return binary_tree;
	}

	Node* current = binary_tree;
	Node* parent = NULL;

	while (current != NULL) {
		parent = current;
		if (current->left == NULL || (current->right && current->left->count <= current->right->count)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	Node* new_node = createNode(node_data);
	if (parent->left == NULL) {
		parent->left = new_node;
	}
	else {
		parent->right = new_node;
	}

	current = parent;
	while (current != NULL) {
		current->count = 1 + (current->left ? current->left->count : 0) + (current->right ? current->right->count : 0);
		current = getParentNode(binary_tree, current);
	}

	return binary_tree;
}


void updateCounts(Node* binary_tree, Node* root) {
	if (root == NULL) return;

	while (getParentNode(binary_tree, root)) {
		root->count--;
		root = getParentNode(binary_tree, root);
	}
	binary_tree->count--;
}


Node* findRightmostIterative(Node* node) {
	if (node == NULL) return NULL;
	while (node->right != NULL) {
		node = node->right;
	}
	if (node->left != NULL) {
		return node->left;
	}
	return node;
}

Node* deleteNode(Node* binary_tree, int key) {
	if (binary_tree == NULL) return NULL;

	Node* keyNode = findNode(binary_tree, key);
	if (keyNode == NULL) return binary_tree;
	if (keyNode->occurence > 1) {
		keyNode->occurence--;
		return binary_tree;
	}

	Node* lastNode = findRightmostIterative(keyNode);

	if (lastNode != keyNode) {
		keyNode->data = lastNode->data;
		Node* parent = getParentNode(binary_tree, lastNode);
		if (parent->left == lastNode) parent->left = NULL;
		else parent->right = NULL;
		free(lastNode);
		updateCounts(binary_tree, parent);
	}
	else {
		Node* parent = getParentNode(binary_tree, keyNode);
		if (parent->left == keyNode) parent->left = NULL;
		else parent->right = NULL;
		free(keyNode);
		updateCounts(binary_tree, parent);
	}

	return binary_tree;
}


void freeTree(Node* binary_tree) {
	if (binary_tree == NULL) return;
	freeTree(binary_tree->left);
	freeTree(binary_tree->right);
	free(binary_tree);
}


Stack* createStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return -1;
	}
	stack->top = NULL;
	return stack;
}


void push(Stack* stack, Node* treeNode) {
	StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
	if (newStackNode == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return -1;
	}
	newStackNode->treeNode = treeNode;
	newStackNode->next = stack->top;
	stack->top = newStackNode;
}


Node* pop(Stack* stack) {
	if (stack->top == NULL) return NULL;

	StackNode* temp = stack->top;
	Node* treeNode = temp->treeNode;
	stack->top = stack->top->next;
	free(temp);
	return treeNode;
}


int isEmptyStack(Stack* stack) {
	return stack->top == NULL;
}


void freeStack(Stack* stack) {
	StackNode* current = stack->top;
	StackNode* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	free(stack);
}

void printTreeInOrder(Node* binary_tree) {
	Stack* stack = createStack();
	Node* current = binary_tree;

	while (current != NULL || !isEmptyStack(stack)) {
		while (current != NULL) {
			push(stack, current);
			current = current->left;
		}

		current = pop(stack);
		if (current != NULL) {
			printf("%d(count: %d, occurence: %d) ", current->data, current->count, current->occurence);
			current = current->right;
		}
	}
	printf("\n");

	freeStack(stack);
}