#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#include "functions.h"
#include <string.h>

void readInput(const char* filename, int* n, unsigned int* K, Telegram** telegrams) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Couldn't open input.txt.\n");
        exit(1);
    }
    fscanf(fp, "%d %u", n, K);
    *telegrams = (Telegram*)malloc((*n) * sizeof(Telegram));
    for (int i = 0; i < *n; i++) {
        (*telegrams)[i].id = i + 1;
        fscanf(fp, "%d %d %d", &(*telegrams)[i].l, &(*telegrams)[i].d, &(*telegrams)[i].w);
        (*telegrams)[i].delivered = 0;
    }
    fclose(fp);
}

void writeOutput(const char* filename, int n, Telegram* schedule) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Couldn't open output.txt.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", schedule[i].id);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

unsigned int computeTotalPenalty(int n, Telegram* schedule) {
    unsigned int totalPenalty = 0;
    unsigned int currentTime = 0;
    for (int i = 0; i < n; i++) {
        currentTime += schedule[i].l;
        int delay = currentTime - schedule[i].d;
        if (delay > 0) {
            totalPenalty += (unsigned int)(delay * schedule[i].w);
        }
    }
    return totalPenalty;
}

void scheduleGreedy(int n, Telegram* telegrams, Telegram* schedule) {
    unsigned int currentTime = 0;

    for (int i = 0; i < n; i++) {
        telegrams[i].delivered = 0;
    }

    for (int i = 0; i < n; i++) {
        double maxPriority = -1.0;
        int selected = -1;
        for (int j = 0; j < n; j++) {
            if (!telegrams[j].delivered) {
                double s = telegrams[j].d - telegrams[j].l - currentTime;
                if (s < 1)
                    s = 1;
                double priority = (double)telegrams[j].w / s;
                if (priority > maxPriority) {
                    maxPriority = priority;
                    selected = j;
                }
                else if (priority == maxPriority && telegrams[j].id < telegrams[selected].id) {
                    selected = j; 
                }
            }
        }
        if (selected != -1) {
            schedule[i] = telegrams[selected];
            telegrams[selected].delivered = 1;
            currentTime += telegrams[selected].l;
        }
        else {
            break;
        }
    }
}

int main() {
    int n;
    unsigned int K;
    Telegram* telegrams;

    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = (Telegram*)malloc(n * sizeof(Telegram));
    unsigned int totalPenalty;

    scheduleGreedy(n, telegrams, schedule);
    totalPenalty = computeTotalPenalty(n, schedule);
    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
        free(telegrams);
        free(schedule);
        return 0;
    }

    FILE* fp = fopen("output.txt", "w");
    if (!fp) {
        printf("Couldn't open output.txt.\n");
        free(telegrams);
        free(schedule);
        exit(1);
    }

    fprintf(fp, "0\n");
    fclose(fp);

    free(telegrams);
    free(schedule);
    return 0;
}

