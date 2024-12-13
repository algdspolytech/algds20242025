#include "pch.h"
#include "..//LabE//LabE.cpp"


// Funcion to compare answer and result file
int compare_ans(FILE* f1, FILE* f2) {
	int a, b;
	int r1 = 1;
	int r2 = 1;

	while(r1 != EOF && r2 != EOF) {
		r1 = fscanf(f1, "%i", &a);
		r2 = fscanf(f2, "%i", &b);

		if (a != b)
			return 0;
	}

	if (r1 != r2)
		return 0;
	return 1;
}

TEST(LabETests, ExampleTest__1) {
	FILE* test = fopen("tests\\example.txt", "r");
	
	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\example_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);	
}

TEST(LabETests, EmptyTest__2) {
	FILE* test = fopen("tests\\empty.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\empty_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}

TEST(LabETests, HardTest__3) {
	FILE* test = fopen("tests\\hard.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\hard_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}


TEST(LabETests, InvalidDataTest__4) {
	FILE* test = fopen("tests\\invalid_data.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\invalid_data_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}


TEST(LabETests, NullTest__5) {
	FILE* test = fopen("tests\\null.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\null_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}


TEST(LabETests, SmallTest__6) {
	FILE* test = fopen("tests\\small.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\small_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}

TEST(LabETests, TallTreeTest__7) {
	FILE* test = fopen("tests\\tall_tree.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\tall_tree_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}

TEST(LabETests, OneSideTreeTest__8) {
	FILE* test = fopen("tests\\one_side_tree.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\one_side_tree_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}

TEST(LabETests, BigTest__9) {
	FILE* test = fopen("tests\\big.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\big_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}

TEST(LabETests, Invalid2Test__10) {
	FILE* test = fopen("tests\\invalid2_test.txt", "r");

	TreeNode* tree = read_tree(test);

	calculate_width(tree); // Running solution

	FILE* result = fopen("tests\\res.txt", "w");
	write_tree_width(result, tree); // Saving result of solution
	fclose(result);

	free_tree(tree);

	result = fopen("tests\\res.txt", "r");
	FILE* ans = fopen("tests\\invalid2_ans.txt", "r");

	EXPECT_TRUE(compare_ans(ans, result));

	fclose(result);
	fclose(test);
	fclose(ans);
}