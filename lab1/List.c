#pragma warning(disable:4996)
#include "List.h" 


Node* ListItem_Create(int data, Node* next) {
    Node* item = (Node*)malloc(sizeof(Node));
    item->data = data;
    item->next = next;
    return item;
}


void Queue_Init(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}


void push(Queue* queue, int x) {
    Node* element = queue->tail;
    queue->tail = ListItem_Create(x, NULL);
    if (queue->size == 0) {
        queue->head = queue->tail;
    }
    else {
        element->next = queue->tail;
    }
    queue->size++;
}


int pop(Queue* queue) {
    if (queue->size == 0) {
        return -1;
    }
    queue->size--;
    Node* element = queue->head;
    queue->head = queue->head->next;
    int value = element->data;
    free(element);
    return value;
}


bool isempty(Queue* queue) {
    return queue->head == NULL;
}


void Queue_Free(Queue* queue) {
    while (queue->head != NULL) {
        Node* temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
    queue->tail = NULL;
    queue->size = 0;
}


