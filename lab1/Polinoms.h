#pragma once
#include<stdio.h>

struct monom
{
	int coef;
	int pow;
	struct monom* next;
};
//очередь
struct Queue
{
	struct monom* first, * last;
};

void Add2Queue(struct Queue* q, int coef, int pow);
void InitQueue(struct Queue* q);
int atoistr(char* buf);
void ReadPol(FILE* F, struct Queue* q);
void Sort(struct Queue* q);
void SupPol(struct Queue* q1, struct Queue* q2, struct Queue* q3);
void WritePol(FILE* F, struct Queue* q);
void SimilarTerm(struct Queue* q);
void MultiplicationPol(struct Queue* q1, struct Queue* q2, struct Queue* q3);
void MultiplicationPol(struct Queue* q1, struct Queue* q2, struct Queue* q3);
void DerPol(struct Queue* q1);

void RunTests();
