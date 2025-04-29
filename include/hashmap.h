#pragma once

#ifdef __cplusplus
extern "C" { 
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <assert.h>

struct node {
    int value;
    char* key;
    struct node* next;
};

unsigned int hash(const char* str, unsigned int size);

struct node** createHashMap(unsigned int size);

void insertValue(struct node** map, unsigned int size, const char* key, int val);

struct node* getVal(struct node** map, unsigned int size, const char* key);

void deleteHashMap(struct node** map, unsigned int size);

#ifdef __cplusplus
}
#endif