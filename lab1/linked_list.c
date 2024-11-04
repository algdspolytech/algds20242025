#include "linked_list.h"

// Создание нового списка
LinkedList* create_list() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

// Добавление элемента в список
void add_to_list(LinkedList *list, const char *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = strdup(data);
    new_node->next = list->head;
    list->head = new_node;
}

// Освобождение памяти, занятой списком
void free_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

// Функция для слияния двух отсортированных списков
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (strcmp(left->data, right->data) < 0) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

// Функция для сортировки списка слиянием
Node* merge_sort(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }

    Node* left = head;
    Node* right = middle->next;
    middle->next = NULL;

    return merge(merge_sort(left), merge_sort(right));
}

// Сортировка списка
void sort_list(LinkedList *list) {
    list->head = merge_sort(list->head);
}

// Печать списка (для отладки)
void print_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULLn");
}