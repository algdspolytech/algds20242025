#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;         
    int level;      
    struct Node* next; 
} Node;


Node* crNode(int value, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->level = level;
    newNode->next = NULL;
    return newNode;
}

int deleteNode(Node** head, int level) {
    if (*head == NULL) {
        return -1; 
    }

    Node* temp = *head;
    Node* prev = NULL;

    if (temp->level == level) {
        *head = temp->next;
        free(temp);
        return 0;
    }

    while (temp != NULL && temp->level != level) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return -1;  
    }

    prev->next = temp->next;
    free(temp);
    return 0; 
}

int insert(Node** head, int value, int level) {
    Node* current = *head;
    while (current != NULL) {
        if (current->level == level) {
            return -1; 
        }
        current = current->next;
    }

    Node* newNode = crNode(value, level);
    Node* currentNode;

    if (*head == NULL || (*head)->level > level) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        currentNode = *head;
        while (currentNode->next != NULL && currentNode->next->level <= level) {
            currentNode = currentNode->next;
        }
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
    return 0;
}



Node* search(Node* head, int level) {
    Node* current = head;
    while (current != NULL) {
        if (current->level == level) {
            printf("Node found: value = %d, level = %d\n", current->value, current->level);
            return current; 
        }
        current = current->next;
    }
    return NULL;
}


void printRoster(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("Element: %d, Level: %d\n", current->value, current->level);
        current = current->next;
    }
}

void freeRoster(Node** head) {
    if (*head == NULL) {
        return; 
    }

    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next; 
        free(current);        
        current = next;      
    }

    *head = NULL; 
}

// Тесты

void TestDeleteHeadElement_no1() {
     //Удаление головного элемента 
    Node* head = NULL;
    insert(&head, 10, 1);
    insert(&head, 20, 2);
    deleteNode(&head, 1);
    printf("TestDeleteHeadElement_no1: ");
    printRoster(head);
    freeRoster(&head);
}

void TestSearchExistingElement_no2() {
     //Поиск существующего элемента 
    Node* head = NULL;
    insert(&head, 30, 3);
    insert(&head, 20, 2);
    insert(&head, 10, 1);
    printf("TestSearchExistingElement_no2: ");
    search(head, 2);
    freeRoster(&head);
}

void TestDeleteMiddleElement_no3() {
    // Удаление элемента из середины списка. 
    Node* head = NULL;
    insert(&head, 10, 1);
    insert(&head, 20, 2);
    insert(&head, 30, 3);
    printf("TestDeleteMiddleElement_no3: ");
    int result = deleteNode(&head, 2);
    if (result == 0) {
        printf("Successfully deleted element with level 2.\n");
    }
    printRoster(head);
    freeRoster(&head);
}

void TestSearchNonExistentElement_no4() {
     //Поиск несуществующего элемента 
    Node* head = NULL;
    insert(&head, 10, 1);
    Node* result = search(head, 2); 
    printf("TestSearchNonExistentElement_no4: ");
    if (result) {
        printf("Found element: %d, Level: %d\n", result->value, result->level);
    }
    else {
        printf("Element is not found.\n");
    }
    freeRoster(&head);
}

void TestAddToEmptyList_no5() {
    //Добавление элемента в пустой список  
    Node* head = NULL;
    insert(&head, 10, 1); 
    printf("TestAddToEmptyList_no5: ");
    printRoster(head);
    freeRoster(&head);
}

void TestAddMultipleElements_no6() {
     //Добавление нескольких элементов в список 
    Node* head = NULL;
    insert(&head, 30, 3);
    insert(&head, 10, 1);
    insert(&head, 20, 2);
    printf("TestAddMultipleElements_no6: ");
    printRoster(head);
    freeRoster(&head);
}

void TestDeleteAllElementsAndCheckEmpty_no7() {
    //Удаление всех элементов и проверка, что список пуст 
    Node* head = NULL;
    insert(&head, 30, 3);
    insert(&head, 20, 2);
    insert(&head, 10, 1);
    deleteNode(&head, 1);
    deleteNode(&head, 2);
    deleteNode(&head, 3);
    if (head == NULL) {
        printf("TestDeleteAllElementsAndCheckEmpty: The list is empty\n");
    }
    else {
        printf("TestDeleteAllElementsAndCheckEmpty: Error: the list is not empty\n");
    }
    freeRoster(&head);
}

void TestAddSingleElementToNonEmptyList_no8() {
    //Добавление элемента в непустой список 
    Node* head = NULL;
    insert(&head, 10, 1); 
    insert(&head, 20, 2); 
    printf("TestAddSingleElementToNonEmptyList_no8: ");
    printRoster(head);
    freeRoster(&head);
}

void TestAddDuplicatePriority_no9() {
    //Попытка добавления элемента с уже существующим приоритетом 
    Node* head = NULL;
    insert(&head, 10, 1);
    printf("TestAddDuplicatePriority_no9: \n");
    int result = insert(&head, 20, 1); 
    if (result == -1) {
        printf("Error: Level 1 already exists. Insertion failed.\n");
    }
    else {
        printf("Inserted element with level 1. This is unexpected.\n");
    }
    printf("Current list: ");
    printRoster(head);
    freeRoster(&head);
}

void TestDeleteNonExistentElement_no10() {
       //Попытка удаления несуществующего элемента 
    Node* head = NULL;
    insert(&head, 10, 1);
    printf("TestDeleteNonExistentElement_no10: ");
    int result = deleteNode(&head, 2);
    if (result == -1) {
        printf("Node with level 2 not found.\n");
    }
    freeRoster(&head);
}

int main() {
    TestDeleteHeadElement_no1();
    TestSearchExistingElement_no2();
    TestDeleteMiddleElement_no3();
    TestSearchNonExistentElement_no4();
    TestAddToEmptyList_no5();
    TestAddMultipleElements_no6();
    TestDeleteAllElementsAndCheckEmpty_no7();
    TestAddSingleElementToNonEmptyList_no8();
    TestAddDuplicatePriority_no9();
    TestDeleteNonExistentElement_no10();

    return 0;
}