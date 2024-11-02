#ifndef STACK
#define STACK
typedef struct Stack {
	int size;
	int* values;
} Stack;

void initStack(int n, int* stack);
void push(Stack st, int element);
int pop(Stack st);
#endif