#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

struct node {
    int value;
    char* key;
    struct node* next;
};

static unsigned int hash(const char* str, unsigned int size);

struct node** createHashMap(unsigned int size);

int insertValue(struct node** map, unsigned int size, const char* key, int val);

struct node* getVal(struct node** map, unsigned int size, const char* key);

void deleteHashMap(struct node** map, unsigned int size);