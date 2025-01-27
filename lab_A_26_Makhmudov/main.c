//Махмудов Сулейман 5030102/30003
//Вариант 26: Температура (2)
//Файл содержит следующую информацию(построчно) : дата и средняя температура в
//этот день.Считать файл в список таким образом, чтобы он оставался
//отсортированным по возрастанию средней температуры(при совпадении средней
//температуры проводить сортировку следует по дате).Вывести на экран информацию
//обо всех днях, в которых средняя температура оказалась ниже нуля.Ввести с
//клавиатуры число и проверить, есть ли в списке день с такой средней
//температурой

#pragma warning(disable : 4996)

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define M 12 // месяцев в году

typedef struct List {
    int day;
    int month;
    int year;
    float t;
    struct List* next;
} List;

void PrintList(struct List* node) {
    for (; node != NULL; node = node->next)
        printf("%d/%d/%d %.4f\n", node->day, node->month, node->year, node->t);
}

void PrintListBelowZero(struct List* node) {
    for (; node != NULL && node->t < 0.0; node = node->next)
        printf("%d/%d/%d %.4f\n", node->day, node->month, node->year, node->t);
}

List* Clear(List* node) {
    while (node != NULL) {
        List* temp = node;
        node = node->next;

        free(temp);
    }
    return node;
}

int Search(List* node, float t) {

    while (node != NULL) {

        if (node->t == t)
            return 1;

        node = node->next;
    }
    return 0;
}

struct List* CreateNode(int day, int month, int year, float temperature) {
    struct List* temp = malloc(sizeof(struct List));

    if (temp != NULL) {
        temp->day = day;
        temp->month = month;
        temp->year = year;
        temp->t = temperature;
        temp->next = NULL;
    }

    return temp;
}

void InsertBefore(struct List* node, int day, int month, int year,
    float temperature) {
    struct List* temp = malloc(sizeof(struct List));

    if (temp != NULL && node != NULL) {
        temp->day = node->day;
        temp->month = node->month;
        temp->year = node->year;
        temp->t = node->t;

        temp->next = node->next;
        node->next = temp;

        node->day = day;
        node->month = month;
        node->year = year;
        node->t = temperature;
    }
}

int main(void) {

    // lab_A_test0.txt - случайные данные в рамках условия
    // lab_A_test1.txt - отсортировано по температуре, одинаковая дата
    // lab_A_test2.txt - рандомно по температуре, одинаковая дата
    // lab_A_test3.txt - обратно отсортировано по температуре
    // lab_A_test4.txt - случайная температура, одиноковая дата
    // lab_A_test5.txt - только отрицательная температура, одинак. дата
    // lab_A_test6.txt - одинаковая температура, разные даты
    // lab_A_test7.txt - одинаковая температура и даты
    // lab_A_test8.txt - пустой файл
    // lab_A_test9.txt - испорченый файл
    // lab_A_test10.txt - случайные данные в рамках условия

    char filename[] = "lab_A_test0.txt";

    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("can't read file\n");
        return 0;
    }

    List* root = NULL;
    List** node;

    int day, month, year;
    float t;

    int number;
    char format[] = "%d/%d/%d %f\n";

    if (fp) {
        while (number = (fscanf(fp, format, &day, &month, &year, &t)) == 4) {

            node = &root;

            while (*node != NULL) {
                // условие сортировки по температуре и по дате (если температуры
                // совпадают)
                if ((*node)->t > t ||
                    ((*node)->t == t &&
                        ((((*node)->month + (*node)->year * M) > (month + year * M)) ||
                            ((((*node)->month + (*node)->year * M) == (month + year * M)) &&
                                ((*node)->day > day))))) {
                    // вставляем элемент перед текущим
                    InsertBefore(*node, day, month, year, t);
                    break;
                }
                else
                    node = &(*node)->next;
            }
            // если список дошел до конца или список изначально пустой то создаём
            // элемент
            if (*node == NULL) {
                *node = CreateNode(day, month, year, t);
            }
        }
        fclose(fp);
    }

    printf("Sorted list:\n");
    PrintList(root);

    printf("\nList of days with negative average temperature:\n");
    PrintListBelowZero(root);

    printf("\n");
    float search_temp;
    while (printf("Type temperature to search for or type stop: ") &&
        scanf("%f", &search_temp)) {
        if (Search(root, search_temp))
            printf("%.1f is on the list\n", search_temp);
        else
            printf("%.1f is NOT on the list\n", search_temp);
    }
    root = Clear(root);

    return 0;
}