#include "Maze.h" 
#include <locale.h>

void TestSearchNext_n1() {
    Point elem = { 4, 0 };
    Direction dir = LEFT;
    if (SearchNext(&elem, dir).x == 3 && SearchNext(&elem, dir).y == 0) {
        printf("1  -  Пройден\n");
    }
}
void TestSearchNext_NoneDir_n2() {
    Point elem = { 4, 0 };
    Direction dir = NONE;
    if (SearchNext(&elem, dir).x == 4 && SearchNext(&elem, dir).y == 0) {
        printf("2  -  Пройден\n");
    }
}

void TestCreateMaze_n3() {
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

void TestTestCreateNullMaze_n4() {
    Maze maze;
    int labyrinth[ROWS][COLS] = { {0} };
    CreateMaze(&maze, labyrinth);
    if (maze.cells[0][1] == 0 && maze.cells[ROWS - 1][COLS - 1] == 0) {
        printf("4  -  Пройден\n");
    }
}


void TestTestFindWay_n5() {
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
void TestFindWay_StartIsWall_n6() {
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

void TestFindWay_StartIsExit_n7() {
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

void TestFindWay_noWay_n8() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 5, 5 };
    int labyrinth[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0},
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

void TestFindWay_ErrorExit_n9() {
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

void TestTestFindWay_NotWalls_n10() {
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
    TestSearchNext_n1();
    TestSearchNext_NoneDir_n2();
    TestCreateMaze_n3();
    TestTestCreateNullMaze_n4();
    TestTestFindWay_n5();
    TestFindWay_StartIsWall_n6();
    TestFindWay_StartIsExit_n7();
    TestFindWay_noWay_n8();
    TestFindWay_ErrorExit_n9(); 
    TestTestFindWay_NotWalls_n10();
}    
