#include "lab1.h"

char* fullname(char* surname, char* name, char* patronymic) {

    char* fullname = (char*)malloc(sizeof(char) * 1000);
    sprintf_s(fullname, 1000, "%s %s %s", surname, name, patronymic);
   
    return fullname;
}

Node* sort_list(Node* head, Node* New) {
    
    if (!New)
        return NULL;

    int cmp = 0;
    char* new_fullname = fullname(New->surname, New->name, New->patronymic);
    if (head) {
        char* head_fullname = fullname(head->surname, head->name, head->patronymic);
        cmp = strcmp(head_fullname, new_fullname);
        free(head_fullname);
    }

    if (head == NULL ||
        (New->date.year < head->date.year) ||
        (New->date.year == head->date.year && New->date.month < head->date.month) ||
        (New->date.year == head->date.year && New->date.month == head->date.month && New->date.day < head->date.day)) {
        New->next = head;
        head = New;
    }

    else {

        Node* p;

        p = head;
        char* pn_fullname = (char*)malloc(sizeof(char) * 1000);
        if (p->next) {
            pn_fullname = fullname(p->next->surname, p->next->name, p->next->patronymic);
            cmp = strcmp(pn_fullname, new_fullname);
        }

        while ((p->next) &&
            ((New->date.year > p->next->date.year) ||
                (New->date.year == p->next->date.year && New->date.month > p->next->date.month) ||
                (New->date.year == p->next->date.year && New->date.month == p->next->date.month && New->date.day > p->next->date.day))) {
            p = p->next;
            pn_fullname = fullname(p->surname, p->name, p->patronymic);
            cmp = strcmp(pn_fullname, new_fullname);
        }
        New->next = p->next;
        p->next = New;
        free(pn_fullname);
    }
    free(new_fullname);
    return head;
}

Node* parse(char* line) {

    Node* New = (Node*)malloc(sizeof(Node));
    int parsed =
        sscanf_s(line, "%s %s %s %d.%d.%d\n", &New->surname, 20, &New->name, 20, &New->patronymic, 20, &New->date.day, &New->date.month,
            &New->date.year);

    if (parsed != 6) {
        free(New);
        return NULL;
    }
    return New;
}

Node* read_file(char* filename) {

    FILE* file;
    Node* Head = NULL;
    char line[100];

    fopen_s(&file, filename, "r");
    while (fgets(line, sizeof(line), file)) {
        Node* New = parse(line);
        if (New) {
            Head = sort_list(Head, New);
        }
    }

    fclose(file);
    return Head;
}

void print_list(Node* head) {
    while (head) {
        printf("%s %s %s %02d.%02d.%04d\n", head->surname, head->name, head->patronymic, head->date.day, head->date.month, head->date.year);
        head = head->next;
    }
}

int main() {

    Node* head = read_file("bd.txt");

    if (head) {
        printf("Sorted list:\n");
        print_list(head);

        Date input_date;
        printf("\nDate (DD.MM.YYYY): ");
        scanf_s("%d.%d.%d", &input_date.day, &input_date.month, &input_date.year);

        Node* p = head;
        printf("\nPeople:\n");
        while (p) {
            if (p->date.day == input_date.day && p->date.month == input_date.month && p->date.year == input_date.year) {
                printf("%s\n", fullname(p->surname, p->name, p->patronymic));
            }
            p = p->next;
        }
        free_all(&head);
    }
    else {
        printf("Error.\n");
    }
    return 0;
}

void free_all(Node** head) {

    Node* p = *head;

    while (p) {
        Node* tmp = p;
        p = p->next;
        free(tmp);
    }
    *head = NULL;
}
