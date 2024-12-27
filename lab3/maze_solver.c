#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_X 4
#define MAZE_Y 4

void free2Darray(int ** array){
    for (int i = 0; i < MAZE_Y; i++){
        free(array[i]);
    }
    free(array);
}

typedef struct Node{
    int x;
    int y;
}Node;

typedef struct Path{
    int maxlen, head;
    Node * path;
}Path;

int nodeCompare(Node * n1, Node * n2){
    if (n1->x == n2->x && n1->y == n2->y)
        return true;
    else
        return false;
}

void pathSetup(Path * p, Node * n){
    p->maxlen = 10;
    p->head = 0;
    p->path = (Node*)malloc(p->maxlen * sizeof(Node));
    p->path[p->head]= *n;
}

void pathEmbiggen(Path * p){
    p->maxlen *= 2;
    p->path = (Node*)realloc(p->path, p->maxlen * sizeof(Node));
}

int pathTooSmall(Path * p){
    return p->head >= p->maxlen - 1;
}

Node * pathHead(Path * p){
    return &(p->path[p->head]);
}

void pathPush(Path * p, Node * n){
    if (pathTooSmall(p)){
        pathEmbiggen(p);
    }
    p->head += 1;
    p->path[p->head] = *n;
}

void pathPop(Path * p){
    if (p->head > 0){
        p->head -= 1;
    }
}

int isValidMove(int x, int y){
    return x >= 0 && x < MAZE_X && y >= 0 && y < MAZE_Y;
}

int canMove(Path * p, int direction){
    switch (direction)
    {
    case U:
        /* code */
        break;
    
    default:
        break;
    }
}

int **createMaze(){
    const int
    U = (1<<0),
    D = (1<<1),
    R = (1<<2),
    L = (1<<3);

    const int
    START = (1<<4),
    FINISH = (1<<5);

    int ** maze = (int**)malloc(MAZE_X * sizeof(int*));
    for (int i = 0; i < MAZE_X; i++){
        maze[i] = (int*)malloc(MAZE_Y * sizeof(int));
    }
    int localMaze[MAZE_X][MAZE_Y] = 
    {
        {R|D|START, L, R|D, L},
        {U|R|D, L|R, U|D|L, D},
        {U|D, R|D, U|R|L, U|D|L},
        {U, U|R, L, U|FINISH}
    };
    for (int i = 0; i < MAZE_X; i++){
        memcpy(maze[i], localMaze[i], sizeof(localMaze[i]));
    }
    return maze;
}

int main(){
    int ** maze = createMaze();
    Node n1, n2;
    (&n1)->x = 1;
    (&n1)->y = 2;
    (&n2)->x = 3;
    (&n2)->y = 4;
    Path p;
    pathSetup(&p, &n1);
    printf("%d\n", p.maxlen);
    free2Darray(maze);
    return 0;
}