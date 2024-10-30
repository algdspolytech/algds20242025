#include "Libr.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Ôóíêöèÿ äëÿ ñîçäàíèÿ íîâîãî óçëà
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(data) + 1); // +1 äëÿ '\0'
    strcpy(newNode->data, data); 
    newNode->next = NULL; 
    return newNode;
}

// Ôóíêöèÿ äëÿ äîáàâëåíèÿ óçëà â êîíåö ñïèñêà
void append(Node** head, const char* str) {
    Node* new_node = createNode(str);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Ôóíêöèÿ äëÿ äîáàâëåíèÿ óçëà â íà÷àëî ñïèñêà
void append_forward(Node** head, const char* data) {
    Node* new = createNode(data);
    new->next = *head;
    *head = new;
}

// Ôóíêöèÿ äëÿ ðàçäåëåíèÿ ñïèñêà íà äâå ïîëîâèíû
void split(Node* source, Node** fir, Node** sec) {
    if (source == NULL) {
        *fir = NULL;
        *sec = NULL;
        return; 
    }

    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    // Ñäâèãàåì óêàçàòåëè, ÷òîáû ðàçáèòü ñïèñîê
    while (fast != NULL) {
        fast = fast->next; 
        if (fast != NULL) {
            slow = slow->next; 
            fast = fast->next; 
        }
    }

    *fir = source; // Ïåðâàÿ ïîëîâèíà
    *sec = slow->next; // Âòîðàÿ ïîëîâèíà
    slow->next = NULL; // Ðàçðûâàåì ñâÿçü
}

// Ôóíêöèÿ äëÿ ñëèÿíèÿ äâóõ îòñîðòèðîâàííûõ ñïèñêîâ
Node* merge(Node* a, Node* b) {
    Node* result = NULL;

    // Áàçîâûé ñëó÷àé
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // Âûáèðàåì ìåíüøèé ýëåìåíò
    if (strcmp(a->data, b->data) <= 0) {
        result = a;
        result->next = merge(a->next, b); 
    }
    else {
        result = b;
        result->next = merge(a, b->next);
    }
    return result;
}

// Ôóíêöèÿ ñîðòèðîâêè ñïèñêà
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

  
    if (head == NULL || head->next == NULL) {
        return;
    }
   
    split(head, &a, &b);

    
    mergeSort(&a);
    mergeSort(&b);

    // Ñëèâàåì îòñîðòèðîâàííûå ïîëîâèíû
    *headRef = merge(a, b);
}

// Ôóíêöèÿ äëÿ âûâîäà ñïèñêà
void printList(Node* node) {
    while (node != NULL) {
        printf("%s\n", node->data);
        node = node->next;
    }
}
