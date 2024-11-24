#ifndef MAIN_H
#define MAIN_H

#define MAX_WORD_LENGTH 100
#define MAX_LIST_SIZE 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int key;
} Pair;

void run_tests(); // Прототип функции run_tests
void read_data(Pair* list, int* n, const char* filename);
int compare(const void* a, const void* b);

#endif // MAIN_H
