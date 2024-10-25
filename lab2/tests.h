#ifndef TESTS
#define TESTS

void runAllTests();

void push_Standart_CorrectAddition();
void push_OverflowStack_SaveOldStateStack();
void push_TryingAddNegativeInteger_SaveOldStateStack();

void pop_Standart_return2();
void pop_EmptyStack_returnMinusOne();
void pop_SeveralPops_return1();

void initMA_Standart_returnZerosMatrix();
void initMA_NonPositiveDemension_returnNULL();
void killMatrix_Standart_returnZero();
void killMatrix_NullDoublePointer_returnOne();

void CheckWay_UndirectedGraph_returnOne();
void CheckWay_DirectedGraph_returnZero();
#endif