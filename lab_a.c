#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Node {
    char word[100];
    int key;
    struct Node* next;
} Node;

Node* createNode(const char* word, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

int insertSorted(Node** head, const char* word, int key) {
    Node* newNode = createNode(word, key);
    Node* current;

    current = *head;
    while (current != NULL) {
        if (current->key == key) {
            free(newNode);
            return 0;
        }
        current = current->next;
    }

    if (*head == NULL || (*head)->key > key) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        current = *head;
        while (current->next != NULL && current->next->key < key) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return 1; 
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s %d\n", current->word, current->key);
        current = current->next;
    }
}

const char* searchByKey(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->key == key) {
            return current->word; 
        }
        current = current->next;
    }
    return NULL; 
}

int main() {
    

    FILE* file;
    Node* head = NULL;
    char word[100];
    int key;

    file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("The file could not be opened");
        return 1;
    }

    while (fscanf(file, "%s %d", word, &key) == 2) {
        if (!insertSorted(&head, word, key)) {
            printf("Error: Duplicate keyword %d for the word %s", key, word);
        }
    }

    fclose(file);

    printf("A list of words and their corresponding key numbers:\n");
    printList(head);

    printf("Enter the key number to search for:");
    scanf("%d", &key);

    const char* result = searchByKey(head, key);
    if (result != NULL) {
        printf("Word found: %s for key %d\n", result, key);
    }
    else {
        printf("The word with the key %d was not found\n", key);
    }

    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
