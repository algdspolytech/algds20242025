#include "LibD.h"


Pos* make_pos(int x, int y) {
	Pos* p = (Pos*)malloc(sizeof(Pos));
	p->x = x;
	p->y = y;

	return p;
}

Board* make_board(int N) {
	Board* board = (Board*)malloc(sizeof(Board));
	board->N = N;

	board->lines = (int*)malloc(sizeof(int) * N);
	board->cols = (int*)malloc(sizeof(int) * N);

	for (int i = 0;i < N;i++) {
		board->lines[i] = 1;
		board->cols[i] = 1;
	}

	board->diag_1 = (int*)malloc(sizeof(int) * (2 * N - 1));
	board->diag_2 = (int*)malloc(sizeof(int) * (2 * N - 1));

	for (int i = 0;i < 2*N-1;i++) {
		board->diag_1[i] = 1;
		board->diag_2[i] = 1;
	}

	board->queens = (Pos**)malloc(sizeof(Pos*)*N);
	board->queens_len = 0;

	return board;
}


bool backtrack(Board* b) {
	if (b->queens_len == b->N) return true;

	for (int _x = 0;_x < b->N;_x++) {
		for (int _y = 0;_y < b->N;_y++) {
			int d1 = _x - _y + 7;
			int d2 = _y + _x;

			

			if (b->cols[_x] && b->lines[_y] && b->diag_1[d1] && b->diag_2[d2]) {
				b->cols[_x] = 0;
				b->lines[_y] = 0;
				b->diag_1[d1] = 0;
				b->diag_2[d2] = 0;

				b->queens[b->queens_len] = make_pos(_x, _y);
				b->queens_len += 1;

				bool res = backtrack(b);

				if (res) return true;

				b->queens_len -= 1;
				free(b->queens[b->queens_len]);

				b->cols[_x] = 1;
				b->lines[_y] = 1;
				b->diag_1[d1] = 1;
				b->diag_2[d2] = 1;
			}
		}
	}

	return false;
}

void LibD(const char* input, const char* output) {
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
