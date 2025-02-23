#include "FunctList.h"

char* fullname(char* surname, char* name) {

    char* fullname = (char*)malloc(sizeof(char) * 40);
    sprintf_s(fullname, 40, "%s %s", surname, name);

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
    int parsed =
        sscanf_s(line, "%d.%d.%d %s %s %d\n", &New->date.day, &New->date.month,
            &New->date.year, &New->surname, 20, &New->name, 20, &New->hours);

    if (parsed != 6) {
        return NULL;
        free(New);
    }

    return New;
}

Node* read_file(char* filename) {

    FILE* file;
    Node* Head = NULL;
    char line[100];

    fopen_s(&file, filename, "r");
    while (fgets(line, sizeof(line), file)) {
        Node* New = parse_line(line);
        Head = add_sort_list(Head, New);
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
