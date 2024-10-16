#pragma once
#include "stdio.h"
#include "malloc.h"

typedef struct list
{
    char *str;
    struct list *next;
} list;

int StringComparison(const char *first, const char *second);
list *ListAdd(list *first, char *string);
list *ListDestr(list *first);
void ListSort(list *first);
list *ListFromFile(const char *filename);
