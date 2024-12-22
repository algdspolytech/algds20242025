#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int time;
    int in_degree;
    int* adjacency_list;
    int adjacency_count;
} Wagon;

int wagons_sort(const char* inputfile_name, const char* outputfile_name);