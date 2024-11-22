#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "NQueens.h"
#include "C:\Users\nasty\source\repos\Lab3\NQueens\NQueens.c"

TEST(CheckPosTest, position_attacked_return_0_no1) {
	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * 2);
	for (int i = 0; i < 2; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * 2);
	}
	board[0][0] = YES;
	board[0][1] = NO;
	board[1][0] = NO;
	board[1][1] = NO;

	int res = CheckPos(board, 1, 1, 2);
	EXPECT_EQ(res, 0);

	for (int i = 0; i < 2; i++) {
		free(board[i]);
	}
	free(board);
}

TEST(CheckPosTest, position_free_return_1_no2) {
	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * 2);
	for (int i = 0; i < 2; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * 2);
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			board[i][j] = NO;
		}
	}

	int res = CheckPos(board, 1, 1, 2);
	EXPECT_EQ(res, 1);

	for (int i = 0; i < 2; i++) {
		free(board[i]);
	}
	free(board);
}

TEST(FindSolutionTestReturn, no_solution_return_0_no3) {
	int n = 3;
	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * n);
	for (int i = 0; i < n; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = NO;
		}
	}

	int res = FindSolution(n, board, 0);
	EXPECT_EQ(res, 0);

	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

TEST(FindSolutionTestReturn, solution_found_return_1_no4) {
	int n = 4;
	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * n);
	for (int i = 0; i < n; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = NO;
		}
	}

	int res = FindSolution(n, board, 0);
	EXPECT_EQ(res, 1);

	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

TEST(FindSolutionTestSolution, solution_found_board_contains_solution_no5) {
	int n = 4;
	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * n);
	for (int i = 0; i < n; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = NO;
		}
	}

	Flag_t solution[4][4] = { {NO, NO, YES, NO}, {YES, NO, NO, NO}, {NO, NO, NO, YES},
		{NO, YES, NO, NO} };

	int res = FindSolution(n, board, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			EXPECT_EQ(board[i][j], solution[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

TEST(FindSolutionTestSolution, no_solution_all_squares_of_board_are_NO_no6) {
	int n = 3;
	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * n);
	for (int i = 0; i < n; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = NO;
		}
	}

	int res = FindSolution(n, board, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			EXPECT_EQ(board[i][j], NO);
		}
	}

	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

TEST(NQueensTestReturn, invalid_board_size_return_0_no7) {
	char* inputFilename = "input_invalid_board_size.txt";
	char* outputFilename = "output_invalid_board_size.txt";

	int res = NQueens(inputFilename, outputFilename);
	EXPECT_EQ(res, 0);
}

TEST(NQueensTestReturn, no_solution_return_0_no8) {
	char* inputFilename = "input_no_solution.txt";
	char* outputFilename = "output_no_solution.txt";

	int res = NQueens(inputFilename, outputFilename);
	EXPECT_EQ(res, 0);
}

TEST(NQueensTestReturn, solution_found_return_1_no9) {
	char* inputFilename = "input.txt";
	char* outputFilename = "output.txt";

	int res = NQueens(inputFilename, outputFilename);
	EXPECT_EQ(res, 1);
}

TEST(NQueensTestSolution, solution_found_output_file_contains_solution_no10) {
	char* inputFilename = "input.txt";
	char* outputFilename = "output.txt";

	int res = NQueens(inputFilename, outputFilename);

	FILE* outputFile = fopen(outputFilename, "r");
	char correctOutput[4][2] = { {'0', '1'}, {'1', '3'}, {'2', '0'}, {'3', '2'} };
	char output[2];

	for (int i = 0; i < 4; i++) {
		fscanf(outputFile, "%c %c\n", &output[0], &output[1]);
		EXPECT_EQ(output[0], correctOutput[i][0]);
		EXPECT_EQ(output[1], correctOutput[i][1]);
	}
	fclose(outputFile);
}

TEST(NQueensTestSolution, no_solution_no_solution_text_written_in_output_file_no11) {
	char* inputFilename = "input_no_solution.txt";
	char* outputFilename = "output_no_solution.txt";

	int res = NQueens(inputFilename, outputFilename);

	FILE* outputFile = fopen(outputFilename, "r");
	char correctOutput[14] = "no solution!\n";
	char output[14];
	for (int i = 0; i < 13; i++) {
		fscanf(outputFile, "%c", &output[i]);
		EXPECT_EQ(output[i], correctOutput[i]);
	}
	fclose(outputFile);
}