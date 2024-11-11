#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "lab4.h"

int main() {
	test();
	printf("Test succeeded\n");
	getchar();
	getchar();
	return 0;
}


int Read_txt(char const* filename, char* A, int* B) {
	FILE* ptrtxt = fopen(filename, "r");
	if (ptrtxt == NULL) {
		//printf("Error: file pointer is null.\n");
		return -1;
		//exit(1);
	}

	int n = 0;      // the number of digits in A

	do {
		A[n] = fgetc(ptrtxt);
		n++;
	} while ((A[n - 1] != ' ') && (A[n - 1] != '\n') && (A[n - 1] != '\0') && (A[n - 1] != EOF));
	n--;

	*B = 0;
	char c = '0';
	do {
		(*B) = (*B) * 10 + (c - '0');
		c = fgetc(ptrtxt);
	} while ((c != ' ') && (c != '\n') && (c != '\0') && (c != EOF));

	return n;
}

int Write_txt(char const* filename, char* Oper, char* A, int B, int n) {
	FILE* ptrtxt = fopen(filename, "w");
	if (!ptrtxt) {
		//printf("Error while opening file for writing\n");
		return -1;
	}

	if (Oper == NULL) {
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < n - 1; i++) {
		fprintf(ptrtxt, "%c", A[i]);
		if (Oper[i] == 0)
			;
		else if (Oper[i] == 1)
			fprintf(ptrtxt, " + ");
		else if (Oper[i] == 2)
			fprintf(ptrtxt, " - ");
		else if (Oper[i] == 3)
			fprintf(ptrtxt, " * ");
		else if (Oper[i] == 4)
			fprintf(ptrtxt, " / ");
	}
	fprintf(ptrtxt, "%c", A[n - 1]);
	fprintf(ptrtxt, " = %d\n", B);

	fclose(ptrtxt);
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

void Free_LinkedStack(list_t* p) {
	while (p != NULL) {
		p = Pop_LinkedStack(p);
	}
}

list_t** Create_Search(int n, list_t* A) {
	list_t* p = A;
	if (A == NULL)
		return NULL;
	list_t** Search = (list_t**)malloc(n * sizeof(list_t*));
	for (int i = n - 1; i >= 0; i--) {
		Search[i] = p;
		p = p->next;
	}
	return Search;
}

char* Arithmetic(const char* A, const int B, int n) {
	if (B < 0)
		return NULL;

	list_t* Copy_A;
	int res;
	list_t** Search;

	char* Oper = (char*)malloc((n - 1) * sizeof(char));
	for (int i = 0; i < (n - 1); i++) {
		Oper[i] = 0;
	}

	while (Oper[0] != 5) {

		Copy_A = NULL;
		for (int i = 0; i < n; i++) {
			Copy_A = Push_LinkedStack(Copy_A, A[i] - '0');
		}

		Search = Create_Search(n, Copy_A);

		//priority of operations
		for (int i = 0; i < n - 1; i++) {
			if (Oper[i] == 0) {
				Search[i]->data = (Search[i]->data) * 10 + (Search[i + 1]->data);
				Search[i + 1] = Search[i];
			}
		}
		for (int i = 0; i < n - 1; i++) {
			if (Oper[i] == 3) {
				Search[i]->data = (Search[i]->data) * (Search[i + 1]->data);
				Search[i + 1] = Search[i];
			}
			if (Oper[i] == 4) {
				Search[i]->data = (Search[i]->data) / (Search[i + 1]->data);
				Search[i + 1] = Search[i];
			}
		}
		for (int i = 0; i < n - 1; i++) {
			if (Oper[i] == 1) {
				Search[i]->data = (Search[i]->data) + (Search[i + 1]->data);
				Search[i + 1] = Search[i];
			}
			if (Oper[i] == 2) {
				Search[i]->data = (Search[i]->data) - (Search[i + 1]->data);
				Search[i + 1] = Search[i];
			}
		}

		res = Search[0]->data;

		Free_LinkedStack(Copy_A);

		if (res == B)
			return Oper;

		Oper[n - 2]++;
		// 0 : ''; 1 : '+'; 2 : '-'; 3 : '*'; 4 : '/'
		for (int i = n - 2; i > 0; i--) {
			if (Oper[i] == 5) {
				Oper[i] = 0;
				Oper[i - 1]++;
			}
		}
	}

	return NULL;
}
