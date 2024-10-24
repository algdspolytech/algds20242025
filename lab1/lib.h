#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int day;
    int month;
    int year;
    int temperature;
    struct Node* next;
} Node;

int compareDates(int day1, int month1, int year1, int day2, int month2, int year2);

Node* insertSorted(Node* head, int day, int month, int year, int temperature);

Node* datesBelowZero(Node* head);

void printNegative(Node* head);

Node* searchTemperature(Node* head, int temperature);

void printList(Node* head);

void freeList(Node* head);

#endif