#pragma warning(disable:4996)
#include <stdio.h>
#include "Header.h"

int main() {
    HashTable* table = create_table();
    insert(table, "Hello");
    insert(table, "World");
    insert(table, "Test");
    insert(table, "Hello");
    printf("Search 'Hello': %d\n", search(table, "Hello"));
    printf("Search 'World': %d\n", search(table, "World"));
    printf("Search 'NotExist': %d\n", search(table, "NotExist"));
    delete(table, "World");
    printf("After delete 'World': %d\n", search(table, "World"));
    printf("\nTable contents:\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i].str != NULL && !table->items[i].is_deleted) {
            printf("Index %d: %s\n", i, table->items[i].str);
        }
    }
    free_table(table);
    return 0;
}