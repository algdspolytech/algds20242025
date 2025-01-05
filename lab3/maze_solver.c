#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_X 4
#define MAZE_Y 4
enum{U = 1<<0, D = 1<<1, R = 1<<2, L = 1<<3, START = 1<<4, FINISH = 1<<5};

typedef struct Node{
    int x;
    int y;
}Node;

typedef struct Path{
    int maxlen, head;
    Node * path;
}Path;

// const int U = (1<<0);
// const int D = (1<<1);
// const int R = (1<<2);
// const int L = (1<<3);

// const int START = (1<<4);
// const int FINISH = (1<<5);

int maze[MAZE_X][MAZE_Y] = 
{
    {R|D|START, L, R|D, L},
    {U|R|D, L|R, U|D|L, D},
    {U|D, R|D, U|R|L, U|D|L},
    {U, U|R, L, U|FINISH}
};

Node start = {0, 0};
Node finish = {3, 3};

void free2Darray(int ** array){
    for (int i = 0; i < MAZE_Y; i++){
        free(array[i]);
    }
    free(array);
}


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
    if (pathTooSmall(p))
        pathEmbiggen(p);
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

int canMove(Node * current, int direction){
    switch (direction)
    {
    case U: return isValidMove(current->x - 1, current->y) && (maze[current->x][current->y] & U);
    case D: return isValidMove(current->x + 1, current->y) && (maze[current->x][current->y] & D);
    case R: return isValidMove(current->x, current->y + 1) && (maze[current->x][current->y] & R);
    case L: return isValidMove(current->x, current->y - 1) && (maze[current->x][current->y] & L);
    default: return 0;
    }
}

int findPath(Path * path, Node * current){
    if(nodeCompare(&finish, current)){
        return 1;
    }
    
    for(int direction = U; direction <= L; direction <<= 1){
        if(canMove(current, direction)){
            Node next;
            switch (direction)
            {
            case U: next.x = current->x - 1; next.y = current->y; break;
            case D: next.x = current->x + 1; next.y = current->y; break;
            case R: next.x = current->x; next.y = current->y + 1; break;
            case L: next.x = current->x; next.y = current->y - 1; break;        
            }
        
            pathPush(path, &next);

            if(findPath(path, &next))
                return 1;
            
            pathPop(path);
        }
    }

    return 0;
}

void printPath(Path * p){
    for(int i = 0; i <= p->head; i++){
        printf("(%d, %d) ", p->path[i].x, p->path[i].y);
    }
    printf("\n");
}

int main(){
    Path path;
    pathSetup(&path, &start);
    if (findPath(&path, &start)){
        printf("Path found\n");
        printPath(&path);
    }
    else
        printf("No Path found\n");
    free(path.path);
    return 0;
}