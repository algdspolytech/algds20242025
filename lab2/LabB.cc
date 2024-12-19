#define _CRT_SECURE_NO_WARNINGS
#include "memallocator.h"
#include "stdlib.h"
#include "stdio.h"

#include <stdbool.h>
#include <stdint.h>

#include <time.h>


void del(void** arr, int l, int size) {
	for (int i = l;i < size - 1;i++)
		arr[i] = arr[i + 1];
}


void memalloc_random_actions(int i, int size, int max_queries, int max_allocation_size, bool verbose) {
	int queries = rand() % max_queries;

	void** memories = (void**)malloc(max_queries * sizeof(void*));
	int memories_size = 0;

	for (int query = 0;query < queries;query++) {
		if (verbose) printf("Attempt %i. Query %i.\n", i, query);
		if (rand() % 4 == 1) {
			if (verbose) printf("Free\n");
			if (!memories_size)
				continue;

			int mem = rand() % memories_size;

			if (verbose) printf("Freeing %i...\n", mem);
			memfree(memories[mem]);
			del(memories, mem, memories_size);
			memories_size--;
		}
		else {
			if (verbose) printf("Alloc\n");

			int alloc_size = rand() % max_allocation_size;

			if (verbose) printf("Allocating %i bytes...\n", alloc_size);

			void* mem = memalloc(alloc_size);

			memories[memories_size] = mem;
			memories_size++;
		}
	}
	free(memories);
}


double memallocator_random_actions_test(double tests, int seed, bool verbose) {
	clock_t begin = clock();

	const int max_memory_size = 1100;
	const int max_queries = 10;
	const int max_allocation_size = 100;

	srand(seed);
	for (int i = 0;i < tests;i++) {
		int size = rand() % max_memory_size;
		if (verbose) printf("%Memory size: %i\n", size);

		void* memory = malloc(size);
		if (!meminit(memory, size))
			memalloc_random_actions(i, size, max_queries, max_allocation_size, verbose);
		memdone();
		free(memory);
	}

	return (double)(clock() - begin) / CLOCKS_PER_SEC;
}

void malloc_random_actions(int i, int size, int max_queries, int max_allocation_size, bool verbose) {
	int queries = rand() % max_queries;

	void** memories = (void**)malloc(max_queries * sizeof(void*));
	int memories_size = 0;

	for (int query = 0;query < queries;query++) {
		if (verbose) printf("Attempt %i. Query %i.\n", i, query);
		if (rand() % 4 == 1) {
			if (verbose) printf("Free\n");
			if (!memories_size)
				continue;

			int mem = rand() % memories_size;

			if (verbose) printf("Freeing %i...\n", mem);
			free(memories[mem]);
			del(memories, mem, memories_size);
			memories_size--;
		}
		else {
			if (verbose) printf("Alloc\n");

			int alloc_size = rand() % max_allocation_size;

			if (verbose) printf("Allocating %i bytes...\n", alloc_size);

			void* mem = malloc(alloc_size);
			memories[memories_size] = mem;
			memories_size++;
		}
	}

	free(memories);
}

double malloc_random_actions_test(int tests, int seed, bool verbose) {
	clock_t begin = clock();

	const int max_memory_size = 1100;
	const int max_queries = 10;
	const int max_allocation_size = 100;

	srand(seed);
	for (int i = 0;i < tests;i++) {
		int size = rand() % max_memory_size;
		if (verbose) printf("%Memory size: %i\n", size);

		malloc_random_actions(i, size, max_queries, max_allocation_size, verbose);
	}

	return (double)(clock() - begin) / CLOCKS_PER_SEC;
}

// Testing funcs and writing results to files
int main() {
	FILE* out = fopen("memalloc.txt", "w");

	for (double tests = 0;tests < 150000;tests += 5000) {
		printf("%f\n", tests);
		fprintf(out, "%f %f\n", tests, memallocator_random_actions_test(tests, tests, false));
	}
	fclose(out);

	FILE* out1 = fopen("malloc.txt", "w");

	for (double tests = 0;tests < 150000;tests += 5000) {
		printf("%f\n", tests);
		fprintf(out, "%f %f\n", tests, malloc_random_actions_test(tests, tests, false));
	}

	fclose(out1);
}