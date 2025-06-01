#pragma once


typedef struct PriorityQueue {
	int data;
	int key;
	struct PriorityQueue* next;
};

#ifdef __cplusplus
extern "C" {
#endif

struct PriorityQueue* PrQcreate(int data, int key);

void PrQclear(struct PriorityQueue* q);

struct PriorityQueue* PrQinsert(struct PriorityQueue* q, int data, int key);

int PrQextractMinimum(struct PriorityQueue* q);

#ifdef __cplusplus
}
#endif