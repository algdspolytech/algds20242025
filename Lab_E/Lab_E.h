#pragma once

typedef struct Tree {
    char* value;          // �������� ����
    struct Tree* left;  // ����� ������
    struct Tree* right; // ������ ������
    int width;          // ������ ���������
};

//������� ���������� ���� width ������������� ������
void Fill_width(Tree* tree);

// ������� ������ ������ � �������. ������ �����, ������ ������
void Print_Tree(Tree* tree, int depth);
