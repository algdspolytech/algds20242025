#define _CRT_SECURE_NO_WARNINGS
#include "Labyrinth.h"
#include <stdio.h>
#include <stdlib.h>

/*
* —оздать клетку
* 
* —оздает структуру типа Square_t по параметрам left, up, right, down: 
YES - в соседнюю клетку в соответствующем направлении можно ходить,
NO - в соседнюю клетку в соответствующем направлении нельз€ ходить
*/
Square_t CreateSquare(Flag_t left, Flag_t up, Flag_t right, Flag_t down) {
	Square_t sq;
	sq.exit = NO;
	sq.flag = NO;
	Flag_t* dirs = (Flag_t*)malloc(sizeof(Flag_t) * N);
	dirs[0] = left;
	dirs[1] = up;
	dirs[2] = right;
	dirs[3] = down;
	sq.dirs = dirs;
	sq.prev = NONE_DIR;
	return sq;
}

/*
* Ќайти выход из лабиринта
* 
* ¬озвращает: 1 - если выход найден, 0 - если нет
* row, col - строка и столбец, соответствующие клетке, в которой сейчас находимс€
* ¬ path записываетс€ путь от начальной клетки до выхода в обратном пор€дке (если выход найден)
* ¬ pathsize записываетс€ количество шагов в пути
*/
int FindExit(Labyrinth_t lab, int row, int col, Direction_t* path, int* pathsize) {
	int exit;
	if (lab.squares[row][col].exit == YES) {
		lab.squares[row][col].prev = NONE_DIR;
		*pathsize = 0;
		return 1;
	}

	if (lab.squares[row][col].flag == YES) {
		lab.squares[row][col].prev = NONE_DIR;
		return 0;
	}

	lab.squares[row][col].flag = YES;
	if ((lab.squares[row][col].dirs[0] == YES) && (lab.squares[row][col].prev != LEFT)) {
		lab.squares[row][col - 1].prev = RIGHT;
		exit = FindExit(lab, row, col - 1, path, pathsize);
		lab.squares[row][col].prev = NONE_DIR;
		if (exit == 1) {
			path[*pathsize] = LEFT;
			*pathsize = *pathsize + 1;
			return 1;
		}
	}
	if ((lab.squares[row][col].dirs[1] == YES) && (lab.squares[row][col].prev != UP)) {
		lab.squares[row - 1][col].prev = DOWN;
		exit = FindExit(lab, row - 1, col, path, pathsize);
		lab.squares[row][col].prev = NONE_DIR;
		if (exit == 1) {
			path[*pathsize] = UP;
			*pathsize = *pathsize + 1;
			return 1;
		}
	}
	if ((lab.squares[row][col].dirs[2] == YES) && (lab.squares[row][col].prev != RIGHT)) {
		lab.squares[row][col + 1].prev = LEFT;
		exit = FindExit(lab, row, col + 1, path, pathsize);
		lab.squares[row][col].prev = NONE_DIR;
		if (exit == 1) {
			path[*pathsize] = RIGHT;
			*pathsize = *pathsize + 1;
			return 1;
		}
	}
	if ((lab.squares[row][col].dirs[3] == YES) && (lab.squares[row][col].prev != DOWN)) {
		lab.squares[row + 1][col].prev = UP;
		exit = FindExit(lab, row + 1, col, path, pathsize);
		lab.squares[row][col].prev = NONE_DIR;
		if (exit == 1) {
			path[*pathsize] = DOWN;
			*pathsize = *pathsize + 1;
			return 1;
		}
	}
	lab.squares[row][col].prev = NONE_DIR;
	return 0;

}

//¬ывести путь
void PrintPath(Direction_t* path, int pathsize) {
	if (pathsize > 0) {
		printf("START");
		for (int i = pathsize - 1; i >= 0; i--) {
			printf(" - ");
			switch (path[i])
			{
			case LEFT:
				printf("left");
				break;
			case UP:
				printf("up");
				break;
			case RIGHT:
				printf("right");
				break;
			case DOWN:
				printf("down");
				break;
			}
		}
		printf(" - EXIT\n");
	}
}

/*
* ќчистка флагов
* 
* ƒелает все пол€ flag клеток лабиринта равными NO
*/
void ClearFlags(Labyrinth_t lab) {
	for (int i = 0; i < lab.rows; i++) {
		for (int j = 0; j < lab.cols; j++) {
			lab.squares[i][j].flag = NO;
		}
	}
}

/*
* Ќайти путь к выходу с последующей очисткой флагов
* 
* ¬озвращает: количество шагов - если выход найден, 0 - если выход не найден;
* row, col - строка и столбец начальной клетки
* ¬ path записываетс€ путь в обратном пор€дке
*/
int ExitPath(Labyrinth_t lab, int row, int col, Direction_t* path) {
	int pathsize = 0;
	int p = FindExit(lab, row, col, path, &pathsize);
	if (p == 0) {
		printf("exit not found!\n");
	}
	ClearFlags(lab);
	return pathsize;
}