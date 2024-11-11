#pragma once 
#include <assert.h>
#include "lab4.h"

void Read_txt_FilePointerIsNull_returnNegativeOne() {
	char* ptrtxt = "not_exist.txt";
	char* A = NULL;
	int B = 0;
	assert(Read_txt(ptrtxt, A, B) == -1);
}

void Read_txt_FilePointerExist_returnPositive() {
	char* A = (char*)malloc(100 * sizeof(char));
	int B = 0;
	char* InputFile = "lab4/input.txt";
	assert(Read_txt(InputFile, A, &B) > 0);
	free(A);
}

void Create_Search_NULL_returnNULL() {
	char* A = NULL;
	int n = 0;
	assert(Create_Search(n, A) == NULL);
}


void Create_Search_NotNULL_returnValidVal() {
	char* A = (char*)malloc(100 * sizeof(char));
	int B = 0;
	char* InputFile = "lab4/input.txt";
	int n = Read_txt(InputFile, A, &B);
	list_t** Search = Create_Search(n, A);
	assert(Search[n - 1] == A);
	free(A);
}

void Arithmetic_Negative_returnNULL() {
	char* A = (char*)malloc(100 * sizeof(char));
	int B = 0;
	char* InputFile = "lab4/input.txt";
	int n = Read_txt(InputFile, A, &B);
	B = -1;
	assert(Arithmetic(A, B, n) == NULL);
	free(A);
}

Arithmetic_SolutionExist_returnValidVal() {
	char* A = (char*)malloc(100 * sizeof(char));
	int B = 0;
	char* InputFile = "lab4/input.txt";
	int n = Read_txt(InputFile, A, &B);
	char* Oper = Arithmetic(A, B, n);
	assert(Oper != NULL);
	free(A);
}


void Write_txt_FilePointerExist_returnZero() {
	char* A = (char*)malloc(100 * sizeof(char));
	int B = 0;
	char* InputFile = "lab4/input.txt";
	int n = Read_txt(InputFile, A, &B);   
	char* Oper = Arithmetic(A, B, n);
	char* OutputFile = "lab4/output.txt";
	assert(Write_txt(OutputFile, Oper, A, B, n) == 0);
	free(A);
	free(Oper);
}

void Write_txt_WrongFilePath_returnNegativeOne() {
	char* A = (char*)malloc(100 * sizeof(char));
	int B = 0;
	char* InputFile = "lab4/input.txt";
	int n = Read_txt(InputFile, A, &B);
	char* Oper = Arithmetic(A, B, n);
	char* OutputFile = "not_exist/output.txt";
	assert(Write_txt(OutputFile, Oper, A, B, n) == -1);
	free(A);
	free(Oper);
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


void test() {
	Read_txt_FilePointerExist_returnPositive();
	Read_txt_FilePointerIsNull_returnNegativeOne();
	Create_Search_NULL_returnNULL();
	Create_Search_NotNULL_returnValidVal();
	Arithmetic_Negative_returnNULL();
	Arithmetic_SolutionExist_returnValidVal();
	Write_txt_FilePointerExist_returnZero();
	Write_txt_WrongFilePath_returnNegativeOne();
	Push_LinkedStack_Integer_returnValidVal();
	Pop_LinkedStack_NotEmptyStack_returnValidVal();
	Pop_LinkedStack_EmptyStack_returnNull();
}