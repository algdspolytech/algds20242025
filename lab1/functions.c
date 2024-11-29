#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <time.h>

#include <windows.h>

#include "functions.h"

Node* init(char* s) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->str = (char*)malloc(sizeof(s));
    strcpy(tmp->str, s);
    tmp->next = NULL;
    return tmp;
}

void add_node(Node* head, char* s) {
    if (head != NULL) {
        Node* help = init(s);

        Node* tmp = head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = help;
    }
}

int len_of_full_str(Node* head) {
    int n = 0;
    Node* tmp = head;
    while (tmp != NULL) {
        n += strlen(tmp->str);
        tmp = tmp->next;
    }
    return n;
}

char* get_full_str(Node* head) {
    int len = len_of_full_str(head);
    char* ans = (char*)malloc(len + 1);
    ans[0] = '\0';
    Node* tmp = head;
    while (tmp != NULL) {
        strcat(ans, tmp->str);
        tmp = tmp->next;
    }
    return ans;
}

void print_list(Node* head) {
    Node* tmp = head;
    while (tmp != NULL) {
        printf("\"%s\"", tmp->str);
        if (tmp->next != NULL) {
            printf("---");
        }
        tmp = tmp->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->str);
        free(tmp);
    }
}