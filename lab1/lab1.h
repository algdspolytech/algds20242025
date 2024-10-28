//
// Created by Александр on 28.10.2024.
//
#pragma once

#include <limits.h>
#define ERROR INT_MIN

typedef struct list_t {
    int data;
    struct list_t* next;
} list_t;

typedef struct {
    int last;
    int capacity;
    int* array;
}array_t;

list_t* Push_LinkedStack(list_t* p, int data);
list_t* Pop_LinkedStack(list_t* p);
int Peek_LinkedStack(list_t* p);
int Push_ArrayStack(array_t* p, int data);
int Pop_ArrayStack(array_t* p);
int Peek_ArrayStack(array_t* p);
array_t* Create_ArrayStack(int capacity);
int IsFull_ArrayStack(array_t* p);
int IsEmpty_ArrayStack(array_t* p);
int IncreazeCapacity_ArrayStack(array_t* p);
void Free_ArrayStack(array_t* p);