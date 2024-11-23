#include "test.h"


void compareGraphs_OneElementGraphs_ruturnTrue() {
	GraphAdjList* g1 = createGraphAdjList(2);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(2);
	addEdgeAdjList(g1, 1, 0);
	addEdgeAdjMatrix(g2, 1, 0);
	assert(compareGraphs(g1, g2));
}

void compareGraphs_OneLoopingElementGraphs_ruturnTrue() {
	GraphAdjList* g1 = createGraphAdjList(1);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(1);
	addEdgeAdjList(g1, 0, 0);
	addEdgeAdjMatrix(g2, 0, 0);
	assert(compareGraphs(g1, g2));
}


void compareGraphs_EmptyGraphs_ruturnTrue() {
	GraphAdjList* g1 = createGraphAdjList(1);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(1);
	assert(compareGraphs(g1, g2));
}


void compareGraphs_ZeroElements_ruturnTrue() {
	GraphAdjList* g1 = createGraphAdjList(0);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(0);
	assert(compareGraphs(g1, g2));
}


void compareGraphs_ManyElementsGraphs_ruturnTrue() {
	GraphAdjList* g1 = createGraphAdjList(4);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(4);
	addEdgeAdjList(g1, 1, 0);
	addEdgeAdjList(g1, 1, 2);
	addEdgeAdjList(g1, 2, 3);
	addEdgeAdjList(g1, 3, 0);
	addEdgeAdjMatrix(g2, 1, 0);
	addEdgeAdjMatrix(g2, 1, 2);
	addEdgeAdjMatrix(g2, 2, 3);
	addEdgeAdjMatrix(g2, 3, 0);
	assert(compareGraphs(g1, g2));
}


void compareGraphs_ManyElementsGraphs_ruturnFalse() {
	GraphAdjList* g1 = createGraphAdjList(4);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(4);
	addEdgeAdjList(g1, 1, 0);
	addEdgeAdjList(g1, 1, 2);
	addEdgeAdjList(g1, 2, 3);
	addEdgeAdjList(g1, 3, 0);
	addEdgeAdjMatrix(g2, 1, 0);
	addEdgeAdjMatrix(g2, 1, 2);
	addEdgeAdjMatrix(g2, 2, 3);
	assert(!compareGraphs(g1, g2));
}


void compareGraphs_DifferentOrder_ruturnTrue() {
	GraphAdjList* g1 = createGraphAdjList(3);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(3);
	addEdgeAdjList(g1, 0, 2);
	addEdgeAdjList(g1, 1, 0);
	addEdgeAdjMatrix(g2, 1, 0);
	addEdgeAdjMatrix(g2, 0, 2);
	assert(compareGraphs(g1, g2));
}

void compareGraphs_DifferentDirection_ruturnFalse() {
	GraphAdjList* g1 = createGraphAdjList(2);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(2);
	addEdgeAdjList(g1, 0, 1);
	addEdgeAdjMatrix(g2, 1, 0);
	assert(!compareGraphs(g1, g2));
}


void compareGraphs_DifferentSizes_ruturnFalse() {
	GraphAdjList* g1 = createGraphAdjList(3);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(2);
	addEdgeAdjList(g1, 1, 0);
	addEdgeAdjMatrix(g2, 1, 0);
	assert(!compareGraphs(g1, g2));
}


void compareGraphs_EmptyAndNormalGraps_ruturnFalse() {
	GraphAdjList* g1 = createGraphAdjList(0);
	GraphAdjMatrix* g2 = createGraphAdjMatrix(2);
	addEdgeAdjMatrix(g2, 1, 0);
	assert(!compareGraphs(g1, g2));
}


void run_all_tests() {
	compareGraphs_OneElementGraphs_ruturnTrue();
	compareGraphs_OneLoopingElementGraphs_ruturnTrue();
	compareGraphs_EmptyGraphs_ruturnTrue();
	compareGraphs_ZeroElements_ruturnTrue();
	compareGraphs_ManyElementsGraphs_ruturnTrue();
	compareGraphs_ManyElementsGraphs_ruturnFalse();
	compareGraphs_DifferentOrder_ruturnTrue();
	compareGraphs_DifferentDirection_ruturnFalse();
	compareGraphs_DifferentSizes_ruturnFalse();
	compareGraphs_EmptyAndNormalGraps_ruturnFalse();
	printf("All tests completed successfully.\n");
}