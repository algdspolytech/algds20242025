#include "xor_list.h"

int main() {
    Node* head = NULL;

    // Добавляем элементы в список
    add(&head, "Hello");
    add(&head, "World");
    add(&head, "XOR");
    add(&head, "List");

    // Выводим список
    printList(head);

    // Поиск элемента
    Node* found = find(head, "World");
    if (found) {
        printf("Найден элемент: %s\n", found->data);
    }

    // Удаление по ключу
    deleteByKey(&head, "XOR");
    printf("После удаления элемента по ключу:\n");
    printList(head);

    // Удаление по адресу
    if (found) {
        deleteByAddress(&head, found);
        printf("После удаления элемента по адресу:\n");
        printList(head);
    }

    // Освобождаем память
    freeList(head);

    return 0;
}