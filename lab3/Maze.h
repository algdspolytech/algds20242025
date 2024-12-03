#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 6 
#define COLS 6 

typedef enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
}Direction;

typedef struct Point {
	int x;
	int y;

}Point;

typedef struct Maze {
	int cells[ROWS][COLS];
	int cols;
	int rows;
}Maze;

void CreateMaze(Maze* maze, int lab[ROWS][COLS]);
Point SearchNext(Point* p, Direction dir);
void PrintWay(Point parent[ROWS][COLS], Point start, Point exit, Direction* dir, int dir_size);
int FindWay(Maze* maze, Point start, Point exit);
