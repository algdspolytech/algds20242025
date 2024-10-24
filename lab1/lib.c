#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include "lib.h"

int compareDates(int day1, int month1, int year1, int day2, int month2, int year2)
{
    if(year1 * 365 + month1 * 31 + day1 < year2 * 365 + month2 * 31 + day2) return 1;
    if(year1 * 365 + month1 * 31 + day1 > year2 * 365 + month2 * 31 + day2) return -1;
    return 0;

}

Node* insertSorted(Node* head, int day, int month, int year, int temperature)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->day = day;
    new_node->month = month;
    new_node->year = year;
    new_node->temperature = temperature;
    new_node->next = NULL;

    if (head == NULL || head->temperature > temperature || (head->temperature == temperature && (compareDates(head->day, head->month, head->year, day, month, year) < 0)))
    {
        new_node->next = head;
        return new_node;
    }

    Node* current = head;
    while (current->next != NULL && (current->next->temperature < temperature || (current->next->temperature == temperature && (compareDates(current->next->day, current->next->month, current->next->year, day, month, year) > 0))))
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;

    return head;
}

void printNegative(Node* head)
{
    int flag = 1;
    while (head != NULL)
    {
        if (head->temperature < 0)
        {
            printf("Date: %02d.%02d.%02d, Temperature: %d\n", head->day, head->month, head->year, head->temperature);
            flag = 0;
        }
        head = head->next;
    }
    if (flag)
    {
        printf("There are no dates with negative temperature!");
    }
}

Node* searchTemperature(Node* head, int temperature) 
{
    Node* result_head = NULL;
    Node* result_tail = NULL;
    while (head != NULL) 
    {
        if (head->temperature == temperature) 
        {
            Node* new_node = (Node*) malloc(sizeof(Node));
            new_node->day = head->day;
            new_node->month = head->month;
            new_node->year = head->year;
            new_node->temperature = head->temperature;
            new_node->next = NULL;
            if (result_head == NULL) 
            {
                result_head = new_node;
                result_tail = new_node;
            } 
            else 
            {
                result_tail->next = new_node;
                result_tail = new_node;
            }
        }
        head = head->next;
    }
    return result_head;
}

void printList(Node* head) 
{
    while (head != NULL) 
    {
        printf("Date: %02d.%02d.%02d, Temperature: %d\n", head->day, head->month, head->year, head->temperature);
        head = head->next;
    }
}

void freeList(Node* head) 
{
    Node* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}