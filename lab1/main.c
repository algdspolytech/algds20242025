#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char * data;
    struct Node * link;
}Node;

Node * XOR_function(Node * a, Node * b){
    return (Node *)((uintptr_t)a ^ (uintptr_t)b);
}

Node * createNode(const char * data){
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node -> link = NULL;
    new_node -> data = strdup(data);
    return new_node;
}

void listInsert(Node ** head, const char * data){
    Node * new_node = createNode(data);
    new_node -> link = *head;
    if(*head){
        (*head) -> link = XOR_function(new_node, (*head) -> link);
    }
    new_node = *head;
}

Node * find(Node * head, const char * key){
    Node * previous = NULL;
    Node * current = head;
    while (current){
        if (strcmp(current -> data, key) == 0){
            return current;
        }
        Node * next = XOR_function(previous, current -> link);
        previous = current;
        current = next;
    }
    return NULL;
}

void deleteByKey(Node ** head, const char * key){
    Node * previous = NULL;
    Node * current = *head;
    while (current){        
        if (strcmp(current -> data, key) == 0){
            Node * next = XOR_function(previous, current -> link);
            if (current == *head){
                *head = next;
            }
            if (next){
                next -> link = XOR_function(previous, XOR_function(current, next -> link));
            }
            if (previous){
                previous -> link = XOR_function(XOR_function(current, previous -> link), next);
            }
            free(current -> data);
            free(current);
            return;
        }
        Node * next = XOR_function(previous, current -> link);
        previous = current;
        current = next;
    }
}

void deleteByAddress(Node ** head, Node * node){
    if (!node) return;
    Node * previous = NULL;
    Node * current = *head;
    while (current){
        if (current == node){
            Node * next = XOR_function(previous, current -> link);
            if(previous){
                previous -> link = XOR_function(XOR_function(current, previous -> link), next);
            }
            if(next){
                next -> link = XOR_function(previous, XOR_function(current, next -> link));
            }
            if (current == *head){
                *head = next;
            }
            free(current -> data);
            free (current);
            return;
        }
        Node * next = XOR_function(previous, current -> link);
        previous = current;
        current = next;
    }
}

void iterate (Node * head){
    if (!head) return;
    Node * previous = NULL;
    Node * current = head;
    while (current){
        printf("%s\n", current -> data);
        Node * next = XOR_function(previous, current -> link);
        previous = current;
        current = next;
    }
}

void clearList (Node ** head){
    Node * current = *head;
    while (current){
        Node * next = XOR_function(NULL, current -> link);
        free(current -> data);
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(){
    Node * head = NULL;
    listInsert(&head, "O");
    listInsert(&head, "D");
    listInsert(&head, "e");
    listInsert(&head, "t");
    iterate(head);
    clearList(&head);
    return 0;
}