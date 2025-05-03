#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

#define TABLE_SIZE 101
typedef enum {EMPTY, OCCUPIED, DELETED} CellState;

static char* table[TABLE_SIZE];
static CellState state[TABLE_SIZE]; // Отслеживаем состояние ячеек

unsigned int hash(const char* str);
char* copy_str(const char* str);
int insert(const char* str);
int search(const char* str);
int del(const char* str);
void free_table();