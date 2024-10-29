#include "expanded_linked_list.h"
#include <stdio.h>

void init_list(ExpandedLinkedList* list) {
    list->head = NULL;
    list->total_count = 0;
}

void add_element(ExpandedLinkedList* list, int value) {
    Node* current = list->head;
    if (!current || current->count == NODE_CAPACITY) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->values[0] = value;
        new_node->count = 1;
        new_node->next = list->head;
        list->head = new_node;
    }
    else {
        current->values[current->count++] = value;
    }
    list->total_count++;
}

int find_element_by_key(ExpandedLinkedList* list, int value) {
    Node* current = list->head;
    int index = 0;
    while (current) {
        for (int i = 0; i < current->count; i++) {
            if (current->values[i] == value) {
                return index;
            }
            index++;
        }
        current = current->next;
    }
    return -1;
}

int find_element_by_index(ExpandedLinkedList* list, int index) {
    if (index < 0 || index >= list->total_count) {
        return -1;
    }
    Node* current = list->head;
    while (current) {
        if (index < current->count) {
            return current->values[index];
        }
        index -= current->count;
        current = current->next;
    }
    return -1;
}

bool remove_element_by_index(ExpandedLinkedList* list, int index) {
    if (index < 0 || index >= list->total_count) {
        return false;
    }
    Node* current = list->head;
    Node* prev = NULL;
    while (current) {
        if (index < current->count) {
            for (int i = index; i < current->count - 1; i++) {
                current->values[i] = current->values[i + 1];
            }
            current->count--;
            list->total_count--;
            if (current->count == 0) {
                if (prev) prev->next = current->next;
                else list->head = current->next;
                free(current);
            }
            return true;
        }
        index -= current->count;
        prev = current;
        current = current->next;
    }
    return false;
}

int get_total_count(ExpandedLinkedList* list) {
    return list->total_count;
}

int get_next_element(ExpandedLinkedList* list, int value) {
    Node* current = list->head;
    bool found = false;
    while (current) {
        for (int i = 0; i < current->count; i++) {
            if (found) return current->values[i];
            if (current->values[i] == value) found = true;
        }
        current = current->next;
    }
    return -1;
}
