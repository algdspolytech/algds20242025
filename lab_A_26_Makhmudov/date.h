#pragma once

#pragma warning(disable : 4996)

#include <stdio.h>

#include <stdlib.h>

#include <string.h>





typedef struct List {
    int day;
    int month;
    int year;
    float t;
    struct List* next;
} List;


List* ReadList(char filename[]);

void PrintList(struct List* node);

void PrintListBelowZero(List* node);

List* Clear(List* node);

int Search(List* node, float t);

List* CreateNode(int day, int month, int year, float temperature);

void InsertBefore(List* node, int day, int month, int year, float temperature);



