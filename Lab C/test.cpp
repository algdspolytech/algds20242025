#include "pch.h"
#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>




extern "C" {
#include "..\Mazez\maze.h"
}

int checkcell(cell_t* cell, dir left, dir up, dir right, dir down) {
	return cell->dirs[0] == left && cell->dirs[1] == up && cell->dirs[2] == right && cell->dirs[3] == down;
}

/*

int move(int cur, dir whereto, maze_t* maze, dir* face);

int leftwalliter(int cur, dir* face, maze_t* maze);

int* leftwallpath(maze_t* maze, int* size);
*/

TEST(MazelistTest, creatcell_NoDirections_ReturnNULL)
{
	ASSERT_EQ(NULL, createcell(n,n,n,n));
}

TEST(MazelistTest, creatcell_AllDirections_ReturnNULL)
{
	ASSERT_EQ(NULL, createcell(l, u, r, d));
}

TEST(MazelistTest, creatcell_ValidVal_ReturnValidVal)
{
	cell_t* cell = createcell(n, n, r, n);
	EXPECT_TRUE(cell->dirs[0] == n && cell->dirs[1] == n && cell->dirs[2] == r && cell->dirs[3] == n);
}

TEST(MazelistTest, createmaze_InvalidVal_ReturnNULL)
{
	ASSERT_EQ(NULL, createmaze(-1,1));
}

TEST(MazelistTest, createmaze_ValidVal_ReturnValidVal)
{
	maze_t* maze = createmaze(5, 5);
	EXPECT_TRUE(maze->cols == 5 && maze ->rows == 5);
}

TEST(MazelistTest, createtestmaze_NULL_ReturnValidVal)
{
	maze_t* maze = createtestmaze();
	int iscell1val = checkcell(maze->cells[0], n, n, r, n);
	int iscell2val = checkcell(maze->cells[1], l, n, r, n);
	int iscell3val = checkcell(maze->cells[2], l, n, r, d);
	int iscell4val = checkcell(maze->cells[3], l, n, r, n);
	int iscell5val = checkcell(maze->cells[4], l, n, n, d);
	EXPECT_TRUE(iscell1val && iscell2val && iscell3val && iscell4val && iscell5val);
}

TEST(MazelistTest, move_ValidVal_ReturnValidVal)
{
	maze_t* maze = createtestmaze();
	dir face = d;
	int newbox = move(1, r, maze, &face);
	EXPECT_TRUE(newbox == 2 && face == r);
}

TEST(MazelistTest, leftwalliter_NULL_ReturnNegOne)
{
	ASSERT_EQ(-1, leftwalliter(1, NULL, NULL));
}

TEST(MazelistTest, leftwalliter_ValidVal_ReturnValidVal)
{
	maze_t* maze = createtestmaze();
	dir face = d;
	ASSERT_EQ(2, leftwalliter(1, &face, maze));
}

TEST(MazelistTest, leftwallpath_NULL_ReturnNULL)
{
	ASSERT_EQ(NULL, leftwallpath(NULL, NULL));
}