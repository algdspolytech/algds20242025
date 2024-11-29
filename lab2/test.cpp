#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "Labyrinth.h"
#include "C:\Users\nasty\source\repos\Lab2\Labyrinth\Labyrinth.c"

TEST(FindExitTestReturn, no_exit_return_0_no1) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	int pathsize = 0;

	int exit = FindExit(lab, 0, 0, path, &pathsize);
	EXPECT_EQ(exit, 0);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(FindExitTestReturn, normal_return_1_no2) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	int pathsize = 0;

	int exit = FindExit(lab, 0, 0, path, &pathsize);
	EXPECT_EQ(exit, 1);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(FindExitTestPathsize, no_exit_pathsize_value_not_changed_no3) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	int pathsize = 1;

	int exit = FindExit(lab, 0, 0, path, &pathsize);
	EXPECT_EQ(pathsize, 1);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(FindExitTestPathsize, normal_pathsize_contains_number_of_steps_no4) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	int pathsize = 0;

	int exit = FindExit(lab, 0, 0, path, &pathsize);
	EXPECT_EQ(pathsize, 2);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(FindExitTestPath, no_exit_path_unchanged_no5) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	for (int i = 0; i < 4; i++) {
		path[i] = LEFT;
	}
	int pathsize = 0;

	int exit = FindExit(lab, 0, 0, path, &pathsize);
	
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(path[i], LEFT);
	}

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(FindExitTestPath, normal_path_contains_steps_to_exit_in_reversed_order_no6) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	int pathsize = 0;

	int exit = FindExit(lab, 0, 0, path, &pathsize);
	
	Direction_t correctPath[2] = {RIGHT, DOWN};

	for (int i = 0; i < pathsize; i++) {
		EXPECT_EQ(path[i], correctPath[i]);
	}

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(FindExitTestFlags, normal_visited_square_flags_except_exit_square_changed_to_YES_no7) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);
	int pathsize = 0;

	int exit = FindExit(lab, 0, 0, path, &pathsize);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (lab.squares[i][j].exit == NO) {
				EXPECT_EQ(lab.squares[i][j].flag, YES);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(ClearFlagsTest, all_flags_changed_back_to_NO_no8) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	for (int i = 0; i < lab.rows; i++) {
		for (int j = 0; j < lab.cols; j++) {
			lab.squares[i][j].flag = YES;
		}
	}

	ClearFlags(lab);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			EXPECT_EQ(lab.squares[i][j].flag, NO);
		}
	}


	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
}

TEST(ExitPathTestReturn, no_exit_return_0_no9) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);

	int pathsize = ExitPath(lab, 0, 0, path);

	EXPECT_EQ(pathsize, 0);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(ExitPathTestReturn, normal_return_pathsize_no10) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);

	int pathsize = ExitPath(lab, 0, 0, path);
	
	EXPECT_EQ(pathsize, 2);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(ExitPathTestPath, normal_path_contains_steps_to_exit_in_reversed_order_no11) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);

	int pathsize = ExitPath(lab, 0, 0, path);

	Direction_t correctPath[2] = { RIGHT, DOWN };

	for (int i = 0; i < pathsize; i++) {
		EXPECT_EQ(path[i], correctPath[i]);
	}

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(ExitPathTestFlags, all_flags_changed_back_to_NO_no12) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);

	int pathsize = ExitPath(lab, 0, 0, path);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			EXPECT_EQ(lab.squares[i][j].flag, NO);
		}
	}

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(PrintPath, no_exit_no_steps_printed_no13) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);

	int pathsize = ExitPath(lab, 0, 0, path);

	PrintPath(path, pathsize);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}

TEST(PrintPath, normal_print_steps_no14) {
	Square_t** squares = (Square_t**)malloc(sizeof(Square_t*) * 2);
	for (int i = 0; i < 2; i++) {
		squares[i] = (Square_t*)malloc(sizeof(Square_t) * 2);
	}
	squares[0][0] = CreateSquare(NO, NO, YES, YES);
	squares[0][1] = CreateSquare(YES, NO, NO, NO);
	squares[1][0] = CreateSquare(NO, YES, YES, NO);
	squares[1][1] = CreateSquare(YES, NO, NO, NO);
	Labyrinth_t lab = { 2, 2, squares };
	lab.squares[1][1].exit = YES;

	Direction_t* path = (Direction_t*)malloc(sizeof(Direction_t) * 4);

	int pathsize = ExitPath(lab, 0, 0, path);

	PrintPath(path, pathsize);

	for (int i = 0; i < 2; i++) {
		free(squares[i]);
	}
	free(squares);
	free(path);
}