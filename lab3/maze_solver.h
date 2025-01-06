#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_X 4
#define MAZE_Y 4

enum {U = 1<<0, D = 1<<1, R = 1<<2, L = 1<<3, START = 1<<4, FINISH = 1<<5};

typedef struct Node {
    int x, y;
} Node;

typedef struct Path {
    int maxlen, head;
    Node *path;
} Path;

extern int maze[MAZE_X][MAZE_Y];
extern Node start;
extern Node finish;
extern int visited[MAZE_X][MAZE_Y];

int nodeCompare(Node *n1, Node *n2);
void pathSetup(Path *p, Node *n);
void pathEmbiggen(Path *p);
int pathTooSmall(Path *p);
void pathPush(Path *p, Node *n);
void pathPop(Path *p);
int isValidMove(int x, int y);
int canMove(Node *current, int direction);
int findPath(Path *path, Node *current);
void printPath(Path *p);

#endif