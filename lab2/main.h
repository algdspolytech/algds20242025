#ifndef MAIN_H
#define MAIN_H
#define MAX_VERTICES 100

#ifdef __cplusplus
extern "C" {
#endif

	// ������� ��� ������ ����� �� ����� � �������������� � ���� ������ ���������
	void readAdjacencyList(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertex_count);

	// ������� ��� ������ ����� �� ����� � �������������� � ���� ������� ���������
	void readAdjacencyMatrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertex_count);

	// ������� ��� ��������� ���� ������ �� ����������
	int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertex_count);

#ifdef __cplusplus
}
#endif

#endif 



