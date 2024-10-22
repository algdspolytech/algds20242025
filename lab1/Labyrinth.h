#pragma once
#define N 4

//направления движения по лабиринту
typedef enum Direction_t {
	NONE_DIR,
	LEFT,
	UP,
	RIGHT,
	DOWN
} Direction_t;

//флаги
typedef enum Flag_t {
	NO,
	YES
} Flag_t;

//клеточка лабиринта
typedef struct Square_t {
	Flag_t exit; //является ли выходом
	Flag_t flag; //были ли уже в этой клетке
	Flag_t* dirs; //свободно ли в каждом из направлений: слева, сверху, справа, снизу
	Direction_t prev; //направление, откуда пришли в эту клетку
} Square_t;

//лабиринт
typedef struct Labyrinth_t {
	int rows; //количество строк
	int cols; //количество столбцов
	Square_t** squares; //клетки лабиринта
} Labyrinth_t;

//создать клетку
Square_t CreateSquare(Flag_t left, Flag_t up, Flag_t right, Flag_t down);

//найти путь к выходу
int FindExit(Labyrinth_t lab, int row, int col, Direction_t* path, int* pathsize);

//вывести путь
void PrintPath(Direction_t* path, int pathsize);

//очистить флаги
void ClearFlags(Labyrinth_t lab);

//найти путь к выходу с последующей очисткой флагов
int ExitPath(Labyrinth_t lab, int row, int col, Direction_t* path);
