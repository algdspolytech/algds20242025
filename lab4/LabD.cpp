#include "LabD.h"


Pos* make_pos(int x, int y) {
	Pos* p = (Pos*)malloc(sizeof(Pos));
	p->x = x;
	p->y = y;

	return p;
}

Board* make_board(int N) {
	Board* b = (Board*)malloc(sizeof(Board));
	b->N = N;

	b->lines = (int*)malloc(sizeof(int) * N);
	b->columns = (int*)malloc(sizeof(int) * N);

	for (int i = 0;i < N;i++) {
		b->lines[i] = 1;
		b->columns[i] = 1;
	}

	b->diag_1 = (int*)malloc(sizeof(int) * (2 * N - 1));
	b->diag_2 = (int*)malloc(sizeof(int) * (2 * N - 1));

	for (int i = 0;i < 2*N-1;i++) {
		b->diag_1[i] = 1;
		b->diag_2[i] = 1;
	}

	b->queens = (Pos**)malloc(sizeof(Pos*)*N);
	b->queens_length = 0;

	return b;
}


bool backtrack(Board* b) {
	if (b->queens_length == b->N) return true;

	for (int _x = 0;_x < b->N;_x++) {
		for (int _y = 0;_y < b->N;_y++) {
			int d1 = _x - _y + 7;
			int d2 = _y + _x;

			

			if (b->columns[_x] && b->lines[_y] && b->diag_1[d1] && b->diag_2[d2]) {
				b->columns[_x] = 0;
				b->lines[_y] = 0;
				b->diag_1[d1] = 0;
				b->diag_2[d2] = 0;

				b->queens[b->queens_length] = make_pos(_x, _y);
				b->queens_length += 1;

				bool res = backtrack(b);

				if (res) return true;

				b->queens_length -= 1;
				free(b->queens[b->queens_length]);

				b->columns[_x] = 1;
				b->lines[_y] = 1;
				b->diag_1[d1] = 1;
				b->diag_2[d2] = 1;
			}
		}
	}

	return false;
}

void LabD(const char* input, const char* output) {
	FILE* inp = fopen(input, "r");

	int N;
	fscanf(inp, "%i", &N);

	fclose(inp);

	Board* b = make_board(N);

	bool res = backtrack(b);

	FILE* out = fopen(output, "w");
	for (int i = 0;i < N;i++)
		fprintf(out, "%i %i\n", b->queens[i]->x, b->queens[i]->y);
	fclose(out);
}
