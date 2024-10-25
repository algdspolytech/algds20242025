#include "head.h"

int main() {

    FILE* fp;

    fp = fopen("file.txt", "r");
    if (fp == NULL) {
        perror("Error openning file");
        return 1;
    }

    head = AddData(fp);

    fclose(fp);

    TempLessZero(head);

    printf("Enter the temperature \n");
    int findTemp;
    if (scanf("%d", &findTemp) != 1) {
        printf("Error scanning temperature\n");
    }
    int found;
    found = FindTemp(head, findTemp);
    if (found == 0) {
        printf("A day with such a temperature has not been found\n");
    }

    return 0;
}