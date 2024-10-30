#include "main.h"


char* fullname(char* surname, char* name) {
    // Выделяем память под полное имя (40 символов как в вашем коде)
    char* fullname = (char*)malloc(sizeof(char) * 40);
    
    if (fullname == NULL) {
        // Обработка ошибки malloc
        return NULL;
    }

    // Используем snprintf вместо sprintf_s для совместимости с GCC
    snprintf(fullname, 40, "%s %s", surname, name);

    return fullname;
}


Node* add_sort_list(Node* head, Node* New) {

    if (!New)
        return NULL;

    int cmp = 0;
    char* new_fullname = fullname(New->surname, New->name);
    if (head) {
        char* head_fullname = fullname(head->surname, head->name);
        cmp = strcmp(head_fullname, new_fullname);
        free(head_fullname);
    }

    if (head == NULL || New->hours < head->hours ||
        (head->hours == New->hours && cmp > 0)) {
        New->next = head;
        head = New;
    }

    else {

        Node* p;

        p = head;
        char* pn_fullname = (char*)malloc(sizeof(char) * 40);
        if (p->next) {
            pn_fullname = fullname(head->next->surname, head->next->name);
            cmp = strcmp(pn_fullname, new_fullname);
        }
        while ((p->next) && (p->next->hours < New->hours ||
            (p->next->hours == New->hours && cmp < 0))) {
            p = p->next;
            pn_fullname = fullname(p->surname, p->name);
            cmp = strcmp(pn_fullname, new_fullname);
        }
        New->next = p->next;
        p->next = New;
        free(pn_fullname);
    }
    free(new_fullname);
    return head;
}
Node* parse_line(char* line) {

    Node* New = (Node*)malloc(sizeof(Node));
    if (New == NULL) {
        // Обработка ошибки malloc
        return NULL;
    }

    // Используем стандартную функцию sscanf с ограничением на количество символов для строк
    int parsed = sscanf(line, "%d.%d.%d %19s %19s %d\n",
                        &New->date.day, &New->date.month, &New->date.year,
                        New->surname, New->name, &New->hours);

    // Проверяем, что все поля успешно прочитаны
    if (parsed != 6) {
        free(New);  // Освобождаем память в случае ошибки
        return NULL;
    }

    return New;
}

Node* read_file(char* filename) {

    FILE* file;
    Node* Head = NULL;
    char line[100];

    // Используем стандартную функцию fopen вместо fopen_s для кроссплатформенности
    file = fopen(filename, "r");
    if (file == NULL) {
        // Обработка ошибки открытия файла
        perror("Error opening file");
        return NULL;
    }

    // Читаем строки из файла
    while (fgets(line, sizeof(line), file)) {
        Node* New = parse_line(line);
        if (New != NULL) {  // Проверяем, что строка корректно разобрана
            Head = add_sort_list(Head, New);
        }
    }

    fclose(file);
    return Head;
}

HourCounter* count_hours(Node* head, int* count) {

    HourCounter* counter = NULL;
    (*count) = 0;
    Node* p = head;

    while (p) {

        int found = 0;
        for (int i = 0; i < *count; i++) {
            char* counter_fullname = fullname(counter[i].surname, counter[i].name);
            char* p_fullname = fullname(p->surname, p->name);
            int cmp = strcmp(counter_fullname, p_fullname);
            free(counter_fullname);
            free(p_fullname);
            if (cmp == 0) {
                counter[i].total += p->hours;
                found = 1;
                break;
            }
        }

        if (!found && head) {
            counter = realloc(counter, (*count + 1) * sizeof(HourCounter));
            counter[*count] = (HourCounter){ p->date, p->name, p->surname, p->hours };
            (*count)++;
        }

        p = p->next;
    }
    return counter;
}

void print_filtered_list(Node* head, int N) {

    int length;
    HourCounter* counter = count_hours(head, &length);

    for (int i = 0; i < length; i++) {
        if (counter[i].total > N)
            printf("%s %02d.%02d.%04d\n", counter[i].surname, counter[i].date.day,
                counter[i].date.month, counter[i].date.year);
    }
    free(counter);
}

void free_all(Node** head) {
    while ((*head)) {
        Node* p = (*head);
        (*head) = (*head)->next;
        free(p);
    }
}
int main() {
    Node* Schedule = NULL;
    int totalSize = 0;
    HourCounter* totalList = NULL;

    setlocale(LC_ALL, "Russian");

    // Чтение данных из файла
    Schedule = read_file("main.txt");
    if (Schedule == NULL) {
        return 1; // Если не удалось прочитать файл, выходим с ошибкой
    }

    // Подсчет суммарного времени для каждого сотрудника
    totalList = count_hours(Schedule, &totalSize);
    if (totalList == NULL) {
        free_all(&Schedule);
        return 1; // Если не удалось подсчитать время, выходим с ошибкой
    }

    // Сортировка по количеству рабочих часов и фамилии
    // Здесь можно использовать любую подходящую сортировку, например, сортировку вставками
    for (int i = 1; i < totalSize; i++) {
        HourCounter key = totalList[i];
        int j = i - 1;
        while (j >= 0 && (totalList[j].total < key.total || 
                (totalList[j].total == key.total && strcmp(totalList[j].surname, key.surname) > 0))) {
            totalList[j + 1] = totalList[j];
            j--;
        }
        totalList[j + 1] = key;
    }

    // Ввод значения N
    int N;
    printf("Введите минимальное количество рабочих часов: ");
    scanf("%d", &N);

    // Вывод сотрудников, отработавших больше N часов
    for (int i = 0; i < totalSize; i++) {
        if (totalList[i].total > N) {
            printf("%s %02d.%02d.%04d\n", totalList[i].surname, totalList[i].date.day,
                   totalList[i].date.month, totalList[i].date.year);
        }
    }

    // Освобождение памяти
    free(totalList);
    free_all(&Schedule);

    return 0;
}

