#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "tests.h"

#pragma warning(disable : 4996)

#define MAX_NODES 100  // ������������ ���������� ������

int main() {
    setlocale(LC_ALL, "Rus");
    FILE* file = fopen("graph.txt", "r"); // ��������� ���� � ������
    if (!file) {
        printf("������: �� ������� ������� ����!\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n); // ������ ���������� ������

    int graph[MAX_NODES][MAX_NODES];

    // ������ ������� ��������� �� �����
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &graph[i][j]);

    fclose(file);

    int start, end;
    printf("������� ��������� � �������� ������� (0-%d): ", n - 1);
    scanf("%d %d", &start, &end);

    if (start < 0 || start >= n || end < 0 || end >= n) {
        printf("������: ������������ �������!\n");
        return 1;
    }

    if (is_path_exists(graph, n, start, end))
        printf("���� ����� ��������� %d � %d ����������.\n", start, end);
    else
        printf("���� ����� ��������� %d � %d ���.\n", start, end);

    test_graph();

    return 0;
}