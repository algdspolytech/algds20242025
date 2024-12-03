#include "Maze.h"

void CreateMaze(Maze* maze, int lab[ROWS][COLS]) {
    maze->rows = ROWS;
    maze->cols = COLS;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze->cells[i][j] = lab[i][j];
        }
    }
}

Point SearchNext(Point *p, Direction dir) {
    Point res;
    switch (dir) {
    case LEFT:
        res.x = p->x - 1;
        res.y = p->y;
        break;
    case RIGHT:
        res.x = p->x + 1;
        res.y = p->y;
        break;
    case UP:
        res.x = p->x;
        res.y = p->y - 1;
        break;
    case DOWN:
        res.x = p->x;
        res.y = p->y + 1;
        break;
    }
    return res;
}

void PrintWay(Point parent[ROWS][COLS], Point start, Point exit, Direction* dir, int dir_size) {
    Point temp = exit;
    while (!(temp.x == start.x && temp.y == start.y)) {
        Point parentPoint = parent[temp.y][temp.x];
        if (temp.x > parentPoint.x) {
            dir[dir_size++] = RIGHT; 
        }
        else if (temp.x < parentPoint.x) {
            dir[dir_size++] = LEFT;
        }
        else if (temp.y > parentPoint.y) {
            dir[dir_size++] = DOWN; 
        }
        else if (temp.y < parentPoint.y) {
            dir[dir_size++] = UP; 
        }
        temp = parentPoint; 
    }
    for (int i = 0; i < dir_size / 2; i++) {
        Direction tmp = dir[i];
        dir[i] = dir[dir_size - 1 - i];
        dir[dir_size - 1 - i] = tmp;
    }
    printf("start -> ");
    for (int i = 0; i < dir_size; i++) {
        switch (dir[i]) {
        case LEFT:
            printf("left -> ");
            break;
        case RIGHT:
            printf("right -> ");
            break;
        case UP:
            printf("up -> ");
            break;
        case DOWN:
            printf("down -> ");
            break;
        }
    }
    printf("finish\n");
}

int FindWay(Maze* maze, Point start, Point exit) {
    if ((start.x < 0) || (start.y < 0) || (start.x > COLS-1) || (start.y > ROWS-1) || (exit.x < 0) || (exit.y < 0) || (exit.x > COLS-1) || (exit.y > ROWS-1)) {
        printf("Error");
        return -1;
    }
    bool visit[ROWS][COLS] = { false };
    int length = ROWS * COLS;
    int dir_size = 0;
    
    Direction dir[ROWS * COLS];
    Point parent[ROWS][COLS];
    Point queue[ROWS * COLS] = { -1,-1 };
    int count = 0, front = 0;
    queue[count++] = start;
    visit[start.y][start.x] = true;
    while (front < count) {
        Point current = queue[front++];
        if (current.x == exit.x && current.y == exit.y) {
            PrintWay(parent, start, exit, dir, dir_size);
            return 1;
        }
        Direction moves[4] = { LEFT, RIGHT, UP, DOWN };
        
        for (int i = 0; i < 4; i++) {
            Point newCell;
            newCell = SearchNext(&current, moves[i]);

            if (newCell.x >= 0 && newCell.x < COLS && newCell.y >= 0 && newCell.y < ROWS && maze->cells[newCell.y][newCell.x] == 0 && !visit[newCell.y][newCell.x]) {
                queue[count++] = newCell;
                visit[newCell.y][newCell.x] = true;
                parent[newCell.y][newCell.x] = current;
               

            }
        }
    }
    printf("Way not found");
    return 0;
}
