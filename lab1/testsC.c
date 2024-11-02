#include "tests.h"
#include "matrix.h"
#include "search.h"
#include "stack.h"
#include <assert.h>

void runAllTests() {

	push_Standart_CorrectAddition();
	push_OverflowStack_SaveOldStateStack();
	push_TryingAddNegativeInteger_SaveOldStateStack();

	pop_Standart_return2();
	pop_EmptyStack_returnMinusOne();
	pop_SeveralPops_return1();

	initMA_Standart_returnZerosMatrix();
	initMA_NonPositiveDemension_returnNULL();
	killMatrix_Standart_returnZero();
	killMatrix_NullDoublePointer_returnOne();

	CheckWay_UndirectedGraph_returnOne();
	CheckWay_DirectedGraph_returnZero();
}

void push_Standart_CorrectAddition() {
	int n = 1;
	int values[n];
	values[0] = -1;
	Stack newStack = { n, values };
	push(newStack, 1);
	assert(newStack.values[0] == 1);
}

void push_OverflowStack_SaveOldStateStack() {
	int n = 1;
	int* values;
	values[0] = 1;
	Stack newStack = { n, values };
	push(newStack, 2);
	assert(newStack.values[0] == 1);
}

void push_TryingAddNegativeInteger_SaveOldStateStack() {
	int n = 2;
	int* values;
	values[0] = 1;
	values[1] = -1;
	Stack newStack = { n, values };
	push(newStack, -2);
	assert(newStack.values[1] == -1);
}

void pop_Standart_return2() {
	int n = 3;
	int* values;
	values[0] = 1;
	values[1] = 2;
	values[2] = -1;
	Stack newStack = { n, values };
	int res = pop(newStack);
	assert(res == 2);
}

void pop_EmptyStack_returnMinusOne() {
	int n = 1;
	int* values;
	values[0] = -1;
	Stack newStack = { n, values };
	int res = pop(newStack);
	assert(res == -1);
}

void pop_SeveralPops_return1() {
	int n = 2;
	int* values;
	values[0] = 1;
	values[1] = 2;
	Stack newStack = { n, values };
	pop(newStack);
	int last_res = pop(newStack);
	assert(last_res == 1);
}

void initMA_Standart_returnZerosMatrix() {
	int n = 2;
	int** res = initMA(n);

	int** zeros = calloc(n, sizeof(int*));
	zeros[0] = calloc(n, sizeof(int));
	zeros[1] = calloc(n, sizeof(int));
	assert(compareMatrixes(res, zeros, n));
}

void initMA_NonPositiveDemension_returnNULL() {
	int n = 0;
	int** res = initMA(n);

	assert(res == NULL);
}

void killMatrix_Standart_returnZero() {
	int n = 2;
	int** MA = calloc(n, sizeof(int*));
	MA[0] = calloc(n, sizeof(int));
	MA[1] = calloc(n, sizeof(int));
	int res = killMatrix(MA, n);
	assert(res == 0);
}

void killMatrix_NullDoublePointer_returnOne() {
	int n = 2;
	int** MA = NULL;
	int res = killMatrix(MA, n);
	assert(res == 1);
}

void CheckWay_UndirectedGraph_returnOne() {
	int n = 2;
	int** MA = calloc(n, sizeof(int*));
	MA[0] = calloc(n, sizeof(int));
	MA[1] = calloc(n, sizeof(int));

	MA[0][1] = 1;
	MA[1][0] = 1;

	int res = CheckWay(n, MA, 2, 1);
	assert(res == 1);
}

void CheckWay_DirectedGraph_returnZero() {
	int n = 2;
	int** MA = calloc(n, sizeof(int*));
	MA[0] = calloc(n, sizeof(int));
	MA[1] = calloc(n, sizeof(int));

	MA[0][1] = 1;

	int res = CheckWay(n, MA, 2, 1);
	assert(res == 0);
}