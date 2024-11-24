#include <stdio.h>
#include <stdlib.h>
#include "Unrolled_linked_list.h"

/*//#define BLOCK_SIZE 4 // ������ ����� � ���� ������

// ����������� ��������� Node
struct Node {
    int values[BLOCK_SIZE]; // ������ �������� � ����
    int count;              // ���������� ��������� � ������� values
    struct Node* next;      // ��������� �� ��������� ����
};

typedef struct Node Node;

// ����������� ��������� UnrolledLinkedList
struct UnrolledLinkedList {
    Node* head;  // ������ ������
    int size;    // ����� ���������� ��������� � ������
};

typedef struct UnrolledLinkedList UnrolledLinkedList;
*/
// ������� ����� ����
Node* createNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) { // �������� ��������� ��������� ������
        printf("������ ��������� ������ ��� ����.\n");
        return NULL;
    }
    node->count = 0;
    node->next = NULL;
    return node;
}

// ������������� ������
UnrolledLinkedList* createList() {
    UnrolledLinkedList* list = (UnrolledLinkedList*)malloc(sizeof(UnrolledLinkedList));
    if (!list) { // �������� ��������� ��������� ������
        printf("������ ��������� ������ ��� ������.\n");
        return NULL;
    }
    list->head = createNode();
    if (!list->head) { // ��������, ���� �� ������� ������� ��������� ����
        free(list);
        return NULL;
    }
    list->size = 0;
    return list;
}

// �������� �������
void add(UnrolledLinkedList* list, int value) {
    if (!list) return; // �������� ��������� ������

    Node* current = list->head;
    // ������� � ���������� ����
    while (current->next != NULL) {
        current = current->next;
    }

    // ���� ������� ���� �����, ������� ����� ����
    if (current->count == BLOCK_SIZE) {
        current->next = createNode();
        if (!current->next) return; // �������� ��������� ��������� ������
        current = current->next;
    }
    current->values[current->count++] = value;
    list->size++;
}

// ����� ����� �������� �� �����
int findIndexByKey(UnrolledLinkedList* list, int key) {
    if (!list) return -1; // �������� ��������� ������

    Node* current = list->head;
    int index = 0;

    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (current->values[i] == key) {
                return index;
            }
            index++;
        }
        current = current->next;
    }
    return -1; // ���� ������� �� ������
}

// ����� ������� �� ������
int findByIndex(UnrolledLinkedList* list, int index) {
    if (!list || index < 0 || index >= list->size) return -1; // �������� ��������� ������

    Node* current = list->head;
    int count = 0;

    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (count == index) {
                return current->values[i];
            }
            count++;
        }
        current = current->next;
    }
    return -1;
}

// ������� ������� �� ������
void deleteByIndex(UnrolledLinkedList* list, int index) {
    if (!list || index < 0 || index >= list->size) return; // �������� ��������� ������

    Node* current = list->head;
    int count = 0;

    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (count == index) {
                for (int j = i; j < current->count - 1; j++) {
                    current->values[j] = current->values[j + 1];
                }
                current->count--;
                list->size--;
                return;
            }
            count++;
        }
        current = current->next;
    }
}

// ���������� ���������� ���������
int getSize(UnrolledLinkedList* list) {
    return list ? list->size : 0; // �������� ��������� ������
}

// ����� ��������� �������
int getNext(UnrolledLinkedList* list, int value) {
    if (!list) return -1; // �������� ��������� ������

    Node* current = list->head;
    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (current->values[i] == value) {
                if (i + 1 < current->count) {
                    return current->values[i + 1];
                }
                else if (current->next != NULL && current->next->count > 0) {
                    return current->next->values[0];
                }
                return -1; // ��� ���������� ��������
            }
        }
        current = current->next;
    }
    return -1;
}

// ������� ������ � ���������� ������
void freeList(UnrolledLinkedList* list) {
    if (!list) return; // �������� ��������� ������

    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

/*int main() {
    UnrolledLinkedList* list = createList();
    if (!list) return -1;

    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40);
    add(list, 50);

    printf("Size: %d\n", getSize(list));
    printf("Index of 30: %d\n", findIndexByKey(list, 30));
    printf("Element at index 2: %d\n", findByIndex(list, 2));

    deleteByIndex(list, 1);
    printf("Size after deletion: %d\n", getSize(list));

    printf("Next element after 40: %d\n", getNext(list, 40));

    freeList(list);

    return 0;
}*/