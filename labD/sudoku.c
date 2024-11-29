#include <stdio.h>

#include "sudoku.h"

#define size(a) (a.n*a.n)

int *at(sudoku s, int x, int y) {
    return &(s.data[x + y * size(s)]);
}

sudoku create_sudoku(int n) {
    sudoku tr;
    tr.data = (int *) malloc(sizeof(int) * n * n * n * n);
    tr.n = n;
    return tr;
}

void free_sudoku(sudoku s) {
    free(s.data);
}

int get(sudoku s, int x, int y) {
    return s.data[y * size(s) + x];
}

void set(sudoku s, int x, int y, int data) {
    s.data[y * size(s) + x] = data;
}

sudoku open_sudoku(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return ERR;
    int n;
    if (fscanf(f, "%d", &n) != 1) return ERR;
    if (n < 2 || n > 9) return ERR;
    sudoku tr = create_sudoku(n);
    for (int y = 0; y < size(tr); y++) {
        for (int x = 0; x < size(tr); x++) {
            if (fscanf(f, "%d", at(tr, x, y)) != 1) {
                free_sudoku(tr);
                return ERR;
            }
            if (get(tr, x, y) < 0 || get(tr, x, y) > n * n) {
                free_sudoku(tr);
                return ERR;
            }
        }
    }

    fclose(f);
    return tr;
}

int write_sudoku(const char *filename, sudoku s) {
    FILE *f = fopen(filename, "w");

    if (!f) return BAD_OUTPUT;

    fprintf(f, "%d\n", s.n);
    for (int y = 0; y < size(s); y++) {
        for (int x = 0; x < size(s); x++) {
            fprintf(f, "%d ", get(s, x, y));
        }
        fprintf(f, "\n");
    }

    fclose(f);

    return NO_ERR;
}

sudoku copy_sudoku(sudoku s) {
    sudoku tr = create_sudoku(s.n);
    for (int y = 0; y < size(s); y++) {
        for (int x = 0; x < size(s); x++) {
            set(tr, x, y, get(s, x, y));
        }
    }

    return tr;
}

int get_chunk_id(int x, int y, int n) {
    return x / n + (y / n) * n;
}

int check(sudoku s1) {
    for (int y = 0; y < size(s1); y++) {
        for (int x = 0; x < size(s1); x++) {
            if (get(s1, x, y) == 0) continue;
            //check row
            for (int x1 = 0; x1 < x; x1++) {
                if (get(s1, x, y) == get(s1, x1, y)) return 0;
            }
            for (int x1 = x + 1; x1 < size(s1); x1++) {
                if (get(s1, x, y) == get(s1, x1, y)) return 0;
            }

            //check column
            for (int y1 = 0; y1 < y; y1++) {
                if (get(s1, x, y) == get(s1, x, y1)) return 0;
            }
            for (int y1 = y + 1; y1 < size(s1); y1++) {
                if (get(s1, x, y) == get(s1, x, y1)) return 0;
            }

            //chunk borders
            int ch_id = get_chunk_id(x, y, s1.n);
            int x0 = (ch_id % s1.n) * s1.n;
            int x1 = (ch_id % s1.n) * s1.n + s1.n;
            int y0 = ch_id / s1.n * s1.n;
            int y1 = ch_id / s1.n * s1.n + s1.n;
            //check chunk
            for (int j = y0; j < y1; j++) {
                for (int i = x0; i < x1; i++) {
                    if (x == i && y == j) continue;
                    if (get(s1, x, y) == get(s1, i, j)) {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

int check_done(sudoku s1) {
    for (int y = 0; y < size(s1); y++) {
        for (int x = 0; x < size(s1); x++) {
            if (get(s1, x, y) == 0) return 0;
            //check row
            for (int x1 = 0; x1 < x; x1++) {
                if (get(s1, x, y) == get(s1, x1, y)) return 0;
            }
            for (int x1 = x + 1; x1 < size(s1); x1++) {
                if (get(s1, x, y) == get(s1, x1, y)) return 0;
            }

            //check column
            for (int y1 = 0; y1 < y; y1++) {
                if (get(s1, x, y) == get(s1, x, y1)) return 0;
            }
            for (int y1 = y + 1; y1 < size(s1); y1++) {
                if (get(s1, x, y) == get(s1, x, y1)) return 0;
            }

            //chunk borders
            int ch_id = get_chunk_id(x, y, s1.n);
            int x0 = (ch_id % s1.n) * s1.n;
            int x1 = (ch_id % s1.n) * s1.n + s1.n;
            int y0 = ch_id / s1.n * s1.n;
            int y1 = ch_id / s1.n * s1.n + s1.n;
            //check chunk
            for (int j = y0; j < y1; j++) {
                for (int i = x0; i < x1; i++) {
                    if (x == i && y == j) continue;
                    if (get(s1, x, y) == get(s1, i, j)) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int find_least_candidates(sudoku s) {
    int xmin = -1;
    int ymin = -1;
    int min_candidates = INT_MAX;

    for (int x = 0; x < size(s); x++) {
        for (int y = 0; y < size(s); y++) {
            if (get(s, x, y) == 0) {
                int candidates = 0;
                for (int i = 0; i < size(s); i++) {
                    set(s, x, y, i);
                    if (check(s)) candidates++;
                }
                if (candidates < min_candidates) {
                    min_candidates = candidates;
                    xmin = x;
                    ymin = y;
                }
                set(s, x, y, 0);
            }
        }
    }
    return xmin + ymin * size(s);
}

sudoku backtrack(sudoku s) {
    int r = find_least_candidates(s);
    if (r < 0) {
        return s;
    }
    int x = r % size(s);
    int y = r / size(s);

    for (int i = 1; i <= size(s); i++) {
        set(s, x, y, i);
        if (check(s)) {
            sudoku s2 = copy_sudoku(s);
            sudoku s1 = backtrack(s2);
            if (check_done(s1)) {
                return s1;
            }
            free_sudoku(s2);
        }
    }


    return s;
}

int solve_sudoku(const char *filename, const char *output) {
    sudoku s = open_sudoku(filename);
    if (s.data == ERR.data) return BAD_INPUT;
    sudoku s1 = backtrack(s);
    if (check_done(s1)) {
        free_sudoku(s);
        return write_sudoku(output, s1);
    }
    else {
        //error
        FILE *of = fopen(output, "w");
        if (!of) return BAD_OUTPUT;
        fprintf(of, "0");
        fclose(of);
        free_sudoku(s);
        return 1;
    }
}