#include "Maze.h"

int main() {
    Maze maze;
    Point start = { 0, 0 };
    Point exit = { 5, 5 };
    int labyrinth[6][6] = {
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1, 0}
    }; 
    CreateMaze(&maze, labyrinth);
    FindWay(&maze, start, exit); 
    return 0;
}                      
