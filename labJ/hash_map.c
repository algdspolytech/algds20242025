#include "hash_map.h"


// Хеш-функция для строк
unsigned int hash(const char *key, int table_size) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key;
        key++;
    }
    return hash_value % table_size;
}

// Создание хеш-таблицы
struct HashTable* create_table(int size) {
    struct HashTable *ht = malloc(sizeof(struct HashTable));
    if (!ht) return NULL;

    ht->size = size;
    ht->table = malloc(sizeof(struct Node*) * size);
    if (!ht->table) {
        free(ht);
        return NULL;
    }

    // Инициализация всех элементов NULL
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

// Вставка строки в таблицу
void insert(struct HashTable *ht, const char *key) {
    if (!ht || !key) return;

    unsigned int index = hash(key, ht->size);

    // Создание нового узла
    struct Node *new_node = malloc(sizeof(struct Node));
    if (!new_node) return;

    new_node->key = strdup(key); // Копирование строки
    if (!new_node->key) {
        free(new_node);
        return;
    }

    // Вставка в начало списка
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

// Поиск строки в таблице
int search(struct HashTable *ht, const char *key) {
    if (!ht || !key) return 0;

    unsigned int index = hash(key, ht->size);
    struct Node *current = ht->table[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1; // Найдено
        }
        current = current->next;
    }
    return 0; // Не найдено
}

// Удаление строки из таблицы
void delete(struct HashTable *ht, const char *key) {
    if (!ht || !key) return;

    unsigned int index = hash(key, ht->size);
    struct Node *current = ht->table[index];
    struct Node *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->table[index] = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Освобождение памяти таблицы
void free_table(struct HashTable *ht) {
    if (!ht) return;

    for (int i = 0; i < ht->size; i++) {
        struct Node *current = ht->table[i];
        while (current) {
            struct Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Пример использования
int main() {
    struct HashTable *ht = create_table(10);

    insert(ht, "hello");
    insert(ht, "world");
    insert(ht, "test");

    printf("Search 'hello': %d\n", search(ht, "hello")); // 1
    printf("Search 'test': %d\n", search(ht, "test"));   // 1
    printf("Search 'missing': %d\n", search(ht, "missing")); // 0

    delete(ht, "hello");
    printf("Search 'hello' after delete: %d\n", search(ht, "hello")); // 0

    free_table(ht);
    return 0;
}