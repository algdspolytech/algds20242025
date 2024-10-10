#include <assert.h>
#include "lab1.h"


void Create_ArrayStack_NegativeCapacity_returnNull() {
	assert(Create_ArrayStack(-1) == NULL);
}

void Create_ArrayStack_PositiveCapacity_returnValidVal() {
	array_t* p = Create_ArrayStack(10);
	assert(p->last == -1);
	assert(p->array != NULL);
	assert(p->capacity == 10);
	Free_ArrayStack(p);
}

void IncreazeCapacity_ArrayStack_Automatic_returnValidVal() {
	array_t* p = Create_ArrayStack(1);
	Push_ArrayStack(p, 1);
	Push_ArrayStack(p, 2);
	assert(p->last == 1);
	assert(p->array[p->last] == 2);
	assert(p->capacity == 2);
	Free_ArrayStack(p);
}


void Push_ArrayStack_Integer_returnValidVal() {
	array_t* p = Create_ArrayStack(10);
	assert(Push_ArrayStack(p, 1) == 1);
	assert(p->last == 0);
	assert(p->array[p->last] == 1);
	assert(p->capacity == 10);
	Free_ArrayStack(p);
}

void Push_ArrayStack_Full_returnValidVal() {
	array_t* p = Create_ArrayStack(1);
	assert(Push_ArrayStack(p, 1) == 1);
	assert(Push_ArrayStack(p, 2) == 2);
	assert(p->last == 1);
	assert(p->array[p->last] == 2);
	assert(p->capacity == 2);
	Free_ArrayStack(p);
}

void IsEmpty_ArrayStack_OneElement_returnFalse() {
	array_t* p = Create_ArrayStack(2);
	assert(Push_ArrayStack(p, 1) == 1);
	assert(IsEmpty_ArrayStack(p) == 0);
	Free_ArrayStack(p);
}

void IsEmpty_ArrayStack_EmptyStack_returnTrue() {
	array_t* p = Create_ArrayStack(2);
	assert(IsEmpty_ArrayStack(p) == 1);
	Free_ArrayStack(p);
}

void IsFull_ArrayStack_EmptyStack_returnFalse() {
	array_t* p = Create_ArrayStack(1);
	assert(IsFull_ArrayStack(p) == 0);
	Free_ArrayStack(p);
}

void IsFull_ArrayStack_FullStack_returnTrue() {
	array_t* p = Create_ArrayStack(1);
	assert(Push_ArrayStack(p, 1) == 1);
	assert(IsFull_ArrayStack(p) == 1);
	Free_ArrayStack(p);
}

void Pop_ArrayStack_Integer_returnValidVal() {
	array_t* p = Create_ArrayStack(3);
	Push_ArrayStack(p, 1);
	Push_ArrayStack(p, 2);
	assert(Pop_ArrayStack(p) == 2);
	assert(p->last == 0);
	assert(p->array[p->last] == 1);
	assert(p->capacity == 3);
	Free_ArrayStack(p);
}

void Pop_ArrayStack_Empty_returnValidVal() {
	array_t* p = Create_ArrayStack(1);
	Pop_ArrayStack(p);
	assert(p->last == -1);
	assert(p->capacity == 1);
	Free_ArrayStack(p);
}

void Peek_ArrayStack_Empty_returnERROR() {
	array_t* p = Create_ArrayStack(1);
	assert(Peek_ArrayStack(p) == ERROR);
	Free_ArrayStack(p);
}

void Peek_ArrayStack_NotEmpty_returnInteger() {
	array_t* p = Create_ArrayStack(1);
	Push_ArrayStack(p, 1);
	assert(Peek_ArrayStack(p) == 1);
	Free_ArrayStack(p);
}

void Push_LinkedStack_Integer_returnValidVal() {
	list_t* p = NULL;
	p = Push_LinkedStack(p, 1);
	assert(p->data == 1);
	assert(p->next == NULL);
	p = Pop_LinkedStack(p);
}

void Pop_LinkedStack_NotEmptyStack_returnValidVal() {
	list_t* p = NULL;
	p = Push_LinkedStack(p, 1);
	p = Push_LinkedStack(p, 2);
	p = Pop_LinkedStack(p);
	assert(p->data == 1);
	assert(p->next == NULL);
	p = Pop_LinkedStack(p);
}

void Pop_LinkedStack_EmptyStack_returnNull() {
	list_t* p = NULL;
	p = Pop_LinkedStack(p);
	assert(p == NULL);
}

void Peek_LinkedStack_NotEmpty_returnInteger() {
	list_t* p = NULL;
	p = Push_LinkedStack(p, 1);
	assert(Peek_LinkedStack(p) == 1);
	p = Pop_LinkedStack(p);
}

void Peek_LinkedStack_Empty_returnERROR() {
	list_t* p = NULL;
	assert(Peek_LinkedStack(p) == ERROR);
}

void test() {
	Create_ArrayStack_NegativeCapacity_returnNull();
	Create_ArrayStack_PositiveCapacity_returnValidVal();
	IncreazeCapacity_ArrayStack_Automatic_returnValidVal();
	Push_ArrayStack_Integer_returnValidVal();
	Push_ArrayStack_Full_returnValidVal();
	IsEmpty_ArrayStack_OneElement_returnFalse();
	IsEmpty_ArrayStack_EmptyStack_returnTrue();
	IsFull_ArrayStack_EmptyStack_returnFalse();
	IsFull_ArrayStack_FullStack_returnTrue();
	Pop_ArrayStack_Integer_returnValidVal();
	Pop_ArrayStack_Empty_returnValidVal();
	Peek_ArrayStack_NotEmpty_returnInteger();
	Peek_ArrayStack_Empty_returnERROR();
	Push_LinkedStack_Integer_returnValidVal();
	Pop_LinkedStack_NotEmptyStack_returnValidVal();
	Pop_LinkedStack_EmptyStack_returnNull();
	Peek_LinkedStack_NotEmpty_returnInteger();
	Peek_LinkedStack_Empty_returnERROR();
}