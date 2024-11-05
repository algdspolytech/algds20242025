#include <assert.h>>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

struct algorithmProfessorResult {
    char **arr;
    int size;
};

struct couple {
    char *before;
    char *after;
};

struct getCouplesResult {
    int size;
    struct couple *couples;
};

struct createStrArrayResult {
    char **arr;
    int size;
};

char *readFile(char *path) {
    char *result = malloc(sizeof(char));
    if (result == NULL) {
        printf("error readFile");
        return;
    }
    char *temp;

    FILE *fp = fopen(path, "r");

    char c;
    int n = 1;

    if (fp) {
        while ((c = getc(fp)) != EOF) {
            n++;
            temp = realloc(result, n);
            if (temp != NULL) {
                result = temp;
                result[n - 2] = c;
            } else {
                printf("\nerror readFile\n");
                free(result);
                return;
            }
        }
        fclose(fp);
    }
    result[n - 1] = '\0';
    return result;
}


void addCharInStr(char **str, char c, int newSize) {
    if (newSize < 2) {
        printf("\nerror addCharInStr newSize must be > 1\n");
        return;
    }

    if (newSize == 2) {
        *str = malloc(sizeof(char) * newSize);
        if (str == NULL) {
            printf("\nerror addCharInStr\n");
            return;
        }
    } else {
        char *temp;
        temp = realloc(*str, sizeof(char) * newSize);

        if (temp == NULL) {
            printf("\nerror addCharInStr\n");
            free(*str);
            return;
        } else {
            *str = temp;
        }
    }

    (*str)[newSize - 2] = c;
    (*str)[newSize - 1] = '\0';
}


struct getCouplesResult getCouples(char *str) {
    struct couple *res = malloc(sizeof(struct couple));
    if (res == NULL) {
        printf("error getCoupls");
        return;
    }
    char c;
    int i = 0;
    int resPosition = 0;

    struct couple *resTemp;

    while (1) {
        resTemp = realloc(res, sizeof(struct couple) * (resPosition + 1));
        if (resTemp == NULL) {
            printf("\nerror getCoupls\n");
            free(res);
            return;
        } else {
            res = resTemp;
        }

        c = str[i];

        int lenOfWord = 2;
        while (c != ' ') {
            addCharInStr(&(res[resPosition].before), c, lenOfWord);
            i++;
            c = str[i];
            lenOfWord++;
        }

        i++;
        c = str[i];

        lenOfWord = 2;
        while (c != '\n' && c != '\0') {
            addCharInStr(&(res[resPosition].after), c, lenOfWord);
            i++;
            c = str[i];
            lenOfWord++;
        }

        if (c == '\0') break;
        i++;

        resPosition++;
    }

    struct getCouplesResult result;
    result.size = resPosition + 1;
    result.couples = res;
    return result;
}

int compareStr(char *x, char *y) {
    int i = 0;
    while (1) {
        if (x[i] == '\0' || y[i] == '\0') return x[i] == y[i];
        if (x[i] != y[i]) return 0;
        i++;
    }
}

int isExistInStrArray(char **arr, int size, char *str) {
    for (int i = 0; i < size; i++) {
        if (compareStr(arr[i], str)) return 1;
    }
    return 0;
}

void addItemToStrArray(char ***arr, int newSize, char *str) {
    char **arrTemp = realloc(*arr, newSize * sizeof(char *));
    if (arrTemp == NULL) {
        printf("\nerror addItemToStrArray\n");
        free(*arr);
        return;
    } else {
        *arr = arrTemp;
    }
    (*arr)[newSize - 1] = str;
}

struct createStrArrayResult createStrArray(struct couple *couples, int size) {
    int resSize = 2;
    char **res = malloc(sizeof(char *) * resSize);

    if (res == NULL) {
        printf("\nerror createStrArray\n");
        return;
    }

    res[0] = couples[0].before;
    res[1] = couples[0].after;

    for (int i = 1; i < size; i++) {
        if (!isExistInStrArray(res, resSize, couples[i].before)) {
            resSize++;
            addItemToStrArray(&res, resSize, couples[i].before);
        }

        if (!isExistInStrArray(res, resSize, couples[i].after)) {
            resSize++;
            addItemToStrArray(&res, resSize, couples[i].after);
        }
    }

    struct createStrArrayResult result;
    result.arr = res;
    result.size = resSize;

    return result;
}


void pastSelectedItemBeforeItem(char **arr, int base, int moving) {
    char *movingWord = arr[moving];
    char *temp1 = arr[base];
    char *temp2;

    for (int i = base; i < moving; i++) {
        temp2 = arr[i + 1];
        arr[i + 1] = temp1;
        temp1 = temp2;
    }
    arr[base] = movingWord;
}

int isTrueOrder(struct couple *couples, int size, char *x, char *y) {
    for (int i = 0; i < size; i++) {
        if (compareStr(couples[i].before, y)) {
            if (compareStr(couples[i].after, x)) return 0;
        }
    }
    return 1;
}

int getStrLength(char *str) {
    int res = 0;
    char c = str[0];
    while (c != '\0') {
        res++;
        c = str[res];
    }
    res++;
    return res;
}

char **getCopyCharArr(char **arr, int size) {
    char **res = calloc(sizeof(char *), size);
    if (res == NULL) {
        printf("\neror getCopyCharArr\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        int lenghCurrentWord = getStrLength(arr[i]);
        res[i] = calloc(sizeof(char), lenghCurrentWord);
        if (res[i] == NULL) {
            printf("\neror getCopyCharArr\n");
            return;
        }
        for (int j = 0; j < lenghCurrentWord; j++) {
            res[i][j] = arr[i][j];
        }
    }
    return res;
}

int compareStrArrays(char **arr1, char **arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (!compareStr(arr1[i], arr2[i])) return 0;
    }
    return 1;
}

void printStrArr(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
}

struct algorithmProfessorResult algorithmProfessor(struct couple *couples, int sizeCouples) {
    char *errT = "error";
    char **err = &errT;

    struct createStrArrayResult arrayStruct = createStrArray(couples, sizeCouples);
    int arrSize = arrayStruct.size;
    char **arr = arrayStruct.arr;

    char **startArrCopy = getCopyCharArr(arr, arrSize);
    int isError = 0;
    while (1) {
        int break_while = 0;
        for (int i = 0; i < arrSize - 1; i++) {
            int break_i = 0;
            for (int j = i + 1; j < arrSize; j++) {
                if (!isTrueOrder(couples, sizeCouples, arr[i], arr[j])) {
                    pastSelectedItemBeforeItem(arr, i, j);

                    if (compareStrArrays(startArrCopy, arr, arrSize)) {
                        break_while = 1;
                        isError = 1;
                    }
                    break_i = 1;
                    break;
                }
            }
            if (break_i) break;
            if (i == arrSize - 2) break_while = 1;
        }
        if (break_while) break;
    }

    struct algorithmProfessorResult res;

    if (!isError) {
        res.arr = arr;
        res.size = arrSize;
    } else {
        free(arr);
        res.arr = err;
        res.size = 1;
    }
    return res;
}

int main() {
    char *path = "../tests/testSimple.txt";
    char *str = readFile(path);
    printf("\n%s\n", str);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *couples = couplesResult.couples;
    int couplesSize = couplesResult.size;

    struct algorithmProfessorResult res = algorithmProfessor(couples, couplesSize);
    printf("result: ");
    printStrArr(res.arr, res.size);

    allTests();
}
