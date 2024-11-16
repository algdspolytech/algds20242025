#include "header_C24.h"

void maze1_simple_5_5() {
	Position start = { -1, -1 };

	readMaze("maze_simple_5_5.txt"); 
	printf("\nInitial Maze 1:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}

	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze2_ordinary_6_6() {
	Position start = { -1, -1 };

	readMaze("maze_ordinary_6_6.txt"); 
	printf("\nInitial Maze 2:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}
	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");



	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}


void maze3_rectangle_3_8() {
	Position start = { -1, -1 };

	readMaze("maze_rectangle_3_8.txt"); 
	printf("\nInitial Maze 3:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}
	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");

	

	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze4_without_start() {
	Position start = { -1, -1 };

	readMaze("maze_without_start.txt"); 
	printf("\nInitial Maze 4:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}
	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze5_without_exit() {
	Position start = { -1, -1 };

	readMaze("maze_without_exit.txt");
	printf("\nInitial Maze 5:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}
	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze6_empty() {
	Position start = { -1, -1 };

	readMaze("maze_empty.txt"); 
	printf("\nInitial Maze 6:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}

	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze7_all_walls() {
	Position start = { -1, -1 };

	readMaze("maze_all_walls.txt"); 
	printf("\nInitial Maze 7:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}

	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");

	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze8_all_path() {
	Position start = { -1, -1 };

	readMaze("maze_all_path.txt"); 
	printf("\nInitial Maze 8:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}

	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze9_no_exit() {
	Position start = { -1, -1 };

	readMaze("maze_no_exit.txt");
	printf("\nInitial Maze 9:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}

	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");

	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}


void maze10_undefined_signs() {
	Position start = { -1, -1 };

	readMaze("maze_undefined_signs.txt"); 
	printf("\nInitial Maze 10:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}
	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}

void maze11_bigger_than_max_size() {
	Position start = { -1, -1 };

	readMaze("maze__bigger_than_max_size.txt"); 
	printf("\nInitial Maze 11:\n");
	printMaze();

	// Находим стартовую позицию
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (maze[i][j] == START) {
				start.x = i;
				start.y = j;
				break;
			}
		}
		if (start.x != -1) break; // Если нашли начальную точку, то выходим из внешнего цикла
	}

	// Проверяем, найдена ли начальная точка
	assert(start.x != -1 && "Стартовая позиция не найдена");


	// Поиск пути
	if (findPath(start)) {
		printf("\nWay is found:\n");
		printMaze();
	}
	else {
		printf("\nNo way to exit\n");
		assert(0 && "!");
	}

}





int main() {
	maze1_simple_5_5();
	maze2_ordinary_6_6();
	maze3_rectangle_3_8();
	maze4_without_start();
	maze5_without_exit();
	maze6_empty();
	maze7_all_walls();
	maze8_all_path();
	maze9_no_exit();
	maze10_undefined_signs();
	maze11_bigger_than_max_size(); 
	return 0;
}

