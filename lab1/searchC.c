#include "search.h"

int CheckWay(int n, int** Ma, int start, int goal) {

    start -= 1;
    goal -= 1;

    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int stack[n];
    for (int i = 0; i < n; i++) {
        stack[i] = -1;
    }
    Stack st = { n, stack };

    push(st, start);
    visited[start] = 1;

    while (stack[0] != -1) {
        int cur = pop(st);

        if (cur == goal)
            return 1;

        for (int i = 0; i < n; i++) {
            if (Ma[cur][i] == 1 && visited[i] == 0) {
                push(st, i);
                visited[i] = 1;
            }
        }
    }
    return 0;
}