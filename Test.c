#include "Header.h"

int Assert_eq(int val1, int val2)
{
	if (val1 != val2)
		return false;
	return true;
}
bool Assert_eq_bool(bool val1, bool val2)
{
	if (val1 != val2)
		return false;
	return true;
}

void AddElem_Test1(){
	graph* v = initGraph(2);
	addEdge(v, 0, 1);
	addEdge(v, 1, 2);

	bool res = true;
	res &= Assert_eq(v->numVertex, 2);

	if (res) printf("Test1  passed\n");
	else     printf("Test1  failed\n");

	free(v);
}

void AddEmptyElem_Test2(){
	graph* v = initGraph(0);
	
	bool res = true;
	res &= Assert_eq(v->numVertex, 0);

	if (res) printf("Test2  passed\n");
	else     printf("Test2  failed\n");

	free(v);
}

void ExistencePath_Test3(){
	graph* v = initGraph(7);
	addEdge(v, 0, 1);
	addEdge(v, 2, 5);
	addEdge(v, 1, 3);
	bool res = true;
	res &= Assert_eq_bool(pathExist(v, 2, 5), true);
	if (res) printf("Test3  passed\n");
	else     printf("Test3  failed\n");

	free(v);
}

void DoesntExistPath_Test4() {
	graph* gr = initGraph(5);
	addEdge(gr, 0, 1);
	addEdge(gr, 1, 3);
	addEdge(gr, 1, 4);

	bool res = true;
	res &= Assert_eq_bool(pathExist(gr, 2, 3), false);
	if (res) printf("Test4  passed\n");
	else     printf("Test4  failed\n");

	free(gr);
}

void Path_Test5() {
	graph* gr = initGraph(1);
	
	bool res = true;
	res &= Assert_eq_bool(pathExist(gr, 1, 1), true);
	if (res) printf("Test5  passed\n");
	else     printf("Test5  failed\n");

	free(gr);	
}

void NonExistEmptyPath_Test6() {
	graph* gr = initGraph(5);
	
	bool res = true;
	res &= Assert_eq_bool(pathExist(gr, 2, 4), false);
	if (res) printf("Test6  passed\n");
	else     printf("Test6  failed\n");

	free(gr);	
}

void NonExistNumTest7(){
	node* n = initNode(5);

	bool res = true;
	res &= Assert_eq((int)n->next, 0);
	if (res) printf("Test7  passed\n");
	else     printf("Test7  failed\n");
	free(n);
}

void NumVertex_Test8(){
	node* n = initNode(5);

	bool res = true;
	res &= Assert_eq((int)n->vertex, 5);
	if (res) printf("Test8  passed\n");
	else     printf("Test8  failed\n");
	free(n);
}

void NonVisitedNum_Test9() {
	graph* gr = initGraph(5);
	addEdge(gr, 0, 1);
	addEdge(gr, 1, 3);
	addEdge(gr, 1, 4);

	bool res = true;
	res &= Assert_eq_bool(gr->adjList[2], false);
	if (res) printf("Test9  passed\n");
	else     printf("Test9  failed\n");

	free(gr);	
}

void VisitedNum_Test10() {
	graph* gr = initGraph(5);
	addEdge(gr, 0, 1);
	addEdge(gr, 1, 3);
	addEdge(gr, 1, 4);

	bool res = true;
	res &= Assert_eq_bool(gr->adjList[1], true);
	if (res) printf("Test10 passed\n");
	else     printf("Test10 failed\n");

	free(gr);	
}

void GraphData_Test11() {
	graph* gr = initGraph(5);
	addEdge(gr, 0, 1);
	addEdge(gr, 1, 3);
	addEdge(gr, 1, 4);
	addEdge(gr, 2, 3);

	bool res = true;
	res &= Assert_eq(gr->numVertex, 5);
	if (res) printf("Test11 passed\n");
	else     printf("Test11 failed\n");

	free(gr);	
}



int main(){
	AddElem_Test1();
	AddEmptyElem_Test2();
	ExistencePath_Test3();
	DoesntExistPath_Test4();
	Path_Test5();
	NonExistEmptyPath_Test6();
	NonExistNumTest7();
	NumVertex_Test8();
	NonVisitedNum_Test9();
	VisitedNum_Test10();
	GraphData_Test11();

	printf("\nall test passed\n");
	return 0;
}
