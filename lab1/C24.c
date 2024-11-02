#include "header_C24.h"


int rows, cols;
char maze[MAX_SIZE][MAX_SIZE];

void readMaze(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open maze file");
        return;
    }

    fscanf(file, "%d %d", &rows, &cols);

    for (int i = 0; i < rows; i++) {
        fscanf(file, "%s", maze[i]);
    }

    fclose(file);
}

void printMaze() {
    for (int i = 0; i < rows; i++) {
        printf("%s\n", maze[i]);
    }
}

int isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && (maze[x][y] == FREE || maze[x][y] == EXIT));
}

int findPath(Position pos) {
    // Если достигли выхода
    if (maze[pos.x][pos.y] == EXIT) {
        return 1; // Путь найден
    }

    // Если это не стартовая позиция, отмечаем её как посещённую
    if (maze[pos.x][pos.y] != START) {
        maze[pos.x][pos.y] = 'X'; // Отметка посещенной клетки
    }

    // Определяем возможные направления движения (вверх, вниз, влево, вправо)
    Position directions[4] = {
        {pos.x - 1, pos.y}, // вверх
        {pos.x + 1, pos.y}, // вниз
        {pos.x, pos.y - 1}, // влево
        {pos.x, pos.y + 1}  // вправо
    };

    // Перебираем все направления
    for (int i = 0; i < 4; i++) {
        if (isValid(directions[i].x, directions[i].y)) {
            if (findPath(directions[i])) { // Рекурсивное обращение
                return 1; // Путь найден
            }
        }
    }

    // Если путь не найден, возвращаем текущее состояние
    // Восстанавливаем клетку как свободную, если это не стартовая позиция
    if (maze[pos.x][pos.y] != START) {
        maze[pos.x][pos.y] = FREE; // Восстановить клетку
    }
    return 0; // Путь не найден
}