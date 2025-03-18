#pragma once

typedef enum dir { l, u, r, d, n } dir;

typedef struct cell_t {
	dir* dirs;
}cell_t;

typedef struct maze_t {
	int rows;
	int cols;
	dir face;
	cell_t** cells;
}maze_t;

cell_t* createcell(dir left, dir up, dir right, dir down);

maze_t* createmaze(int rows, int cols);

maze_t* createtestmaze();

int move(int cur, dir whereto, maze_t* maze, dir* face);

int leftwalliter(int cur, dir* face, maze_t* maze);

int* leftwallpath(maze_t* maze, int* size);

void printpath(int* path, int size);
