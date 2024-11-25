#pragma once

//������ � ���. �����������
typedef struct Tree {
	int data; //�������� � ����
	struct Tree* left; //����� ���
	struct Tree* right; //������ ���
	int width; //������ ���������
} Tree_t;

//���������� �������� � �����
int DataWidth(int data);

//������ �����������
void TreeWidth(Tree_t* tree);

//������ ������
int TreeHeight(Tree_t* tree);

//������� ����� � ������
char IntToChar(int digit);

//������ ����� � �������
void WriteData(int data, char** matrix, int x, int y);

//������ ������ � �������
void TreeToMatrix(Tree_t* tree, char** matrix, int* x, int y);

//������ ������
void PrintTree(Tree_t* tree);