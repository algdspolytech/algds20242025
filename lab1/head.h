#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Temperature {
    int day;
    int month;
    int year;
    int temp;
} Temperature;

typedef struct Node {
    Temperature data;
    struct Node* next;
} Node;

struct Node* head = NULL;
struct Node* current = NULL;

Node* CreateNode(Temperature data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* AddNode(Node* head, Temperature data) {
    Node* newNode = CreateNode(data);

    if (head == NULL || data.temp < head->data.temp ||
        (data.temp == head->data.temp &&
            (data.year < head->data.year ||
                (data.year == head->data.year && data.month < head->data.month) ||
                (data.year == head->data.year && data.month == head->data.month &&
                    data.day < head->data.day)))) {
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    Node* previous = NULL;
    while (current != NULL && (data.temp > current->data.temp ||
        (data.temp == current->data.temp &&
            (data.year > current->data.year ||
                (data.year == current->data.year &&
                    data.month > current->data.month) ||
                (data.year == current->data.year &&
                    data.month == current->data.month &&
                    data.day >= current->data.day))))) {
        previous = current;
        current = current->next;
    }

    previous->next = newNode;
    newNode->next = current;

    return head;
}

void TempLessZero(Node* head) {
    Node* current = head;
    while (current != NULL && current->data.temp < 0) {
        printf("Date: %d.%d.%d, Temperature: %.d\n", current->data.day,
            current->data.month, current->data.year, current->data.temp);
        current = current->next;
    }
}

int FindTemp(Node* head, int findTemp) {

    int found = 0;

    Node* current = head;
    while (current != NULL) {
        if (current->data.temp == findTemp) {
            printf("Day with this temperature: %d.%d.%d\n", current->data.day,
                current->data.month, current->data.year);
            found++;
        }

        current = current->next;
    }

    return found;
}

Node* AddData(FILE* fp) {

    head = NULL;

    char buffer[100];

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

        buffer[strcspn(buffer, "\n")] = '\0';

        char* date = strtok(buffer, " ");
        char* strtemp = strtok(NULL, " ");

        if (date == NULL) {
            fprintf(stderr, "Error reading file\n");
        }

        if (strtemp == NULL) {
            fprintf(stderr, "Error reading file 2\n");
        }
        Temperature data;

        data.day = (date[0] - '0') * 10 + (date[1] - '0');
        data.month = (date[3] - '0') * 10 + (date[4] - '0');
        data.year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
            (date[8] - '0') * 10 + (date[9] - '0');
        data.temp = atoi(strtemp);
        head = AddNode(head, data);
    }
    return head;
}

