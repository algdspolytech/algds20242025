#include "lab_a.h"

int main() {
	Node* set1 = NULL;
	Node* set2 = NULL;

	AddElem(&set1, 3);
	AddElem(&set1, 1);
	AddElem(&set1, 4);
	AddElem(&set1, 2);
	printf("Set №1: ");
	printSet(set1);

	AddElem(&set2, 4);
	AddElem(&set2, 5);
	AddElem(&set2, 2);
	printf("Set №2: ");
	printSet(set2);

	printf("Union of Set №1 and Set №2: ");
	Node* unionSet = UnionSets(set1, set2);
	printSet(unionSet);

	printf("Intersection of Set №1 and Set №2: ");
	Node* intersectSet = IntersectionSets(set1, set2);
	printSet(intersectSet);

	DeleteElem(&set1, 3);
	printf("Set №1 after removing 3: ");
	printSet(set1);



	return 0;
}