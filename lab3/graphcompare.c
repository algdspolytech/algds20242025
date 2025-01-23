#include "graphcompare.h";

void readAdjList(const char* path, int graph[MAX_VERT][MAX_VERT], int* vertcount) {
	FILE* file = fopen(path, "r");
	if (!file) {
		fprintf(stderr, "Invalid File Path");
		exit(1);
	}
	if (fscanf(file, "%d", vertcount) != 0) {
		int a = 0;
		int b = 0;
		for (int i = 0; i < vertcount; i++) {
			for (int j = 0; j < vertcount; j++) {
				graph[i][j] = 0;
			}
		}
		while (fscanf(file, "%d:", a) != 0) {
			while (fscanf(file, " %d", b) != 0) {
				graph[a][b] = 1;
			}
		}
	}
	else {
		*vertcount = 0;
	}
}

void readAdjMatrix(const char* path, int graph[MAX_VERT][MAX_VERT], int* vertcount) {
	FILE* file = fopen(path, "r");
	if (!file) {
		fprintf(stderr, "Invalid File Path");
		exit(1);
	}
	if (fscanf(file, "%d", vertcount) != 0) {
		for (int i = 0; i < vertcount; i++) {
			for (int j = 0; j < vertcount; j++) {
				fscanf(file, "%d", graph[i][j]);
			}
		}
	}
	else {
		*vertcount = 0;
	}
}

int graphEquals(const char* pathlist, const char* pathmatrix) {
	int graphlist[MAX_VERT][MAX_VERT];
	int vclist = 0;
	int graphmatrix[MAX_VERT][MAX_VERT];
	int vcmatrix = 0;
	readAdjList(pathlist, graphlist, &vclist);
	readAdjMatrix(pathmatrix, graphmatrix, &vcmatrix);
	if (vclist != vcmatrix) {
		return 0;
	}
	else {
		for (int i = 0; i < vclist; i++) {
			for (int j = 0; j < vclist; j++) {
				if (graphlist[i][j]!=graphmatrix[i][j]) {
					return 0;
				}
			}
		}
		return 1;
	}
}