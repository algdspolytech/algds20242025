#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "maze_solver.h"

int maze[MAZE_X][MAZE_Y] = {
    {R|D|START, L, R|D, L},
    {U|R|D, L|R, U|D|L, D},
    {U|D, R|D, U|R|L, U|D|L},
    {U, U|R, L, U|FINISH}
};

Node start = {0, 0};
Node finish = {3, 3};

int visited[MAZE_X][MAZE_Y] = {0};

int nodeCompare(Node *n1, Node *n2) {
    return n1->x == n2->x && n1->y == n2->y;
}

void pathSetup(Path *p, Node *n) {
    p->maxlen = 10;
    p->head = 0;
    p->path = (Node*)malloc(p->maxlen * sizeof(Node));
    p->path[p->head] = *n;
}

void pathEmbiggen(Path *p) {
    p->maxlen *= 2;
    p->path = (Node*)realloc(p->path, p->maxlen * sizeof(Node));
}

int pathTooSmall(Path *p) {
    return p->head >= p->maxlen - 1;
}

void pathPush(Path *p, Node *n) {
    if (pathTooSmall(p))
        pathEmbiggen(p);
    p->head++;
    p->path[p->head] = *n;
}

void pathPop(Path *p) {
    if (p->head > 0)
        p->head--;
}

int isValidMove(int x, int y) {
    return x >= 0 && x < MAZE_X && y >= 0 && y < MAZE_Y;
}

int canMove(Node *current, int direction) {
    switch (direction) {
        case U: return isValidMove(current->x - 1, current->y) && (maze[current->x][current->y] & U);
        case D: return isValidMove(current->x + 1, current->y) && (maze[current->x][current->y] & D);
        case R: return isValidMove(current->x, current->y + 1) && (maze[current->x][current->y] & R);
        case L: return isValidMove(current->x, current->y - 1) && (maze[current->x][current->y] & L);
        default: return 0;
    }
}

int findPath(Path *path, Node *current) {
    if (nodeCompare(&finish, current))
        return 1;

    for (int direction = U; direction <= L; direction <<= 1) {
        if (canMove(current, direction)) {
            Node next = {current->x, current->y};
            switch (direction) {
                case U: next.x--; break;
                case D: next.x++; break;
                case R: next.y++; break;
                case L: next.y--; break;
            }

            if (!visited[next.x][next.y]) {
                visited[next.x][next.y] = 1;
                pathPush(path, &next);

                if (findPath(path, &next))
                    return 1;

                pathPop(path);
                visited[next.x][next.y] = 0;
            }
        }
    }

    return 0;
}

void printPath(Path *p) {
    for (int i = 0; i <= p->head; i++) {
        printf("(%d, %d) ", p->path[i].x, p->path[i].y);
    }
    printf("\n");
}

// int main() {
//     Path path;
//     pathSetup(&path, &start);
//     visited[start.x][start.y] = 1;

//     if (findPath(&path, &start)) {
//         printf("Path found\n");
//         printPath(&path);
//     } else {
//         printf("No Path found\n");
//     }

//     free(path.path);
//     return 0;
// }
