#include <stdio.h>
#include <stdlib.h>

/// Состояния ячейки в хеш-таблице
#define EMPTY 0
#define USED  1
#define DEL   2

/// Начальный размер хеш-таблицы (простое число ~ 1e6)
#define INIT_CAPACITY 1000003
/// Коэффициент загрузки, при превышении которого делаем rehash
#define LOAD_FACTOR 0.7

typedef struct {
    int  *keys;   // массив ключей
    char *state;  // массив состояний (EMPTY, USED, DEL)
    int  capacity;// текущая ёмкость
    int  size;    // кол-во реально хранящихся элементов (USED)
} HashTable;

/// Прототипы функций
HashTable* createTable(int cap);
void freeTable(HashTable *ht);
unsigned long hashFunction(unsigned long x);
void rehash(HashTable *ht);
int findKey(HashTable *ht, int key);
int insertKey(HashTable *ht, int key);
int removeKey(HashTable *ht, int key);

/// Создаём хеш-таблицу заданного размера
HashTable* createTable(int cap) {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        fprintf(stderr, "Memory alloc error\n");
        exit(EXIT_FAILURE);
    }
    ht->capacity = cap;
    ht->size = 0;
    ht->keys = (int*)malloc(sizeof(int) * cap);
    ht->state = (char*)malloc(sizeof(char) * cap);
    if (!ht->keys || !ht->state) {
        fprintf(stderr, "Memory alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < cap; i++) {
        ht->state[i] = EMPTY;  // все ячейки по умолчанию пустые
    }
    return ht;
}

/// Освобождаем память
void freeTable(HashTable *ht) {
    if (!ht) return;
    free(ht->keys);
    free(ht->state);
    free(ht);
}

/// Простая хеш-функция для int
/// (Можно улучшать, но как минимум так будет работать)
unsigned long hashFunction(unsigned long x) {
    // попробуем вариант типа Knuth:
    // (x * золотое_число) >> некий_сдвиг
    // или что-нибудь из стандартных
    // Для наглядности возьмём что-то простое:
    return x * 2654435789ul;
}

/// Увеличить хеш-таблицу вдвое и перехешировать все элементы
void rehash(HashTable *ht) {
    int oldCap = ht->capacity;
    int newCap = oldCap * 2 + 1; // желательно простое, но можно и так
    int *oldKeys = ht->keys;
    char *oldState = ht->state;

    // Создаём новую, в 2 раза больше
    ht->capacity = newCap;
    ht->keys = (int*)malloc(sizeof(int) * newCap);
    ht->state = (char*)malloc(sizeof(char) * newCap);
    if (!ht->keys || !ht->state) {
        fprintf(stderr, "Memory alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < newCap; i++) {
        ht->state[i] = EMPTY;
    }
    ht->size = 0;

    // Переносим все USED элементы из старой таблицы
    for (int i = 0; i < oldCap; i++) {
        if (oldState[i] == USED) {
            insertKey(ht, oldKeys[i]);
        }
    }

    // Освобождаем старые массивы
    free(oldKeys);
    free(oldState);
}

/// Функция поиска: возвращает 1 если элемент есть, 0 - иначе
int findKey(HashTable *ht, int key) {
    // Начальный индекс
    unsigned long h = hashFunction((unsigned long)key);
    int idx = (int)(h % ht->capacity);

    for (int probe = 0; probe < ht->capacity; probe++) {
        int pos = (idx + probe) % ht->capacity;
        if (ht->state[pos] == EMPTY) {
            // Дошли до пустой ячейки — значит, точно нет
            return 0;
        }
        if (ht->state[pos] == USED && ht->keys[pos] == key) {
            return 1;
        }
        // если state[pos] == DEL или другой ключ — идём дальше
    }
    // Если вдруг мы обошли всю таблицу — нет элемента
    return 0;
}

/// Вставка элемента: возвращает 1, если элемент вставлен впервые, 0 - если уже существует
int insertKey(HashTable *ht, int key) {
    // Если load factor превысил 0.7 — делаем rehash
    if ((double)(ht->size + 1) / ht->capacity > LOAD_FACTOR) {
        rehash(ht);
    }
    unsigned long h = hashFunction((unsigned long)key);
    int idx = (int)(h % ht->capacity);

    int firstDelPos = -1; // запомним первую позицию с DEL, куда можно вставить, если найдём

    for (int probe = 0; probe < ht->capacity; probe++) {
        int pos = (idx + probe) % ht->capacity;
        if (ht->state[pos] == EMPTY) {
            // Пустая ячейка: если уже есть DEL, вставим туда, иначе вставим сюда
            int insertPos = (firstDelPos != -1) ? firstDelPos : pos;
            ht->keys[insertPos] = key;
            ht->state[insertPos] = USED;
            ht->size++;
            return 1;
        } else if (ht->state[pos] == DEL) {
            // Если ещё не зафиксировали первую DEL-позицию, запомним
            if (firstDelPos == -1) {
                firstDelPos = pos;
            }
            // но не прерываемся, надо проверить, нет ли совпадения ключа дальше
        } else if (ht->state[pos] == USED && ht->keys[pos] == key) {
            // Ключ уже существует — не вставляем
            return 0;
        }
    }
    // Если дошли до конца — таблица переполнена (при правильном rehash такое вряд ли)
    return 0;
}

/// Удаление ключа: возвращает 1, если удалён, 0 - если не найден
int removeKey(HashTable *ht, int key) {
    unsigned long h = hashFunction((unsigned long)key);
    int idx = (int)(h % ht->capacity);

    for (int probe = 0; probe < ht->capacity; probe++) {
        int pos = (idx + probe) % ht->capacity;
        if (ht->state[pos] == EMPTY) {
            // Если наткнулись на пустую — элемента точно нет
            return 0;
        }
        if (ht->state[pos] == USED && ht->keys[pos] == key) {
            // Нашли — удаляем
            ht->state[pos] = DEL;
            ht->size--;
            return 1;
        }
        // Если DEL или другой ключ — идём дальше
    }
    return 0;
}

int main(void) {
    // Создаём хеш-таблицу (начальный размер ~ 1e6, можно меньше, можно больше)
    HashTable *ht = createTable(INIT_CAPACITY);

    char op;
    int key;
    while (scanf(" %c %d", &op, &key) == 2) {
        switch(op) {
            case 'a':
                insertKey(ht, key);
                break;
            case 'r':
                removeKey(ht, key);
                break;
            case 'f':
                printf("%s\n", findKey(ht, key) ? "yes" : "no");
                break;
            default:
                // неизвестная операция
                break;
        }
    }

    freeTable(ht);
    return 0;
}
