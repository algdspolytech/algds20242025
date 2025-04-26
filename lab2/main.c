#include <stdio.h>
#include "hashtable.h"

int main() {
    // Создание хеш-таблицы
    HashTable *ht = create_table();

    // Вставка элементов
    printf("Вставка элементов в хэш-таблицу...\n");
    insert(ht, "apple", 10);
    insert(ht, "banana", 20);
    insert(ht, "cherry", 30);

    // Поиск элементов
    printf("Поиск элемента 'apple': %d\n", search(ht, "apple"));
    printf("Поиск элемента 'banana': %d\n", search(ht, "banana"));
    printf("Поиск элемента 'cherry': %d\n", search(ht, "cherry"));
    printf("Поиск элемента 'orange': %d\n", search(ht, "orange"));

    // Удаление элемента
    printf("Удаление элемента 'banana'...\n");
    remove_entry(ht, "banana");

    // Поиск после удаления
    printf("Поиск элемента 'banana' после его удаления: %d\n", search(ht, "banana"));

    // Вывод таблицы
    printf("\nВывод хэш-таблицы:\n");
    print_table(ht);

    // Удаление хеш-таблицы
    destroy_table(ht);

    return 0;
}
