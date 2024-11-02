#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LEN 100
#define MAX_LEN_FILE 5

typedef struct
{
	char surname[MAX_LEN];
	char name[MAX_LEN];
	char patronymic[MAX_LEN];
} Full_name;


FILE* init(const char* filename);
int compare(const void* a, const void* b);
int adding(FILE* file, Full_name* arr);
void find(Full_name* arr, int n);

int find_testable(Full_name* people, int count, const char* surname, const char* name, const char* patronymic, char found_surnames[][50]);

#endif