#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TABLE_SIZE 100

extern char* table[TABLE_SIZE];

unsigned int hash(const char* str);
char* my_strdup(const char* str);
int insert(const char* str);
int search(const char* str);
void free_table(void);