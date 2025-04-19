#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Состояния ячейки */
#define EMPTY_SLOT 0
#define OCCUPIED_SLOT 1
#define DELETED_SLOT 2

/* Константы хеш‑таблицы */
#define TABLE_SIZE 101
#define HASH1_MULTIPLIER 31
#define HASH2_MULTIPLIER 17
#define HASH2_MOD (TABLE_SIZE - 1)

/* Элемент таблицы */
typedef struct {
    char* value;
    int state; /* EMPTY_SLOT / OCCUPIED_SLOT / DELETED_SLOT */
} HashEntry;

void initTable(void);
void insertKey(const char* s);
int searchKey(const char* s);
void deleteKey(const char* s);
void freeTable(void);

#ifdef __cplusplus
}
#endif

#endif
