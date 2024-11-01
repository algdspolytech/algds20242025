
#include <assert.h>>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_WORD 20

#define SIZE_OF_LINE (SIZE_OF_WORD * 4)

struct HandleResult {
    char* str;
    int lenght;
};

struct sortItem {
    char* hours;
    char* name;
    char* date;
    long hoursLong;
};

void fillStrGaps(char* str, int size) {
    for (int i = 0; i < size; i++) {
        str[i] = ' ';
    }
}

void printSortItems(struct sortItem* items, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < SIZE_OF_WORD; j++) {
            printf("%c", items[i].date[j]);
        }

        for (int j = 0; j < SIZE_OF_WORD * 2; j++) {
            printf("%c", items[i].name[j]);
        }

        for (int j = 0; j < SIZE_OF_WORD; j++) {
            printf("%c", items[i].hours[j]);
        }

        printf("\n\n\n");
    }
}

struct HandleResult handleData(char* str, char separator) {
    char* result = malloc(sizeof(char));
    char* currentLine = malloc(sizeof(char) * SIZE_OF_LINE);

    if (!currentLine || !result) {
        printf("error handleData");
        return;
    }
    fillStrGaps(currentLine, SIZE_OF_LINE);

    char* temp;
    int positionCurrentWord = 0;
    int lenghtCurrentWord = 0;

    char c;
    int i = 0;
    int j = 0;

    int resultPosition = 0;
    while (1) {
        c = str[i];
        i++;

        if (c == '\n' || c == '\0') {
            j++;
            temp = realloc(result, sizeof(char) * j * SIZE_OF_LINE);

            if (temp) {
                result = temp;
            }
            else {
                free(result);
                printf("error handleData");
                return;
            }
            for (int k = 0; k < SIZE_OF_LINE; k++) {
                result[resultPosition] = currentLine[k];

                resultPosition++;
            }

            fillStrGaps(currentLine, SIZE_OF_LINE);
            positionCurrentWord = 0;
            lenghtCurrentWord = 0;
        }
        else {
            if ((c != separator) && (c != ' ')) {
                currentLine[positionCurrentWord] = c;
                lenghtCurrentWord++;
                positionCurrentWord++;
            }
            else {
                positionCurrentWord += SIZE_OF_WORD - lenghtCurrentWord;
                lenghtCurrentWord = 0;
            }
        }

        if (c == '\0') {
            break;
        }
    }
    result[(j)*SIZE_OF_LINE - 1] = '\0';

    struct HandleResult res;
    res.str = result;
    res.lenght = j * SIZE_OF_LINE;

    return res;
}

char* readFile(char* path) {
    char* result = malloc(sizeof(char));
    if (!result) {
        printf("error readFile");
        return;
    }
    char* temp;

    FILE* fp = fopen(path, "r");

    char c;
    int n = 1;

    if (fp) {
        while ((c = getc(fp)) != EOF) {
            n++;
            temp = realloc(result, n);
            if (temp) {
                result = temp;
                result[n - 2] = c;
            }
            else {
                printf("error readFile");
                free(result);
                return;
            }
        }
        fclose(fp);
    }
    result[n - 1] = '\0';
    return result;
}

struct sortItem* getItems(char* str, int size) {
    struct sortItem* res = malloc(sizeof(struct sortItem) * size / SIZE_OF_LINE);
    char* dateT;
    char* nameT;
    char* hoursT;

    if (!res) {
        printf("eror getItems");
        return;
    }
    int num = 0;
    for (int i = 0; i < size; i += SIZE_OF_LINE) {
        if (str[i] == ' ') break;

        res[num].date = calloc(sizeof(char), SIZE_OF_WORD);
        res[num].name = calloc(sizeof(char), SIZE_OF_WORD * 2);
        res[num].hours = calloc(sizeof(char), SIZE_OF_WORD);

        if ((!res[num].date) || (!res[num].name) || (!res[num].hours)) {
            printf("eror getItems");
            return;
        }

        int j = i;

        int k = 0;
        while (j < i + SIZE_OF_WORD) {
            res[num].date[k] = str[j];
            j++;
            k++;
        }

        k = 0;
        while (j < i + SIZE_OF_WORD * 3) {
            res[num].name[k] = str[j];
            j++;
            k++;
        }

        k = 0;
        while (j < i + SIZE_OF_WORD * 4) {
            res[num].hours[k] = str[j];
            j++;
            k++;
        }
        res[num].hoursLong = strtol(res[num].hours, NULL, 10);
        num++;
    }

    return res;
}

int compare(struct sortItem x, struct sortItem y) {  // x > y
    if (x.hoursLong > y.hoursLong) return 1;
    if (x.hoursLong < y.hoursLong) return 0;

    for (int i = 0; i < SIZE_OF_WORD * 2; i++) {
        if (x.name[i] > y.name[i]) return 1;
        if (x.name[i] < y.name[i]) return 0;
    }
    return 0;
}

void sort(struct sortItem* items, int size) {
    int location;
    struct sortItem newElement;

    for (int i = 1; i < size; i++) {
        newElement = items[i];
        location = i - 1;
        while (location >= 0 && compare(items[location], newElement)) {
            items[location + 1] = items[location];
            location = location - 1;
        }
        items[location + 1] = newElement;
    }
}

void printItemsResult(struct sortItem* items, int size, int n) {
    for (int i = 0; i < size; i++) {
        if (items[i].hoursLong > n) {
            char c;
            for (int j = 0; j < SIZE_OF_WORD; j++) {
                c = items[i].date[j];
                if (c == ' ') break;
                printf("%c", c);
            }
            printf(" ");
            for (int j = 0; j < SIZE_OF_WORD; j++) {
                c = items[i].name[j];
                if (c == ' ') break;
                printf("%c", c);
            }
            printf(" ");
            for (int j = SIZE_OF_WORD; j < SIZE_OF_WORD * 2; j++) {
                c = items[i].name[j];
                if (c == ' ') break;
                printf("%c", c);
            }
            printf("\n");
        }
    }
}

void handleData_Gap_as_separator_HandleResult_1() {
    char* str = "10.12.12 Abc Abc 12\n20.12.12 Abc Aac 12\n30.12.08 zzz zzz 10";
    struct HandleResult result = handleData(str, ' ');

    char* expectedResult =
        "10.12.12            Abc                 Abc                 12          "
        "        20.12.12            Abc                 Aac                 12  "
        "                30.12.08            zzz                 zzz             "
        "    10                 ";

    for (int i = 0; i < 3 * SIZE_OF_LINE; i++) {
        assert(result.str[i] == expectedResult[i]);
    }
}

void handleData_Comma_as_separator_HandleResult_2() {
    char* str = "10.12.12,Abc Abc,12\n20.12.12,Abc Aac,12\n30.12.08,zzz zzz,10";
    struct HandleResult result = handleData(str, ',');

    char* expectedResult =
        "10.12.12            Abc                 Abc                 12          "
        "        20.12.12            Abc                 Aac                 12  "
        "                30.12.08            zzz                 zzz             "
        "    10                 ";

    for (int i = 0; i < 3 * SIZE_OF_LINE; i++) {
        assert(result.str[i] == expectedResult[i]);
    }
}

void handleData_Comma_as_separator_comma_as_name_separator_HandleResult_3() {
    char* str = "10.12.12,Abc,Abc,12\n20.12.12,Abc,Aac,12\n30.12.08,zzz,zzz,10";
    struct HandleResult result = handleData(str, ',');

    char* expectedResult =
        "10.12.12            Abc                 Abc                 12          "
        "        20.12.12            Abc                 Aac                 12  "
        "                30.12.08            zzz                 zzz             "
        "    10                 ";

    for (int i = 0; i < 3 * SIZE_OF_LINE; i++) {
        assert(result.str[i] == expectedResult[i]);
    }
}

void getItems_3Lines_data_SortItem_hoursInt_is_Int_4() {
    struct HandleResult hangleResult;
    hangleResult.str =
        "10.12.12            Abc                 Abc                 12          "
        "        20.12.12            Abc                 Aac                 12  "
        "                30.12.08            zzz                 zzz             "
        "    10                 ";
    hangleResult.lenght = SIZE_OF_LINE * 3;

    struct sortItem* items = getItems(hangleResult.str, hangleResult.lenght);
    assert((10 == items[2].hoursLong) && (12 == items[1].hoursLong) &&
        (12 == items[0].hoursLong));
}

void compare_hours10_hours_12_False_5() {
    struct sortItem x;
    struct sortItem y;

    x.hoursLong = 10;
    y.hoursLong = 12;
    x.name = "abc";
    y.name = "aac";

    assert(!compare(x, y));
}

void compare_hours10_hours_10_abc_aac_True_6() {
    struct sortItem x;
    struct sortItem y;

    x.hoursLong = 10;
    y.hoursLong = 10;
    x.name = "abc";
    y.name = "aac";

    assert(compare(x, y));
}

void compare_hours10_hours_10_abc_abc_False_7() {
    struct sortItem x;
    struct sortItem y;

    x.hoursLong = 10;
    y.hoursLong = 10;
    x.name = "abc";
    y.name = "abc";

    assert(!compare(x, y));
}

void sort_All_hours_different_Sort_items_8() {
    struct sortItem items[3];
    char* name1 = "abc";
    char* name2 = "aac";
    char* name3 = "aaa";

    int hours1 = 2;
    int hours2 = 1;
    int hours3 = 3;

    items[0].hoursLong = hours1;
    items[0].name = name1;

    items[1].hoursLong = hours2;
    items[1].name = name2;

    items[2].hoursLong = hours3;
    items[2].name = name3;

    sort(items, 3);

    assert((items[0].hoursLong == 1) && (items[1].hoursLong == 2) &&
        (items[2].hoursLong == 3));
}

void sort_hours_2_2_3_Sort_items_9() {
    struct sortItem items[3];
    char* name1 = "abc";
    char* name2 = "aac";
    char* name3 = "aaa";

    int hours1 = 2;
    int hours2 = 2;
    int hours3 = 3;

    items[0].hoursLong = hours1;
    items[0].name = name1;

    items[1].hoursLong = hours2;
    items[1].name = name2;

    items[2].hoursLong = hours3;
    items[2].name = name3;

    sort(items, 3);

    assert((items[0].name == "aac") && (items[1].name == "abc") &&
        (items[2].name == "aaa"));
}

void sort_hours_2_2_2_Sort_items_10() {
    struct sortItem items[3];
    char* name1 = "abc";
    char* name2 = "aac";
    char* name3 = "aaa";

    int hours1 = 2;
    int hours2 = 2;
    int hours3 = 2;

    items[0].hoursLong = hours1;
    items[0].name = name1;

    items[1].hoursLong = hours2;
    items[1].name = name2;

    items[2].hoursLong = hours3;
    items[2].name = name3;

    sort(items, 3);

    assert((items[0].name == "aaa") && (items[1].name == "aac") &&
        (items[2].name == "abc"));
}

void unitTests() {
    handleData_Gap_as_separator_HandleResult_1();
    handleData_Comma_as_separator_HandleResult_2();
    handleData_Comma_as_separator_comma_as_name_separator_HandleResult_3();

    getItems_3Lines_data_SortItem_hoursInt_is_Int_4();

    compare_hours10_hours_12_False_5();
    compare_hours10_hours_10_abc_aac_True_6();
    compare_hours10_hours_10_abc_abc_False_7();

    sort_All_hours_different_Sort_items_8();
    sort_hours_2_2_3_Sort_items_9();
    sort_hours_2_2_2_Sort_items_10();
    printf("\n\nunit tests ok\n\n");
}

int main() {
    char* path = "test.txt";

    char* fileStr = readFile(path);

    struct HandleResult handleResult = handleData(fileStr, ' ');

    int countOfItems = handleResult.lenght / SIZE_OF_LINE;

    struct sortItem* items = getItems(handleResult.str, handleResult.lenght);

    sort(items, countOfItems);

    //printSortItems(items, countOfItems);

    printItemsResult(items, countOfItems, 2);

    //unitTests();
}