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
    // ���� �������� ������
    if (maze[pos.x][pos.y] == EXIT) {
        return 1; // ���� ������
    }

    // ���� ��� �� ��������� �������, �������� � ��� ����������
    if (maze[pos.x][pos.y] != START) {
        maze[pos.x][pos.y] = 'X'; // ������� ���������� ������
    }

    // ���������� ��������� ����������� �������� (�����, ����, �����, ������)
    Position directions[4] = {
        {pos.x - 1, pos.y}, // �����
        {pos.x + 1, pos.y}, // ����
        {pos.x, pos.y - 1}, // �����
        {pos.x, pos.y + 1}  // ������
    };

    // ���������� ��� �����������
    for (int i = 0; i < 4; i++) {
        if (isValid(directions[i].x, directions[i].y)) {
            if (findPath(directions[i])) { // ����������� ���������
                return 1; // ���� ������
            }
        }
    }

    // ���� ���� �� ������, ���������� ������� ���������
    // ��������������� ������ ��� ���������, ���� ��� �� ��������� �������
    if (maze[pos.x][pos.y] != START) {
        maze[pos.x][pos.y] = FREE; // ������������ ������
    }
    return 0; // ���� �� ������
}