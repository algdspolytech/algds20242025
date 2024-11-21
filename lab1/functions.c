#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void read_input(const char* filename, int* n, unsigned int* K, Telegram** telegrams) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }
    fscanf_s(file, "%d %u", n, K);
    *telegrams = (Telegram*)malloc((*n) * sizeof(Telegram));
    for (int i = 0; i < *n; i++) {
        (*telegrams)[i].index = i + 1;
        fscanf_s(file, "%d %d %d", &(*telegrams)[i].l, &(*telegrams)[i].d, &(*telegrams)[i].w);
    }
    fclose(file);
}

void write_output(const char* filename, int n, int* order) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }
    if (order == NULL) {
        fprintf(file, "0\n");
    }
    else {
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d%c", order[i], (i == n - 1) ? '\n' : ' ');
        }
    }
    fclose(file);
}

int cmp_edd(const void* a, const void* b) {
    Telegram* ta = (Telegram*)a;
    Telegram* tb = (Telegram*)b;
    if (ta->d != tb->d)
        return ta->d - tb->d;
    else
        return ta->index - tb->index;
}

int cmp_wspt(const void* a, const void* b) {
    Telegram* ta = (Telegram*)a;
    Telegram* tb = (Telegram*)b;
    double ratio_a = (double)ta->l / ta->w;
    double ratio_b = (double)tb->l / tb->w; 
    if (ratio_a < ratio_b)
        return -1;
    else if (ratio_a > ratio_b)
        return 1;
    else
        return ta->index - tb->index;
}

int cmp_w(const void* a, const void* b) {
    Telegram* ta = (Telegram*)a;
    Telegram* tb = (Telegram*)b;
    if (ta->w != tb->w)
        return tb->w - ta->w;
    else
        return ta->index - tb->index;
}

int schedule_telegrams(int n, unsigned int K, Telegram* telegrams, int* order) {
    Telegram* temp = (Telegram*)malloc(n * sizeof(Telegram));
    unsigned int total_penalty;
    int success = 0;

    // First attempt: Earliest Due Date (EDD)
    memcpy(temp, telegrams, n * sizeof(Telegram));
    qsort(temp, n, sizeof(Telegram), cmp_edd);

    total_penalty = 0;
    unsigned int time = 0;
    for (int i = 0; i < n; i++) {
        time += temp[i].l;
        if (time > temp[i].d) {
            total_penalty += (time - temp[i].d) * temp[i].w;
            if (total_penalty > K)
                break;
        }
    }

    if (total_penalty <= K) {
        for (int i = 0; i < n; i++)
            order[i] = temp[i].index;
        success = 1;
        free(temp);
        return success;
    }

    // Second attempt: Weighted Shortest Processing Time (WSPT)
    memcpy(temp, telegrams, n * sizeof(Telegram));
    qsort(temp, n, sizeof(Telegram), cmp_wspt);

    total_penalty = 0;
    time = 0;
    for (int i = 0; i < n; i++) {
        time += temp[i].l;
        if (time > temp[i].d) {
            total_penalty += (time - temp[i].d) * temp[i].w;
            if (total_penalty > K)
                break;
        }
    }

    if (total_penalty <= K) {
        for (int i = 0; i < n; i++)
            order[i] = temp[i].index;
        success = 1;
        free(temp);
        return success;
    }

    // Third attempt: Decreasing Penalty Weight (w_i)
    memcpy(temp, telegrams, n * sizeof(Telegram));
    qsort(temp, n, sizeof(Telegram), cmp_w);
    total_penalty = 0;
    time = 0;
    for (int i = 0; i < n; i++) {
        time += temp[i].l;
        if (time > temp[i].d) {
            total_penalty += (time - temp[i].d) * temp[i].w;
            if (total_penalty > K)
                break;
        }
    }

    if (total_penalty <= K) {
        for (int i = 0; i < n; i++)
            order[i] = temp[i].index;
        success = 1;
        free(temp);
        return success;
    }

    free(temp);
    return 0;
}