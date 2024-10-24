#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable:4996)

typedef struct {
	int day;
	int month;
	int year;
} Date;

typedef struct Node {
	int hours;
	Date date;
	char name[20];
	char surname[20];
	struct Node* next;
} Node;

typedef struct HourCounter {
	Date date;
	char* name;
	char* surname;
	int total;
} HourCounter;

#ifdef __cplusplus

extern "C" {
#endif

	char* fullname(char* surname, char* name);
	Node* add_sort_list(Node* head, Node* New);
	Node* parse_line(char* line);
	Node* read_file(char* filename);
	void print_filtered_list(Node* head, int N);
	HourCounter* count_hours(Node* head, int* count);
	void free_all(Node** head);

#ifdef __cplusplus
}
#endif
