#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100 // размер лабиринта

typedef struct {
    int x;
    int y;
} Point;

// Путь
typedef struct {
    Point points[MAX_SIZE];
    int size;
} Path;

// Проверка, можно ли сделать ход в клетку
bool can_move(int maze[MAX_SIZE][MAX_SIZE], int visited[MAX_SIZE][MAX_SIZE], int x, int y, int rows, int cols) {
    // Проверка на границы
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false; // Если выход за границы, возвращаем false
    }

    bool is_passable = (maze[x][y] == 0); // Проверка на проходимость
    bool is_not_visited = !visited[x][y]; // Проверка на посещенность

    return is_passable && is_not_visited;
}

// Добавление точки в путь
void add_point(Path* path, int x, int y) {
    Point new_point;
    new_point.x = x;
    new_point.y = y;
    path->points[path->size] = new_point;
    path->size++;
}

// Удаление последней точки из пути
void remove_last_point(Path* path) {
    if (path->size > 0) {
        path->size--;
    }
}

// Рекурсивный поиск пути в лабиринте
bool search_path(int maze[MAX_SIZE][MAX_SIZE], int visited[MAX_SIZE][MAX_SIZE], Path* path, int x, int y, int exit_x, int exit_y, int rows, int cols) {
    if (x == exit_x && y == exit_y) { // Если достигли выхода
        add_point(path, x, y);
        return true;
    }

    if (can_move(maze, visited, x, y, rows, cols)) {
        visited[x][y] = 1;
        add_point(path, x, y);

        // Исследуем соседние клетки
        if (search_path(maze, visited, path, x + 1, y, exit_x, exit_y, rows, cols) || // вниз
            search_path(maze, visited, path, x - 1, y, exit_x, exit_y, rows, cols) || // вверх
            search_path(maze, visited, path, x, y + 1, exit_x, exit_y, rows, cols) || // вправо
            search_path(maze, visited, path, x, y - 1, exit_x, exit_y, rows, cols)) { // влево
            return true; // Если путь найден, возвращаем true
        }

        remove_last_point(path);
        visited[x][y] = 0;
    }

    return false; // Путь не найден
}

// Инициализация массива посещенных клеток
void initialize_visited(int visited[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0; // Все клетки изначально непосещенные
        }
    }
}

// Тесты для функции can_move
void TestCanMove_no1() {
    // Проверяем, что можно переместиться в клетку (0, 0) в пустом лабиринте
    int maze[1][1] = { {0} };
    int visited[1][1] = { {0} };
    bool result = can_move(maze, visited, 0, 0, 1, 1);
    printf("TestCanMove_no1: %s\n", result ? "Passed" : "Failed");
} // Ожидание: Passed

void TestCanMove_no2() {
    // Проверяем, что нельзя переместиться в клетку (0, 0), если она заблокирована
    int maze[1][1] = { {1} };
    int visited[1][1] = { {0} };
    bool result = can_move(maze, visited, 0, 0, 1, 1);
    printf("TestCanMove_no2: %s\n", result ? "Passed" : "Failed");
}  // Ожидание: Failed


void TestCanMove_no3() {
    // Проверяем, что нельзя переместиться в клетку (1, 1), которая вне границ
    int maze[1][1] = { {0} };
    int visited[1][1] = { {0} };
    bool result = can_move(maze, visited, 1, 1, 1, 1); // Проверяем координаты вне границ
    printf("TestCanMove_no3: %s\n", result ? "Passed" : "Failed");
}// Ожидание: Failed

void TestCanMove_no4() {
    // Проверяем, что нельзя переместиться в клетку (0, 1), если она заблокирована
    int maze[2][2] = { {0, 1}, {0, 0} };
    int visited[2][2] = { {0, 0}, {0, 0} };
    bool result = can_move(maze, visited, 0, 1, 2, 2);
    printf("TestCanMove_no4: %s\n", result ? "Passed" : "Failed");
}  // Ожидание: Failed

// Тесты для функции add_point
void TestAddPoint_no5() {
    // Проверяем добавление первой точки в пустой путь
    Path path = { .size = 0 };
    add_point(&path, 1, 1);
    printf("TestAddPoint_no5: %s\n", path.size == 1 && path.points[0].x == 1 && path.points[0].y == 1 ? "Passed" : "Failed");
}  // Ожидание: Passed

void TestAddPoint_no6() {
    // Проверяем добавление двух точек в путь
    Path path = { .size = 0 };
    add_point(&path, 2, 3);
    add_point(&path, 4, 5);
    printf("TestAddPoint_no6: %s\n", path.size == 2 && path.points[1].x == 4 && path.points[1].y == 5 ? "Passed" : "Failed");
} // Ожидание: Passed

// Тесты для функции remove_last_point
void TestRemoveLastPoint_no7() {
    // Проверяем удаление последней точки из пути, когда путь содержит одну точку
    Path path = { .size = 1, .points = {{1, 1}} };
    remove_last_point(&path);
    printf("TestRemoveLastPoint_no7: %s\n", path.size == 0 ? "Passed" : "Failed");
}  // Ожидание: Passed

void TestRemoveLastPoint_no8() {
    // Проверяем удаление последней точки из пути, когда путь содержит две точки
    Path path = { .size = 2, .points = {{1, 1}, {2, 2}} };
    remove_last_point(&path);
    printf("TestRemoveLastPoint_no8: %s\n", path.size == 1 && path.points[0].x == 1 ? "Passed" : "Failed");
}  // Ожидание: Passed

void TestSearchPath_no9() {
    // Проверяем успешный поиск пути в лабиринте
    int maze[3][3] = { {0, 1, 0}, {0, 0, 0}, {1, 0, 0} };
    int visited[3][3] = { {0} };
    Path path = { .size = 0 };
    bool result = search_path(maze, visited, &path, 0, 0, 2, 2, 3, 3);
    printf("TestSearchPath_no9: %s\n", result && path.size > 0 ? "Passed" : "Failed");
}  // Ожидание: Passed

void TestSearchPath_no10() {
    // Проверяем, что путь не найден в полностью заблокированном лабиринте
    int maze[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
    int visited[3][3] = { {0} };
    Path path = { .size = 0 };
    bool result = search_path(maze, visited, &path, 0, 0, 2, 2, 3, 3);
    printf("TestSearchPath_no10: %s\n", result ? "Passed" : "Failed");
}  // Ожидание: Failed

// Основная функция для запуска тестов
int main() {
    TestCanMove_no1();
    TestCanMove_no2();
    TestCanMove_no3();
    TestCanMove_no4();
    TestAddPoint_no5();
    TestAddPoint_no6();
    TestRemoveLastPoint_no7();
    TestRemoveLastPoint_no8();
    TestSearchPath_no9();
    TestSearchPath_no10();

    return 0;
}

