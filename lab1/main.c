#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;           // Данные элемента
    int priority;      // Приоритет элемента
    struct Node* next; // Указатель на следующий элемент
} Node;

// Функция для создания нового узла
Node* createNode(int data, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Функция для вставки узла в отсортированный список
int insert(Node** head, int data, int priority) {
    // Ункальность приоритета
    Node* current = *head;
    while (current != NULL) {
        if (current->priority == priority) {
            return -1; // Возвращаем ошибку, если приоритет уже существует
        }
        current = current->next;
    }

    Node* newNode = createNode(data, priority);
    Node* currentNode;

    // Если список пуст или новый узел имеет наивысший приоритет
    if (*head == NULL || (*head)->priority > priority) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        // Найти позицию для вставки
        currentNode = *head;
        while (currentNode->next != NULL && currentNode->next->priority <= priority) {
            currentNode = currentNode->next;
        }
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
    return 0;
}

// Функция для удаления узла по приоритету
int deleteNode(Node** head, int priority) {
    if (*head == NULL) {
        return -1; // Список пустой
    }

    Node* temp = *head;
    Node* prev = NULL;

    // Если узел для удаления - это голова списка
    if (temp->priority == priority) {
        *head = temp->next;
        free(temp);
        return 0;
    }

    while (temp != NULL && temp->priority != priority) {
        prev = temp;
        temp = temp->next;
    }

    // Если узел не найден
    if (temp == NULL) {
        return -1; // Элемент с таким приоритетом не найден
    }

    // Удалить узел
    prev->next = temp->next;
    free(temp);
    return 0; // Успешное удаление
}


// Функция для поиска узла по приоритету
Node* search(Node* head, int priority) {
    Node* current = head;
    while (current != NULL) {
        if (current->priority == priority) {
            printf("Node found: data = %d, priority = %d\n", current->data, current->priority);
            return current; // Узел найден и возвращается
        }
        current = current->next;
    }
    return NULL;
}

// Функция для печати списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("Element: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }
}

void freeList(Node** head) {
    if (*head == NULL) {
        return; // Если список пустой, просто выходим из функции
    }

    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next; // Сохраняем указатель на следующий узел
        free(current);        // Освобождаем текущий узел
        current = next;      // Переходим к следующему узлу
    }

    *head = NULL; // Устанавливаем указатель на голову в NULL
}

// Тесты
void TestAddToEmptyList_no1() {
    Node* head = NULL;
    insert(&head, 10, 1); // Добавляем элемент в пустой список
    printf("TestAddToEmptyList_no1: ");
    printList(head);
    freeList(&head);
    // Ожидается: 10, Приоритет: 1
}

void TestAddSingleElement_no2() {
    Node* head = NULL;
    insert(&head, 10, 1); // Добавляем первый элемент
    insert(&head, 20, 2); // Добавляем элемент в непустой список
    printf("TestAddSingleElementToNonEmptyList_no2: ");
    printList(head);
    freeList(&head);
    // Ожидается: 10, Приоритет: 1; 20, Приоритет: 2
}

void TestAddMultipleElements_no3() {
    Node* head = NULL;
    insert(&head, 30, 3);
    insert(&head, 10, 1);
    insert(&head, 20, 2);
    printf("TestAddMultipleElements_no3: ");
    printList(head);
    freeList(&head);
    // Ожидается: 10, Приоритет: 1; 20, Приоритет: 2; 30, Приоритет: 3
}

void TestAddDuplicatePriority_no4() {
    Node* head = NULL;
    insert(&head, 10, 1);
    printf("TestAddDuplicatePriority_no4: \n");

    // Второй элемент с тем же приоритетом
    int result = insert(&head, 20, 1); // Проверяем результат вставки

    // Проверяем, что функция возвращает ошибку
    if (result == -1) {
        printf("Error: Priority 1 already exists. Insertion failed.\n");
    }
    else {
        printf("Inserted element with priority 1. This is unexpected.\n");
    }

    // Печатаем список, чтобы убедиться, что он не изменился
    printf("Current list: ");
    printList(head);
    freeList(&head);
    // Ожидается: 10, Приоритет: 1
}

void TestDeleteHeadElement_no5() {
    Node* head = NULL;
    insert(&head, 10, 1);
    insert(&head, 20, 2);
    deleteNode(&head, 1);
    printf("TestDeleteHeadElement_no5: ");
    printList(head);
    freeList(&head);
    // Ожидается: 20, Приоритет: 2
}

void TestDeleteMiddleElement_no6() {
    Node* head = NULL;
    insert(&head, 10, 1);
    insert(&head, 20, 2);
    insert(&head, 30, 3);

    printf("TestDeleteMiddleElement_no6: ");

    // Удаляем элемент с приоритетом 2 
    int result = deleteNode(&head, 2);
    if (result == 0) {
        printf("Successfully deleted element with priority 2.\n");
    }

    printList(head);
    freeList(&head);
    // Ожидается: 10, Приоритет: 1; 30, Приоритет: 3
}

void TestDeleteNonExistentElement_no7() {
    Node* head = NULL;
    insert(&head, 10, 1);

    printf("TestDeleteNonExistentElement_no7: ");

    // Пытаемся удалить несуществующий элемент с приоритетом 2 из непустого списка
    int result = deleteNode(&head, 2);
    if (result == -1) {
        printf("Node with priority 2 not found.\n");
    }
    freeList(&head);
}

void TestSearchExistingElement_no8() {
    Node* head = NULL;

    insert(&head, 30, 3);
    insert(&head, 20, 2);
    insert(&head, 10, 1);

    // Поиск для узла с приоритетом 2
    printf("TestSearchExistingElement_no8: ");
    search(head, 2);
    freeList(&head);
    // Ожидается: Найден элемент: 20, Приоритет: 2
}

void TestSearchNonExistentElement_no9() {
    Node* head = NULL;
    insert(&head, 10, 1);
    Node* result = search(head, 2); // Ищем узел с приоритетом 2

    printf("TestSearchNonExistentElement_no9: ");
    if (result) {
        // Если узел найден
        printf("Found element: %d, Priority: %d\n", result->data, result->priority);
    }
    else {
        // Если узел не найден
        printf("Element is not found.\n");
    }
    freeList(&head);
    // Ожидается: Элемент не найден.
}

void TestDeleteAllElementsAndCheckEmpty_no10() {
    Node* head = NULL;

    insert(&head, 30, 3);
    insert(&head, 20, 2);
    insert(&head, 10, 1);

    deleteNode(&head, 1);
    deleteNode(&head, 2);
    deleteNode(&head, 3);

    // Проверяем, пуст ли список
    if (head == NULL) {
        printf("TestDeleteAllElementsAndCheckEmpty: The list is empty\n");
    }
    else {
        printf("TestDeleteAllElementsAndCheckEmpty: Error: the list is not empty\n");
    }
    freeList(&head);
}


int main() {
    TestAddToEmptyList_no1();
    TestAddSingleElement_no2();
    TestAddMultipleElements_no3();
    TestAddDuplicatePriority_no4();
    TestDeleteHeadElement_no5();
    TestDeleteMiddleElement_no6();
    TestDeleteNonExistentElement_no7();
    TestSearchExistingElement_no8();
    TestSearchNonExistentElement_no9();
    TestDeleteAllElementsAndCheckEmpty_no10();

    return 0;
}