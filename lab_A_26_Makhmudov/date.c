#include "date.h"

#define M 12 // months in a year

List* ReadList(char filename[]) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    List* root = NULL;
    List** node;

    int day, month, year;
    float t;
    char format[] = "%d/%d/%d %f\n";

    if (fp) {

        while (fscanf(fp, format, &day, &month, &year, &t) == 4) {

            node = &root;

            while (*node != NULL) {
                if ((*node)->t > t ||
                    ((*node)->t == t &&
                        ((((*node)->month + (*node)->year * M) > (month + year * M)) ||
                            ((((*node)->month + (*node)->year * M) == (month + year * M)) &&
                                ((*node)->day > day))))) { 
                    //huge condition because we need to compare two dates
                    InsertBefore(*node, day, month, year, t);
                    break;
                }
                else
                    node = &(*node)->next;
            }

            if (*node == NULL) {
                *node = CreateNode(day, month, year, t);
            }
        }

        fclose(fp);
    }


    return root;
}

void PrintList(List* node) {
    for (; node != NULL; node = node->next)
        printf("%d/%d/%d %.4f\n", node->day, node->month, node->year, node->t);
}

void PrintListBelowZero(List* node) {
    for (; node != NULL && node->t < 0.0; node = node->next)
        printf("%d/%d/%d %.4f\n", node->day, node->month, node->year, node->t);
}

List* Clear(List* node) {
    while (node != NULL) {
        List* temp = node;
        node = node->next;

        free(temp);
    }
    return node;
}

int Search(List* node, float t) {

    while (node != NULL) {

        if (node->t == t)
            return 1;

        node = node->next;
    }
    return 0;
}

List* CreateNode(int day, int month, int year, float temperature) {
    List* temp = malloc(sizeof(List));

    if (temp != NULL) {
        temp->day = day;
        temp->month = month;
        temp->year = year;
        temp->t = temperature;
        temp->next = NULL;
    }

    return temp;
}

void InsertBefore(List* node, int day, int month, int year,
    float temperature) {
    List* temp = malloc(sizeof(List));

    if (temp != NULL && node != NULL) {
        temp->day = node->day;
        temp->month = node->month;
        temp->year = node->year;
        temp->t = node->t;

        temp->next = node->next;
        node->next = temp;

        node->day = day;
        node->month = month;
        node->year = year;
        node->t = temperature;
    }
}
