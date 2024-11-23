#include "rucksack.h"

#include <stdlib.h>

void printSubset(FILE* out, int** dyn_с_s, int* weight, int c, int s) {
    if(s >= 0 && c >= 0 && dyn_с_s[c][s] != 0) {
        if(dyn_с_s[c - 1][s] == dyn_с_s[c][s])
            printSubset(out, dyn_с_s, weight, c - 1, s);
        else {
            fprintf(out, "%i ", c);
            printSubset(out, dyn_с_s, weight, c - 1, s - weight[c - 1]);
        }

    }
}

void RUCKSACK_exec(FILE* in, FILE* out) {
    int N, B, K;
    int v1, v2;
    fscanf(in, "%i %i %i", &N, &B, &K);

    if(N <= 0)
        return;

    int** dyn_с_s;
    int* size;
    int* value;

    dyn_с_s = malloc((N + 1) * sizeof(int*));
    size = malloc((N + 1) * sizeof(int));
    value = malloc((N + 1) * sizeof(int));

    for (int i = 0; i <= N; i++) {
        dyn_с_s[i] = malloc((B + 1) * sizeof(int));
        dyn_с_s[i][0] = 0;
    }

    for (int i = 0; i <= B; i++)
        dyn_с_s[0][i] = 0;

    for(int i = 0; i < N; i++)
        fscanf(in, "%i", &size[i]);
    for(int i = 0; i < N; i++)
        fscanf(in, "%i", &value[i]);

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= B; j++) {
            v1 = dyn_с_s[i - 1][j];
            v2 = (j >= size[i - 1]) ? (dyn_с_s[i - 1][j - size[i - 1]] + value[i - 1]) : 0;

            if(v1 > v2)
                dyn_с_s[i][j] = v1;
            else
                dyn_с_s[i][j] = v2;
        }
    }

    // for(int i = 0; i <= N; i++) {
    //     for(int j = 0; j <= B; j++) {
    //         fprintf(out, "%i\t", dyn_с_s[i][j]);
    //     }
    //     fprintf(out, "\n");
    // }

    if(dyn_с_s[N][B] < K)
        fprintf(out, "0\n");
    else {
        printSubset(out, dyn_с_s, size, N, B);
        fprintf(out, "\n");
    }
}