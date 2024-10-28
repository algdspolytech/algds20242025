#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100 // ������ ���������

typedef struct {
    int x;
    int y;
} Point;

// ����
typedef struct {
    Point points[MAX_SIZE];
    int size;
} Path;

// ��������, ����� �� ������� ��� � ������
bool can_move(int maze[MAX_SIZE][MAX_SIZE], int visited[MAX_SIZE][MAX_SIZE], int x, int y, int rows, int cols) {
    // �������� �� �������
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return false; // ���� ����� �� �������, ���������� false
    }

    bool is_passable = (maze[x][y] == 0); // �������� �� ������������
    bool is_not_visited = !visited[x][y]; // �������� �� ������������

    return is_passable && is_not_visited;
}

// ���������� ����� � ����
void add_point(Path* path, int x, int y) {
    Point new_point;
    new_point.x = x;
    new_point.y = y;
    path->points[path->size] = new_point;
    path->size++;
}

// �������� ��������� ����� �� ����
void remove_last_point(Path* path) {
    if (path->size > 0) {
        path->size--;
    }
}

// ����������� ����� ���� � ���������
bool search_path(int maze[MAX_SIZE][MAX_SIZE], int visited[MAX_SIZE][MAX_SIZE], Path* path, int x, int y, int exit_x, int exit_y, int rows, int cols) {
    if (x == exit_x && y == exit_y) { // ���� �������� ������
        add_point(path, x, y);
        return true;
    }

    if (can_move(maze, visited, x, y, rows, cols)) {
        visited[x][y] = 1;
        add_point(path, x, y);

        // ��������� �������� ������
        if (search_path(maze, visited, path, x + 1, y, exit_x, exit_y, rows, cols) || // ����
            search_path(maze, visited, path, x - 1, y, exit_x, exit_y, rows, cols) || // �����
            search_path(maze, visited, path, x, y + 1, exit_x, exit_y, rows, cols) || // ������
            search_path(maze, visited, path, x, y - 1, exit_x, exit_y, rows, cols)) { // �����
            return true; // ���� ���� ������, ���������� true
        }

        remove_last_point(path);
        visited[x][y] = 0;
    }

    return false; // ���� �� ������
}

// ������������� ������� ���������� ������
void initialize_visited(int visited[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0; // ��� ������ ���������� ������������
        }
    }
}

// ����� ��� ������� can_move
void TestCanMove_no1() {
    // ���������, ��� ����� ������������� � ������ (0, 0) � ������ ���������
    int maze[1][1] = { {0} };
    int visited[1][1] = { {0} };
    bool result = can_move(maze, visited, 0, 0, 1, 1);
    printf("TestCanMove_no1: %s\n", result ? "Passed" : "Failed");
} // ��������: Passed

void TestCanMove_no2() {
    // ���������, ��� ������ ������������� � ������ (0, 0), ���� ��� �������������
    int maze[1][1] = { {1} };
    int visited[1][1] = { {0} };
    bool result = can_move(maze, visited, 0, 0, 1, 1);
    printf("TestCanMove_no2: %s\n", result ? "Passed" : "Failed");
}  // ��������: Failed


void TestCanMove_no3() {
    // ���������, ��� ������ ������������� � ������ (1, 1), ������� ��� ������
    int maze[1][1] = { {0} };
    int visited[1][1] = { {0} };
    bool result = can_move(maze, visited, 1, 1, 1, 1); // ��������� ���������� ��� ������
    printf("TestCanMove_no3: %s\n", result ? "Passed" : "Failed");
}// ��������: Failed

void TestCanMove_no4() {
    // ���������, ��� ������ ������������� � ������ (0, 1), ���� ��� �������������
    int maze[2][2] = { {0, 1}, {0, 0} };
    int visited[2][2] = { {0, 0}, {0, 0} };
    bool result = can_move(maze, visited, 0, 1, 2, 2);
    printf("TestCanMove_no4: %s\n", result ? "Passed" : "Failed");
}  // ��������: Failed

// ����� ��� ������� add_point
void TestAddPoint_no5() {
    // ��������� ���������� ������ ����� � ������ ����
    Path path = { .size = 0 };
    add_point(&path, 1, 1);
    printf("TestAddPoint_no5: %s\n", path.size == 1 && path.points[0].x == 1 && path.points[0].y == 1 ? "Passed" : "Failed");
}  // ��������: Passed

void TestAddPoint_no6() {
    // ��������� ���������� ���� ����� � ����
    Path path = { .size = 0 };
    add_point(&path, 2, 3);
    add_point(&path, 4, 5);
    printf("TestAddPoint_no6: %s\n", path.size == 2 && path.points[1].x == 4 && path.points[1].y == 5 ? "Passed" : "Failed");
} // ��������: Passed

// ����� ��� ������� remove_last_point
void TestRemoveLastPoint_no7() {
    // ��������� �������� ��������� ����� �� ����, ����� ���� �������� ���� �����
    Path path = { .size = 1, .points = {{1, 1}} };
    remove_last_point(&path);
    printf("TestRemoveLastPoint_no7: %s\n", path.size == 0 ? "Passed" : "Failed");
}  // ��������: Passed

void TestRemoveLastPoint_no8() {
    // ��������� �������� ��������� ����� �� ����, ����� ���� �������� ��� �����
    Path path = { .size = 2, .points = {{1, 1}, {2, 2}} };
    remove_last_point(&path);
    printf("TestRemoveLastPoint_no8: %s\n", path.size == 1 && path.points[0].x == 1 ? "Passed" : "Failed");
}  // ��������: Passed

void TestSearchPath_no9() {
    // ��������� �������� ����� ���� � ���������
    int maze[3][3] = { {0, 1, 0}, {0, 0, 0}, {1, 0, 0} };
    int visited[3][3] = { {0} };
    Path path = { .size = 0 };
    bool result = search_path(maze, visited, &path, 0, 0, 2, 2, 3, 3);
    printf("TestSearchPath_no9: %s\n", result && path.size > 0 ? "Passed" : "Failed");
}  // ��������: Passed

void TestSearchPath_no10() {
    // ���������, ��� ���� �� ������ � ��������� ��������������� ���������
    int maze[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
    int visited[3][3] = { {0} };
    Path path = { .size = 0 };
    bool result = search_path(maze, visited, &path, 0, 0, 2, 2, 3, 3);
    printf("TestSearchPath_no10: %s\n", result ? "Passed" : "Failed");
}  // ��������: Failed

// �������� ������� ��� ������� ������
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

