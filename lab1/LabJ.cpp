#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 128 // Размер хеш-таблицы


// Структура для узла цепочки
typedef struct Node {
    char *key;          // Ключ (ASCII-Z строка)
    struct Node *next;  // Указатель на следующий узел
} Node;

// Структура хеш-таблицы
typedef struct HashTable {
    Node *buckets[TABLE_SIZE]; // Массив указателей на узлы
} HashTable;

// Хеш-функция для ASCII-Z строк
unsigned int hash(const char *key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key++;
    }
    return hash_value % TABLE_SIZE;
}

// Инициализация хеш-таблицы
HashTable *create_table() {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// Создание нового узла
Node *create_node(const char *key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = strdup(key); // Копируем строку
    node->next = NULL;
    return node;
}

// Вставка элемента в хеш-таблицу (a <строка>)
void insert(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *node = table->buckets[index];

    // Проверка, существует ли уже такой ключ
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return; // Ключ уже существует, ничего не делаем
        }
        node = node->next;
    }

    // Ключ не найден, создаем новый узел
    Node *new_node = create_node(key);
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

// Поиск элемента в хеш-таблице (f <строка>)
int search(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *node = table->buckets[index];

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return 1; // Найден
        }
        node = node->next;
    }

    return 0; // Не найден
}

// Удаление элемента из хеш-таблицы (r <строка>)
void delete_item(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *node = table->buckets[index];
    Node *prev = NULL;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL) {
                // Удаление первого узла в цепочке
                table->buckets[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Освобождение памяти хеш-таблицы
void free_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = table->buckets[i];
        while (node != NULL) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

int main() {
    HashTable *table = create_table();
    char command;
    char key[256]; // Буфер для ввода строк

    while (1) {
        if (scanf(" %c", &command) != 1) {
            break; // Конец ввода или ошибка
        }

        if (command == 'a' || command == 'r' || command == 'f') {
            if (scanf("%255s", key) != 1) {
                break; // Ошибка ввода строки
            }

            switch (command) {
                case 'a':
                    insert(table, key);
                    break;
                case 'r':
                    delete_item(table, key);
                    break;
                case 'f':
                    printf(search(table, key) ? "yes\n" : "no\n");
                    fflush(stdout);
                    break;
                default:
                    break;
            }
        } else {
            break; // Неизвестная команда
        }
    }

    free_table(table);
    return 0;
}
