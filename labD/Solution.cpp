#include "Solution.h"


bool backtrack(int* w, int* attached, int** p, int* t, int wl, int al, int pl, int V, int T) {
	if (T < 0) return false;
	if (V == 0) return true;

	for (int i = 0;i < al;i++) {
		if (!attached[i]) {
			bool flag = true;
			for (int k = 0;k < pl;k++) {
				if (p[k][0] == i + 1) {
					for (int j = 0;j < wl;j++) {
						if (w[j] == p[k][1]) {
							flag = false;
							break;
						}
					}
				}

				if (!flag) break;
			}

			if (flag) {
				attached[i] = 1;
				w[wl] = i + 1;

				bool search = backtrack(w, attached, p, t, wl + 1, al, pl, V - 1, T - t[i]);

				if (search)
					return true;

				attached[i] = 0;
			}
		}
	}

	return false;
}

void solution(const char* input_file, const char* output_file) {
	FILE* input = fopen(input_file, "r");

	int W, D, K;
	int* t;
	int N;
	int** p;

	fscanf(input, "%i %i %i", &W, &D, &K);

	t = (int*)malloc(sizeof(int) * W);
	for (int i = 0;i < W;i++)
		fscanf(input, "%i", &t[i]);

	fscanf(input, "%i", &N);

	p = (int**)malloc(sizeof(int*) * N);
	for (int i = 0;i < N;i++) {
		p[i] = (int*)malloc(sizeof(int) * 2);
		fscanf(input, "%i %i", &p[i][0], &p[i][1]);
	}

	int V = W - K;
	int* w = (int*)malloc(sizeof(int) * V);

	int* attached = (int*)malloc(sizeof(int) * W);
	for (int i = 0;i < W;i++) attached[i] = 0;

	bool search = backtrack(w, attached, p, t, 0, W, N, V, D);

	FILE* output = fopen(output_file, "w");
	for (int i = 0;i < V;i++)
		fprintf(output, "%i ", w[i]);

	fclose(output);
	fclose(input);

}