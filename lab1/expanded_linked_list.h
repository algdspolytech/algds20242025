#ifndef EXPANDED_LINKED_LIST_H
#define EXPANDED_LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#define NODE_CAPACITY 4 

typedef struct Node {
    int values[NODE_CAPACITY];
    int count;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int total_count;
} ExpandedLinkedList;

// ������������� ������
void init_list(ExpandedLinkedList* list);

// ���������� �������� � ������
void add_element(ExpandedLinkedList* list, int value);

// ����� ������� �������� �� ��������
int find_element_by_key(ExpandedLinkedList* list, int value);

// ����� �������� �� �������
int find_element_by_index(ExpandedLinkedList* list, int index);

// �������� �������� �� �������
bool remove_element_by_index(ExpandedLinkedList* list, int index);

// ������� ������ ���������� ���������
int get_total_count(ExpandedLinkedList* list);

// ����� ���������� �������� ����� ��������� ��������
int get_next_element(ExpandedLinkedList* list, int value);

#endif // EXPANDED_LINKED_LIST_H
