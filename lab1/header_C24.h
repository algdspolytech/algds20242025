#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>

#define MAX_SIZE 100
#define WALL '#'
#define FREE '.'
#define START 'S'
#define EXIT 'E'

// структуру для позиции
typedef struct {
    int x;
    int y;
} Position;


void readMaze(const char* filename);
void printMaze();
int findPath(Position pos);
int isValid(int x, int y);


extern int rows, cols;
extern char maze[MAX_SIZE][MAX_SIZE];

#endif // MAZE_H