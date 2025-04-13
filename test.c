#include <assert.h>
#include "code.h"


void OneElementGraphs() {
	Graph_l* g1 = createGraph_l(2);
	Graph_m* g2 = createGraph_m(2);
	add_l(g1, 1, 0);
	add_m(g2, 1, 0);
	assert(compareGraphs(g1, g2));
}

void OneLoopingElementGraphs() {
	Graph_l* g1 = createGraph_l(1);
	Graph_m* g2 = createGraph_m(1);
	add_l(g1, 0, 0);
	add_m(g2, 0, 0);
	assert(compareGraphs(g1, g2));
}


void EmptyGraphs() {
	Graph_l* g1 = createGraph_l(1);
	Graph_m* g2 = createGraph_m(1);
	assert(compareGraphs(g1, g2));
}


void ZeroElements() {
	Graph_l* g1 = createGraph_l(0);
	GraphAdjMatrix* g2 = createGraph_m(0);
	assert(compareGraphs(g1, g2));
}


void ManyElementsGraphs_True() {
	Graph_l* g1 = createGraph_l(4);
	Graph_m* g2 = createGraph_m(4);
	add_l(g1, 1, 0);
	add_l(g1, 1, 3);
	add_l(g1, 2, 1);
	add_l(g1, 3, 0);
	add_m(g2, 1, 0);
	add_m(g2, 1, 3);
	add_m(g2, 2, 1);
	add_m(g2, 3, 0);
	assert(compareGraphs(g1, g2));
}


void ManyElementsGraphs_False() {
	Graph_l* g1 = createGraph_l(4);
	Graph_m* g2 = createGraph_m(4);
	add_l(g1, 1, 0);
	add_l(g1, 1, 3);
	add_l(g1, 2, 1);
	add_l(g1, 3, 0);
	add_m(g2, 1, 0);
	add_m(g2, 1, 3);
	add_m(g2, 2, 1);
	assert(!compareGraphs(g1, g2));
}


void DifferentOrder() {
	Graph_l* g1 = createGraph_l(3);
	Graph_m* g2 = createGraph_m(3);
	add_l(g1, 1, 2);
	add_l(g1, 1, 0);
	add_m(g2, 1, 0);
	add_m(g2, 1, 2);
	assert(compareGraphs(g1, g2));
}

void DifferentDirection() {
	Graph_l* g1 = createGraph_l(2);
	Graph_m* g2 = createGraph_m(2);
	add_l(g1, 0, 1);
	add_m(g2, 1, 0);
	assert(!compareGraphs(g1, g2));
}


void DifferentSizes() {
	Graph_l* g1 = createGraph_l(5);
	Graph_m* g2 = createGraph_m(2);
	add_l(g1, 1, 0);
	add_m(g2, 1, 0);
	assert(!compareGraphs(g1, g2));
}


void EmptyAndNormalGraps() {
	Graph_l* g1 = createGraph_l(0);
	Graph_m* g2 = createGraph_m(2);
	add_m(g2, 1, 0);
	assert(!compareGraphs(g1, g2));
}


void run_all_tests() {
	OneElementGraphs();
	OneLoopingElementGraphs();
	EmptyGraphs();
	ZeroElements();
	ManyElementsGraphs_True();
	ManyElementsGraphs_False();
	DifferentOrder();
	DifferentDirection();
	DifferentSizes();
	EmptyAndNormalGraps();
	printf("All tests completed successfully.\n");
}

int main()
{
	run_all_tests();
	return 0;
}