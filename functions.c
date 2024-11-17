#include "Header.h"

void read_f(const char* ch, int* b, int* n, int arr[]) {
    FILE* file = fopen(ch, "r");

    if (file == NULL) {
        printf("The file could not be opened\n");
        return;
    }

    fscanf(file, "%d", b);
    fscanf(file, "%d", n);

    // Проверка на максимальный размер массива
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

void findSubsetWithSum(int set[], int n, int target, FILE* file) {
    int found = 0; // Флаг, указывающий, найден ли хотя бы один подмножество

    for (int i = 0; i < (1 << n); i++) {
        int sum = 0;

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum += set[j];
            }
        }

        if (sum == target) {
            found = 1; // Подмножество найдено
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    printf("%d ", set[j]);
                    fprintf(file, "%d ", set[j]);
                }
            }
            fprintf(file, "\n");
            break;
        }
    }

    if (!found) {
        fprintf(file, "0\n");
    }
}

void putToFile(const char* filename, int* sequence, int n, int b) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    findSubsetWithSum(sequence, n, b, file);

    fclose(file);
}

//function for tests
bool findSubset(int set[], int n, int target) {
    bool found = false;

    for (int i = 0; i < (1 << n); i++) {
        int sum = 0;

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum += set[j];
            }
        }
        if (sum == target) {
            found = 1;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    //printf("%d ", set[j]);
                    //fprintf(file, "%d ", set[j]);
                }
            }
            found = true;
           // fprintf(file, "\n");
        }
    }
return found;
}