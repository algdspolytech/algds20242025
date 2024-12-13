#include "LabE.h"


int main() {
	FILE* inp = fopen("tree.txt", "r");
	TreeNode* tree = read_tree(inp);

	calculate_width(tree);

	display_tree(tree);

	FILE* out = fopen("output.txt", "w");
	write_tree_width(out, tree);

	free_tree(tree);
	fclose(out);
	fclose(inp);

	return 0;
}