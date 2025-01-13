#include "labA.h"

char* create_fullname(char* last_name, char* first_name, char* middle_name) {
    char* full_name = (char*)malloc(sizeof(char) * 1000);
    sprintf_s(full_name, 1000, "%s %s %s", last_name, first_name, middle_name);
    return full_name;
}

Node* insert_sorted(Node* head, Node* new_node) {
    if (!new_node)
        return NULL;

    int comparison = 0;
    char* new_full_name = create_fullname(new_node->last_name, new_node->first_name, new_node->middle_name);
    if (head) {
        char* head_full_name = create_fullname(head->last_name, head->first_name, head->middle_name);
        comparison = strcmp(head_full_name, new_full_name);
        free(head_full_name);
    }

    if (head == NULL ||
        (new_node->date.year < head->date.year) ||
        (new_node->date.year == head->date.year && new_node->date.month < head->date.month) ||
        (new_node->date.year == head->date.year && new_node->date.month == head->date.month && new_node->date.day < head->date.day)) {
        new_node->next = head;
        head = new_node;
    }
    else {
        Node* current = head;
        char* next_full_name = (char*)malloc(sizeof(char) * 1000);
        if (current->next) {
            next_full_name = create_fullname(current->next->last_name, current->next->first_name, current->next->middle_name);
            comparison = strcmp(next_full_name, new_full_name);
        }

        while ((current->next) &&
            ((new_node->date.year > current->next->date.year) ||
                (new_node->date.year == current->next->date.year && new_node->date.month > current->next->date.month) ||
                (new_node->date.year == current->next->date.year && new_node->date.month == current->next->date.month && new_node->date.day > current->next->date.day))) {
            current = current->next;
            next_full_name = create_fullname(current->last_name, current->first_name, current->middle_name);
            comparison = strcmp(next_full_name, new_full_name);
        }
        new_node->next = current->next;
        current->next = new_node;
        free(next_full_name);
    }
    free(new_full_name);
    return head;
}

Node* parse_line(char* line) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    int parsed = sscanf_s(line, "%s %s %s %d.%d.%d", &new_node->last_name, 20, &new_node->first_name, 20, &new_node->middle_name, 20, &new_node->date.day, &new_node->date.month, &new_node->date.year);

        if (parsed != 6) {
            free(new_node);
            return NULL;
        }
    return new_node;
}

Node* read_from_file(char* filename) {
    FILE* file;
    Node* head = NULL;
    char line[100];

    fopen_s(&file, filename, "r");
    while (fgets(line, sizeof(line), file)) {
        Node* new_node = parse_line(line);
        if (new_node) {
            head = insert_sorted(head, new_node);
        }
    }

    fclose(file);
    return head;
}

void display_list(Node* head) {
    while (head) {
        printf("%s %s %s %02d.%02d.%04d", head->last_name, head->first_name, head->middle_name, head->date.day, head->date.month, head->date.year);
            head = head->next;
    }
}

int main() {
    Node* head = read_from_file("data.txt");

    if (head) {
        printf("Sorted list:\n");
        display_list(head);

        Date input_date;
        printf("\nDate (DD.MM.YYYY): ");
        scanf_s("%d.%d.%d", &input_date.day, &input_date.month, &input_date.year);

        Node* current = head;
        printf("\nPeople:\n");
        while (current) {
            if (current->date.day == input_date.day && current->date.month == input_date.month && current->date.year == input_date.year) {
                printf("%s", create_fullname(current->last_name, current->first_name, current->middle_name));
            }
            current = current->next;
        }
        free_memory(&head);
    }
    else {
        printf("Error.\n");
    }
    return 0;
}

void free_memory(Node** head) {
    Node* current = *head;

    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}
