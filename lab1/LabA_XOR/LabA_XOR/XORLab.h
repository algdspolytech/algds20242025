#pragma once
typedef struct Node {
	char* data;
	struct Node* link;
} Node;

typedef struct XORLinkedList {
	Node* head;
	Node* tail;
} XORLinkedList;
Node* XOR(Node* a, Node* b);
Node* create_node(const char* data);
void add(XORLinkedList* list, const char* data);
Node* find(XORLinkedList* list, const char* key);
void delete_by_address(XORLinkedList* list, Node* node);
void delete_by_key(XORLinkedList* list, const char* key);
void iterate(XORLinkedList* list);
void free_list(XORLinkedList* list);