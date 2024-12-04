#pragma once

typedef struct{
	int start;
	int end;
} interval_t;

typedef struct node_t {
	interval_t interval;
	double max_end;
	struct node_t* left;
	struct node_t* right;
}node_t;

node_t* CreateNode(interval_t interval);
node_t* InsertInterval(node_t* node, interval_t interval);
int IsIntersection(interval_t i1, interval_t i2);
interval_t* SearchIntersections(node_t* node, interval_t interval, interval_t* result, int* count);
void UpdateMaxEnd(node_t* node);
node_t* DeleteInterval(node_t* root, interval_t interval);

