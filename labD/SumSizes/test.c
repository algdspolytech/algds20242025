#include "test.h"


int compare(int* a, int* b, int len_a, int len_b) {
	if (len_a != len_b) return 0;
	for (int i = 0; i < len_a; i++) {
		if (a[i] != b[i]) return 0;
	}
	return 1;
}


void subsetSum_ExampleTest_returnValue() {
	int B = 10, N = 5;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 2;
	A[1] = 3;
	A[2] = 4;
	A[3] = 5;
	A[4] = 9;
	int* a = NULL;
	int len_a = subsetSum(B, A, N, &a);

	int len_b = 3;
	int* b;
	b = (int*)malloc((len_b) * sizeof(int));
	b[0] = 2;
	b[1] = 3;
	b[2] = 5;
	assert(compare(a, b, len_a, len_b));
}


void subsetSum_tooBigB_return0() {
	int B = 42, N = 5;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 2;
	A[1] = 3;
	A[2] = 4;
	A[3] = 5;
	A[4] = 9;
	int* a = NULL;
	assert(!subsetSum(B, A, N, &a));
}


void subsetSum_OneElement_returnValue() {
	int B = 10, N = 1;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 10;
	int* a = NULL;
	int len_a = subsetSum(B, A, N, &a);

	int len_b = 1;
	int* b;
	b = (int*)malloc((len_b) * sizeof(int));
	b[0] = 10;
	assert(compare(a, b, len_a, len_b));
}


void subsetSum_OneElement_return0() {
	int B = 10, N = 1;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 11;
	int* a = NULL;
	assert(!subsetSum(B, A, N, &a));
}


void subsetSum_NoAnswer_return0() {
	int B = 7, N = 5;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 1;
	A[1] = 5;
	A[2] = 4;
	A[3] = 5;
	A[4] = 9;
	int* a = NULL;
	assert(!subsetSum(B, A, N, &a));
}


void subsetSum_ManyAnwers_returnValue() {
	int B = 6, N = 5;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 3;
	A[1] = 3;
	A[2] = 4;
	A[3] = 2;
	A[4] = 6;
	int* a = NULL;
	int len_a = subsetSum(B, A, N, &a);

	int len_b = 2;
	int* b;
	b = (int*)malloc((len_b) * sizeof(int));
	b[0] = 3;
	b[1] = 3;
	assert(compare(a, b, len_a, len_b));
}


void subsetSum_IdenticalElements_returnValue() {
	int B = 8, N = 3;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 4;
	A[1] = 4;
	A[2] = 4;
	int* a = NULL;
	int len_a = subsetSum(B, A, N, &a);

	int len_b = 2;
	int* b;
	b = (int*)malloc((len_b) * sizeof(int));
	b[0] = 4;
	b[1] = 4;
	assert(compare(a, b, len_a, len_b));
}


void subsetSum_EmptyA_return0() {
	int B = 7, N = 0;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	int* a = NULL;
	assert(!subsetSum(B, A, N, &a));
}


void subsetSum_AllElementsMoreThanB_return0() {
	int B = 2, N = 5;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 5;
	A[1] = 6;
	A[2] = 4;
	A[3] = 5;
	A[4] = 9;
	int* a = NULL;
	assert(!subsetSum(B, A, N, &a));
}


void subsetSum_IdenticalElements_return0() {
	int B = 7, N = 3;
	int* A;
	A = (int*)malloc((N) * sizeof(int));
	A[0] = 4;
	A[1] = 4;
	A[2] = 4;
	int* a = NULL;
	assert(!subsetSum(B, A, N, &a));
}

void run_all_tests() {
	subsetSum_ExampleTest_returnValue();
	subsetSum_tooBigB_return0();
	subsetSum_OneElement_returnValue();
	subsetSum_OneElement_return0();
	subsetSum_NoAnswer_return0();
	subsetSum_ManyAnwers_returnValue();
	subsetSum_IdenticalElements_returnValue();
	subsetSum_EmptyA_return0();
	subsetSum_AllElementsMoreThanB_return0();
	subsetSum_IdenticalElements_return0();
	printf("All tests completed successfully.\n");
}