#include "header.h"

int main() {
    char A[1000];
    int B;

    FILE* input;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error openning file");
        return 1;
    }
    if (fscanf(input, "%s %d", &A, &B) != 2) {
        fprintf(stderr, "Error reading values from file\n");
    }
    fclose(input);

    if (!GenerateExpressions(A, B)) {
        WriteOutput("0");
    }

    return 0;
}