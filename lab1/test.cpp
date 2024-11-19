#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "SubtreeWidth.h"
#include "C:\Users\nasty\source\repos\Lab4\SubtreeWidth\SubtreeWidth.c"

TEST(DataWidthTest, return_data_width_no1) {
	int data = 100;
	int width = DataWidth(data);
	EXPECT_EQ(width, 3);
}

TEST(TreeWidthTest, leaf_width_is_data_width_no2) {
	Tree_t t = { 10, NULL, NULL, 0 };
	TreeWidth(&t);
	EXPECT_EQ(t.width, 2);
}

TEST(TreeWidthTest, root_width_is_tree_width_no3) {
	Tree_t t1 = { 10, NULL, NULL, 0 };
	Tree_t t2 = { 1, NULL, NULL, 0 };
	Tree_t t3 = { 1, &t1, NULL, 0 };
	Tree_t t4 = { 10, &t3, &t2, 0 };

	TreeWidth(&t4);

	EXPECT_EQ(t4.width, 6);
}

TEST(TreeWidthTest, child_width_is_subtree_width_no4) {
	Tree_t t1 = { 10, NULL, NULL, 0 };
	Tree_t t2 = { 1, &t1, NULL, 0 };
	Tree_t t3 = { 10, &t2, NULL, 0 };

	TreeWidth(&t3);

	EXPECT_EQ(t2.width, 3);
}

TEST(TreeHeightTest, tree_ptr_is_null_return_0_no5) {
	Tree_t* ptr = NULL;
	int height = TreeHeight(ptr);
	EXPECT_EQ(height, 0);
}

TEST(TreeHeightTest, tree_not_null_return_tree_height_no6) {
	Tree_t t1 = { 10, NULL, NULL, 0 };
	Tree_t t2 = { 1, NULL, NULL, 0 };
	Tree_t t3 = { 1, &t1, NULL, 0 };
	Tree_t t4 = { 10, &t3, &t2, 0 };

	int height = TreeHeight(&t4);

	EXPECT_EQ(height, 3);
}

TEST(IntToCharTest, return_digit_symbol_no7) {
	int digit = 5;
	char ch = IntToChar(digit);
	EXPECT_EQ(ch, '5');
}

TEST(WriteDataTest, data_written_into_matrix_no8) {
	int data = 1234;
	char** matrix = (char**)malloc(sizeof(char*));
	matrix[0] = (char*)malloc(sizeof(char) * 4);
	
	WriteData(data, matrix, 0, 0);

	char chdata[5] = "1234";
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(matrix[0][i], chdata[i]);
	}

	free(matrix[0]);
	free(matrix);
}

TEST(TreeToMatrixTest, tree_ptr_is_null_matrix_unchanged_no9) {
	char** matrix = (char**)malloc(sizeof(char*));
	matrix[0] = (char*)malloc(sizeof(char) * 4);
	for (int i = 0; i < 4; i++) {
		matrix[0][i] = ' ';
	}
	Tree_t* ptr = NULL;

	int x = 0;
	TreeToMatrix(ptr, matrix, &x, 0);

	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(matrix[0][i], ' ');
	}

	free(matrix[0]);
	free(matrix);
}

TEST(TreeToMatrixTest, tree_not_null_tree_written_to_matrix_no10) {
	Tree_t t1 = { 1, NULL, NULL, 1 };
	Tree_t t2 = { 1, NULL, NULL, 1 };
	Tree_t t3 = { 10, &t1, &t2, 4 };

	char** matrix = (char**)malloc(sizeof(char*) * 4);
	for (int i = 0; i < 4; i++) {
		matrix[i] = (char*)malloc(sizeof(char) * 4);
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = ' ';
		}
	}

	int x = 0;
	TreeToMatrix(&t3, matrix, &x, 0);

	char correctMatrix[5][5] = { " 10 ", " 4  ", "1  1", "1  1" };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			EXPECT_EQ(matrix[i][j], correctMatrix[i][j]);
		}
	}

	for (int i = 0; i < 4; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

TEST(PrintTreeTest, tree_printed_no11) {
	Tree_t t1 = { 1, NULL, NULL, 1 };
	Tree_t t2 = { 1, NULL, NULL, 1 };
	Tree_t t3 = { 10, &t1, &t2, 4 };
	PrintTree(&t3);
}


