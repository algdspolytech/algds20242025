#include <stdio.h>
#include <list.c>
#define FILENAME "../input.txt"

int main() {
    List list = {NULL};
    readWordsFromFile(&list, FILENAME);

    size_t N;
    printf("Enter the number N: ");
    scanf("%zu", &N);
    printf("Words longer than %zu characters:\n", N);
    printWordsLongerThan(&list, N);

    printf("Enter the length of the word to check: ");
    size_t lengthToCheck;
    scanf("%zu", &lengthToCheck);
    if (hasWordOfLength(&list, lengthToCheck)) {
        printf("Words of length %zu characters:\n", lengthToCheck);
        printWordsOfLength(&list, lengthToCheck);
    } else {
        printf("No words of length %zu characters found.\n", lengthToCheck);
    }

    freeList(&list);
    return 0;
}
