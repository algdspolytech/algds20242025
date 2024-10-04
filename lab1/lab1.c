#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#include <stdio.h>
#include "test.h"
//#include "lab1.h"


int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);


	test();
	printf("Test succeeded\n");
	return 0;
}


list_t* Push_LinkedStack(list_t* p, int data) {
	list_t* t = (list_t*)malloc(sizeof(list_t));
	if (t == NULL) {
		free(t);
		printf("MEMORY ALLOCATION ERROR\n");
		return p;
	}
	list_t* a = t;
	a->data = data;
	a->next = p;
	return a;
}

list_t* Pop_LinkedStack(list_t* p) {
	if (p == NULL) {
		printf("There are no more elements\n");
		return NULL;
	}
	list_t* p1 = p->next;
	free(p);
	return p1;
}

int Peek_LinkedStack(list_t* p) {
	if (p == NULL)
		return 666;              //пустой стэк
	return p->data;
}

array_t* Create_ArrayStack(int capacity) {
	if (capacity <= 0)
		return NULL;
	array_t* t = (array_t*)malloc(sizeof(array_t));
	if (t == NULL)
		return NULL;
	array_t* stack = t;
	stack->last = -1;
	stack->capacity = capacity;
	int* t1 = (int*)malloc(sizeof(int) * capacity);
	if (t1 == NULL)
		return NULL;
	stack->array = t1;
	return stack;
}

int IncreazeCapacity_ArrayStack(array_t* p) {
	int* t = realloc(p->array, p->capacity * 2 * sizeof(int));
	if (t != NULL) 
		p->array = t;
	else {
		free(p->array);
		printf("MEMORY ALLOCATION ERROR\n");
		return 1;
	}
	p->capacity *= 2;
	return 0;
}

int IsFull_ArrayStack(array_t* p) {
	return (p->last == (p->capacity - 1));
}

int IsEmpty_ArrayStack(array_t* p) {
	return p->last == -1;
}

int Push_ArrayStack(array_t* p, int data) {
	if (IsFull_ArrayStack(p))
		if (IncreazeCapacity_ArrayStack(p) == 1)
			return 666;
	p->array[++p->last] = data;
	return data;
}

int Pop_ArrayStack(array_t* p) {
	if (IsEmpty_ArrayStack(p)) {
		printf("There are no more elements\n");
		return 666;
	}
	int data = p->array[p->last];
	p->last--;
	return data;
}

int Peek_ArrayStack(array_t* p) {
	if (p->last == -1)
		return 666;               //пустой стэк
	return p->array[p->last];
}

void Free_ArrayStack(array_t* p) {
	free(p->array);
	free(p);
}