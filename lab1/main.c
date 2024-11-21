#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    int n;
    unsigned int K;
    Telegram* telegrams;
    read_input("Maximum_n.txt", &n, &K, &telegrams);
    int* order = (int*)malloc(n * sizeof(int));

    if (schedule_telegrams(n, K, telegrams, order)) {
        write_output("output.txt", n, order);
    }
    else {
        write_output("output.txt", 0, NULL);
    }

    free(order);
    free(telegrams);
    return 0;
}
