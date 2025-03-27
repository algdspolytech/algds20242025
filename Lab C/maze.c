#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"


cell_t* createcell(dir left, dir up, dir right, dir down)
{

	if (left == n && up == n && right == n && down == n || left == l && up == u && right == r && down == d) {
		return NULL;
	}
	dir directions[4] = { left, up, right, down };
	cell_t* cell = malloc(sizeof(cell_t));
	dir order[] = {l, u, r, d};
	cell->dirs = malloc(sizeof(dir) * 4);
	for (int i = 0; i < 4; i++) {
		cell->dirs[i] = directions[i];
	}
	return cell;
}

maze_t* createmaze(int rows, int cols)
{
	if (rows < 1 || cols < 1) {
		return NULL;
	}
	maze_t* maze = malloc(sizeof(maze_t));
	maze->rows = rows;
	maze->cols = cols;
	maze->cells = malloc(cols* rows * sizeof(cell_t*));
	return maze;
}

/*
			   ||||||||||||
 0  1  2  3  4            |
			   ||||| |||| |
 5  6  7  8  9 |     |    |
			   | ||| ||||||
10 11 12 13 14 | |        |
			   | ||||||||||
15 16 17 18 19 |   |      |
			   | ||| ||||||
20 21 22 23 24 |
			   ||||||||||||
*/
maze_t* createtestmaze() { 
	maze_t* maze = createmaze(5, 5);
	maze->face = r;
	// lurd
	maze->cells[0] = createcell(n, n, r, n);
	maze->cells[1] = createcell(l,n,r,n);
	maze->cells[2] = createcell(l,n,r,d);
	maze->cells[3] = createcell(l, n, r, n);
	maze->cells[4] = createcell(l, n, n, d);
	maze->cells[5] = createcell(n,n,r,d);
	maze->cells[6] = createcell(l, n, r, n);
	maze->cells[7] = createcell(l,u,n,d);
	maze->cells[8] = createcell(n, n, r, n);
	maze->cells[9] = createcell(l,u,n,n);
	maze->cells[10] = createcell(n,u,n,d);
	maze->cells[11] = createcell(n, n, r, n);
	maze->cells[12] = createcell(l, u, r, n);
	maze->cells[13] = createcell(l, n, r, n);
	maze->cells[14] = createcell(l,n,n,n);
	maze->cells[15] = createcell(n,u,r,d);
	maze->cells[16] = createcell(l, n, n, n);
	maze->cells[17] = createcell(n,n,r,d);
	maze->cells[18] = createcell(l, n, r, n);
	maze->cells[19] = createcell(l, n, n, n);
	maze->cells[20] = createcell(n, u, r, n);
	maze->cells[21] = createcell(l, n, r, n);
	maze->cells[22] = createcell(l, u, r, n);
	maze->cells[23] = createcell(l, n, r, n);
	maze->cells[24] = createcell(l, n, n, n);
	return maze;
} 

int move(int cur, dir whereto, maze_t* maze, dir* face) {
	*face = whereto;
	switch (whereto) {
	case l:
		return cur - 1;
	case u:
		return cur - maze->cols;
	case r:
		return cur + 1;
	case d:
		return cur + maze->cols;
	}
}


int leftwalliter(int cur, dir* face, maze_t* maze) {
	if (maze == NULL || face == NULL) {
		return -1;
	}
	dir order[] = { u,r,d,l };
	for (int i = 0; i < 4;i++) { // face r = 2
		if (maze->cells[cur]->dirs[(i + *face+3) % 4] != n) {
			return move(cur, (dir)((i + *face+3) % 4), maze, face);
		}
	}
} 


int* leftwallpath(maze_t* maze, int* size) {
	if (maze == NULL) {
		return NULL;
	}
	int cur = 0;
	int len = 1;
	dir face = maze->face;
	int* cellpath = malloc(2*maze->cols * maze->rows * sizeof(int));
	cellpath[0] = 0;
	do {
		cur = leftwalliter(cur, &face, maze);
		cellpath[len] = cur;
		len++;
	}while (cur != maze->cols * maze->rows - 1);
	*size = len;
	return cellpath;
}

void printpath(int* path, int size) {
	for (int i = 0; i < size;i++) {
		printf("%i \n", path[i]);
	}
}



/*
1	2	3	4	5
6	7	8	9	10
11	12	13	14	15
16	17	18	19	20
21	22	23	24	25
*/


