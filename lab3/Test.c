#include "Maze.h" 
#include <locale.h>

void Test1() {
    Point elem = { 4, 0 };
    Direction dir = LEFT;
    if (SearchNext(&elem, dir).x == 3 && SearchNext(&elem, dir).y == 0) {
        printf("1  -  Пройден\n");
    }
}

void Test2() {
    Point elem = { 4, 0 };
    Direction dir = NONE;
    if (SearchNext(&elem, dir).x == 4 && SearchNext(&elem, dir).y == 0) {
        printf("2  -  Пройден\n");
    }
}

void Test3() {
    Maze maze;
    int labyrinth[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };
    CreateMaze(&maze, labyrinth);
    if (maze.cells[1][1] == 1 && maze.cells[ROWS - 1][COLS - 1] == 0) {
        printf("3  -  Пройден\n");
    }
}

void Test4() {
    Maze maze;
    int labyrinth[ROWS][COLS] = { {0} };
    CreateMaze(&maze, labyrinth);
    if (maze.cells[0][1] == 0 && maze.cells[ROWS - 1][COLS - 1] == 0) {
        printf("4  -  Пройден\n");
    }
}

void Test5() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 5, 5 };
    int labyrinth[ROWS][COLS] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1, 0}
    };
    CreateMaze(&maze, labyrinth);
    if (FindWay(&maze, start, exit) == 1) {
        printf("5  -  Пройден\n"); 
    }
}

void Test6() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 5, 5 };
    int labyrinth[ROWS][COLS] = {
        {1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1, 0}
    };
    CreateMaze(&maze, labyrinth);
    if (FindWay(&maze, start, exit) == -2) {
        printf("6  -  Пройден\n");
    }
}

void Test7() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 0, 0 };
    int labyrinth[ROWS][COLS] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1, 0}
    };
    CreateMaze(&maze, labyrinth);
    if (FindWay(&maze, start, exit) == 1) {
        printf("7  -  Пройден\n");
    }
}

void Test8() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 5, 5 };
    int labyrinth[ROWS][COLS] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };
    CreateMaze(&maze, labyrinth);
    if (FindWay(&maze, start, exit) == 0) {
        printf("8  -  Пройден\n");
    }
}

void Test9() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 7, 7 };
    int labyrinth[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };
    CreateMaze(&maze, labyrinth);
    if (FindWay(&maze, start, exit) == -1) {
        printf("9  -  Пройден\n"); 
    }
}

void Test10() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 5, 5 };
    int labyrinth[ROWS][COLS] = { 0 };
    CreateMaze(&maze, labyrinth);
    if (FindWay(&maze, start, exit) == 1) {
        printf("10  -  Пройден\n"); 
    }
}

void Tests() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
}              
