#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

#define TABLE_SIZE 101
typedef enum { EMPTY, OCCUPIED, DELETED } CellState;

char* table[TABLE_SIZE];
CellState state[TABLE_SIZE];

unsigned int hash(const char* str);
char* copystr(const char* str);
int insert(const char* str);
int search(const char* str);
int del(const char* str);
void freetable();