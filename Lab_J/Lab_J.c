#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101
#define HASH1_MULTIPLIER 31
#define HASH2_MULTIPLIER 17
#define HASH2_MOD (TABLE_SIZE - 1)

#define EMPTY_SLOT 0
#define OCCUPIED_SLOT 1
#define DELETED_SLOT 2

// Структура таблицы
typedef struct {
    char* value;
    int state; // EMPTY_SLOT, OCCUPIED_SLOT, DELETED_SLOT
} HashEntry;

static HashEntry table[TABLE_SIZE];

// Функция инициализации таблицы
void initTable(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].value = NULL;
        table[i].state = EMPTY_SLOT;
    }
}

// Функции хеширования
int hash1(const char* s) {
    unsigned int h = 0;
    while (*s)
        h = (h * HASH1_MULTIPLIER + (unsigned char)*s++) % TABLE_SIZE;
    return (int)h;
}

int hash2(const char* s) {
    unsigned int h = 0;
    while (*s)
        h = (h * HASH2_MULTIPLIER + (unsigned char)*s++) % HASH2_MOD;
    return (int)(h % HASH2_MOD) + 1;
}

// Вспомогательная функция для модицифакии Брента
int nextProbeOld(const char* oldValue, int currentPos) {
    int hy1 = hash1(oldValue);
    int hy2 = hash2(oldValue);
    /* найдём t: (hy1 + t*hy2)%m == currentPos */
    int t = 0, pos;
    do {
        pos = (hy1 + t * hy2) % TABLE_SIZE;
        t++;
    } while (pos != currentPos && t < TABLE_SIZE);
    /* теперь nextOld = (hy1 + t*hy2)%m */
    return (hy1 + t * hy2) % TABLE_SIZE;
}

// Функция вставки
void insertKey(const char* s) {
    int h1 = hash1(s), h2 = hash2(s);
    int firstDeleted = -1, pos;

    for (int i = 0;; i++) {
        pos = (h1 + i * h2) % TABLE_SIZE;

        if (table[pos].state == OCCUPIED_SLOT) {
            if (strcmp(table[pos].value, s) == 0)
                return; // дубликат

            if (table[pos].state == OCCUPIED_SLOT) {
                /* попробуем сдвинуть именно старый элемент */
                int nextOld = nextProbeOld(table[pos].value, pos);
                if (table[nextOld].state != OCCUPIED_SLOT) {
                    /* пересадим старого в его nextOld */
                    table[nextOld] = table[pos];
                    table[pos].state = EMPTY_SLOT;
                    /* тут же вставим новый */
                    break;
                }
            }
        } else if (table[pos].state == DELETED_SLOT) {
            if (firstDeleted < 0)
                firstDeleted = pos;
        } else {
            break;
        }
    }

    /* если был tombstone — займём его */
    if (firstDeleted >= 0)
        pos = firstDeleted;

    table[pos].value = _strdup(s);
    table[pos].state = OCCUPIED_SLOT;
}

// Функция пооиска по ключу
int searchKey(const char* s) {
    int h1 = hash1(s), h2 = hash2(s);
    for (int i = 0;; i++) {
        int pos = (h1 + i * h2) % TABLE_SIZE;
        if (table[pos].state == OCCUPIED_SLOT &&
            strcmp(table[pos].value, s) == 0)
            return pos;
        if (table[pos].state == EMPTY_SLOT)
            return -1;
    }
}

// Функция удаления по ключу
void deleteKey(const char* s) {
    int pos = searchKey(s);
    if (pos < 0) {
        printf("deleteKey: '%s' not found\n", s);
        return;
    }
    free(table[pos].value);
    table[pos].value = NULL;
    table[pos].state = DELETED_SLOT;
}

// Вывод всей таблицы
void printTable(void) {
    puts("Current hash table contents:");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].state == OCCUPIED_SLOT) {
            printf(" [%3d] -> %s\n", i, table[i].value);
        }
    }
}

// Фукнция высвобождения памяти из под таблицы
void freeTable(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].state == OCCUPIED_SLOT)
            free(table[i].value);
        table[i].state = EMPTY_SLOT;
    }
}

