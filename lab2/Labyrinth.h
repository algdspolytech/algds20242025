#pragma once
#define N 4

//����������� �������� �� ���������
typedef enum Direction_t {
	NONE_DIR,
	LEFT,
	UP,
	RIGHT,
	DOWN
} Direction_t;

//�����
typedef enum Flag_t {
	NO,
	YES
} Flag_t;

//�������� ���������
typedef struct Square_t {
	Flag_t exit; //�������� �� �������
	Flag_t flag; //���� �� ��� � ���� ������
	Flag_t* dirs; //�������� �� � ������ �� �����������: �����, ������, ������, �����
	Direction_t prev; //�����������, ������ ������ � ��� ������
} Square_t;

//��������
typedef struct Labyrinth_t {
	int rows; //���������� �����
	int cols; //���������� ��������
	Square_t** squares; //������ ���������
} Labyrinth_t;

//������� ������
Square_t CreateSquare(Flag_t left, Flag_t up, Flag_t right, Flag_t down);

//����� ���� � ������
int FindExit(Labyrinth_t lab, int row, int col, Direction_t* path, int* pathsize);

//������� ����
void PrintPath(Direction_t* path, int pathsize);

//�������� �����
void ClearFlags(Labyrinth_t lab);

//����� ���� � ������ � ����������� �������� ������
int ExitPath(Labyrinth_t lab, int row, int col, Direction_t* path);
