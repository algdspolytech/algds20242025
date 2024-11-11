#pragma once
typedef struct list_t {
	int data;
	struct list_t* next;
} list_t;

int Read_txt(char const* filename, char* A, int* B);
int Write_txt(char const* filename, char* Oper, char* A, int B, int n);
list_t* Push_LinkedStack(list_t* p, int data);
list_t* Pop_LinkedStack(list_t* p);
void Free_LinkedStack(list_t* p);
list_t** Create_Search(int n, list_t* A);
char* Arithmetic(const char* A, const int B, int n);
