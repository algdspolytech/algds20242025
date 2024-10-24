#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include "lib.h"
#include "tests.h"

int main() 
{
    runAllTests();

    FILE* file = fopen("randomTable.csv", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    Node* head = NULL;
    int day;
    int month;
    int year;
    int temperature;

    while (fscanf(file, "%d.%d.%d, %d", &day, &month, &year, &temperature) == 4) 
    {
        head = insertSorted(head, day, month, year, temperature);
    }
    fclose(file);

    printf("Dates with temperature below zero:\n");
    printNegative(head);

    int input_temp;
    printf("Search temperature: ");
    scanf("%d", &input_temp);

    Node* found_list = NULL;
    found_list = searchTemperature(head, input_temp);
    if(found_list == NULL)
    {
        printf("There is no such temperature!");
    }
    printList(found_list);
    freeList(head);

    return 0;
}
