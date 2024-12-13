#include "Lab_E.h"


int main() {
	FILE* inp = fopen("input.txt", "r");
	FILE* out1 = fopen("output1.txt", "w");
	FILE* out2 = fopen("output2.txt", "w");

	Node* node = readTree(inp);

	displayTree1(out1, node);
	displayTree2(out2, node);

	fclose(inp);
	fclose(out1);
	fclose(out2);


	out1 = fopen("output1.txt", "r");
	out2 = fopen("output2.txt", "r");

	displayFile(out1);
	displayFile(out2);

	fclose(out1);
	fclose(out2);


	return 0;
}