#pragma once
#include <assert.h>>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

struct algorithmProfessorResult {
    char **arr;
    int size;
};

struct couple {
    char *before;
    char *after;
};

struct getCouplesResult {
    int size;
    struct couple *couples;
};

struct createStrArrayResult {
    char **arr;
    int size;
};

char *readFile(char *path);

void addCharInStr(char **str, char c, int newSize);

struct getCouplesResult getCouples(char *str);

int compareStr(char *x, char *y);

int isExistInStrArray(char **arr, int size, char *str);

void addItemToStrArray(char ***arr, int newSize, char *str);

struct createStrArrayResult createStrArray(struct couple *couples, int size);

void pastSelectedItemBeforeItem(char **arr, int base, int moving);

int isTrueOrder(struct couple *couples, int size, char *x, char *y);

int getStrLength(char *str);

int getMaxSwapNum(int sizeOfArray);

void printStrArr(char **arr, int size);

struct algorithmProfessorResult algorithmProfessor(struct couple *coupls, int sizeCoupls);
