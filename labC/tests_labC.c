#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "labC.h"  // Заголовочный файл с объявлениями функций и структур

void TestInitializeMaze_ValidMaze_no1() {
    Maze maze;
    int matrix[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };
    InitializeMaze(&maze, matrix);
    printf("Test 1 = %i\n", maze.grid[0][1] == 1 && maze.grid[5][5] == 0);
}

void TestSearchPath_EmptyMaze_no2() {
    Maze maze;
    int matrix[ROWS][COLS] = { 0 };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = 0;
    int result = SearchPath(&maze, 0, 0, path, &path_length);
    printf("Test 2 = %i\n", result == 1);
}

void TestSearchPath_MazeWithWalls_no3() {
    Maze maze;
    int matrix[ROWS][COLS] = {
        {0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0}
    };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = 0;
    int result = SearchPath(&maze, 0, 0, path, &path_length);
    printf("Test 3 = %i\n", result == 0);
}

void TestSearchPath_SinglePathMaze_no4() {
    Maze maze;
    int matrix[ROWS][COLS] = {
        {0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 0}
    };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = 0;
    int result = SearchPath(&maze, 0, 0, path, &path_length);
    printf("Test 4 = %i\n", result == 1);
}


void TestFindExitPath_ValidPath_no5() {
    Maze maze;
    int matrix[ROWS][COLS] = {
        {0, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 0},
        {1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0}
    };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = FindExitPath(&maze, 0, 0, path);
    printf("Test 5 = %i\n", path_length > 0);
}

void TestFindExitPath_NoPath_no6() {
    Maze maze;
    int matrix[ROWS][COLS] = {
        {0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0}
    };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = FindExitPath(&maze, 0, 0, path);
    printf("Test 6 = %i\n", path_length == 0);
}

#include <string.h>

void TestPrintPath_ValidPath_no7() {
    Dir path[3] = { DIR_DOWN, DIR_RIGHT, DIR_DOWN };
    FILE* temp = freopen("temp.txt", "w", stdout);
    PrintPath(path, 3);
    fclose(temp);
    freopen("CON", "w", stdout);
    temp = fopen("temp.txt", "r");
    char output[100];
    fgets(output, 100, temp);
    fclose(temp);
    remove("temp.txt");
    printf("Test 7 = %i\n", strcmp(output, "START -> down -> right -> down -> EXIT\n") == 0);
}

void TestPrintPath_EmptyPath_no8() {
    Dir path[1] = { NO_DIRECTION };
    FILE* temp = freopen("temp.txt", "w", stdout);
    PrintPath(path, 0);
    fclose(temp);
    freopen("CON", "w", stdout);
    temp = fopen("temp.txt", "r");
    char output[100];
    fgets(output, 100, temp);
    fclose(temp);
    remove("temp.txt");
    printf("Test 8 = %i\n", strcmp(output, "Path not found\n") == 0);
}

void TestInitializeMaze_EmptyGrid_no9() {
    Maze maze;
    int matrix[ROWS][COLS] = { {0} };
    InitializeMaze(&maze, matrix);
    printf("Test 9 = %i\n", maze.grid[0][0] == 0 && maze.grid[ROWS - 1][COLS - 1] == 0);
}

void TestFindExitPath_StartIsExit_no10() {
    Maze maze;
    int matrix[ROWS][COLS] = { {0} };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = FindExitPath(&maze, ROWS - 1, COLS - 1, path);
    printf("Test 10 = %i\n", path_length == 0);
}

void TestFindExitPath_MazeFilledWithWalls_no11() {
    Maze maze;
    int matrix[ROWS][COLS] = {
        {0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0}
    };
    InitializeMaze(&maze, matrix);
    Dir path[100];
    int path_length = FindExitPath(&maze, 0, 0, path);
    printf("Test 11 = %i\n", path_length == 0);
}

void TestFindExitPath_SingleRowMaze_no12() {
    Maze maze;
    int matrix[1][COLS] = { {0, 0, 0, 0, 0, 0} };
    maze.rows = 1;
    maze.cols = COLS;
    for (int i = 0; i < COLS; i++) {
        maze.grid[0][i] = matrix[0][i];
    }
    Dir path[100];
    int path_length = FindExitPath(&maze, 0, 0, path);
    printf("Test 12 = %i\n", path_length > 0);
}

void RunMainMazeTest() {
    int matrix[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };

    Maze maze;
    InitializeMaze(&maze, matrix);

    Dir path[100];
    int path_length = FindExitPath(&maze, 0, 0, path);
    PrintPath(path, path_length);
}

void runAllTests() {
    TestInitializeMaze_ValidMaze_no1();
    TestSearchPath_EmptyMaze_no2();
    TestSearchPath_MazeWithWalls_no3();
    TestSearchPath_SinglePathMaze_no4();
    TestFindExitPath_ValidPath_no5();
    TestFindExitPath_NoPath_no6();
    TestPrintPath_ValidPath_no7();
    TestPrintPath_EmptyPath_no8();
    TestInitializeMaze_EmptyGrid_no9();
    TestFindExitPath_StartIsExit_no10();
    TestFindExitPath_MazeFilledWithWalls_no11();
    TestFindExitPath_SingleRowMaze_no12();
    RunMainMazeTest();
}

int main() {
    runAllTests();
    return 0;
}
