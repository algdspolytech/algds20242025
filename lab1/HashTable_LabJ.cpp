#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <string.h>


#define CRC32_C 0x1EDC6F41
#define HASHTABLE_SHIFT_MODULE 2 // Шаг квадратичной последовательности проб
#define HASHTABLE_FILLING_DEGREE 0.5 // Степень заполнения таблицы при которой производиться перевыделение памяти под таблицу
#define EMPTY_WORD (char*)'\0'


struct HashTable {
    char** hashtable;
    bool* occupied;

    size_t size;
    size_t filled;
};

uint32_t crc32c_table[256]; // Эту таблицу просчитаем заранее для ускорения работы программы

// Функция для заполнения таблицы crc32c_table
void create_hash_crc32c_table() {
    uint32_t crc; int i, j;

    for (i = 0; i < 256; i++) {
        crc = i;
        for (j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ CRC32_C : crc >> 1;

        crc32c_table[i] = crc;
    }
}

// Хеш-функция
uint32_t hash_crc32c(char* str) {
    uint_least32_t crc; int i, j;

    crc = 0xFFFFFFFF;

    size_t len = strlen(str);
    while (len--)
        crc = crc32c_table[(crc ^ *str++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFF;
}

// Функция создания хештаблицы
HashTable* hashtable_create(size_t size=1000) {
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));

    if (hashtable) {
        hashtable->hashtable = (char**)malloc(sizeof(char*) * size);

        if (hashtable->hashtable)
            memset(hashtable->hashtable, 0, sizeof(char*) * size);

        hashtable->occupied = (bool*)malloc(sizeof(bool) * size);

        if (hashtable->occupied)
            memset(hashtable->occupied, 0, sizeof(bool) * size);

        hashtable->size = size;
        hashtable->filled = 0;
    }

    return hashtable;
}

bool hashtable_search(HashTable* hashtable, char* key) {
    if (!hashtable || !hashtable->hashtable)
        return false; // Таблица не создана
    
    uint32_t hash = hash_crc32c(key) % hashtable->size;
    uint32_t shift = 0;

    while (hashtable->hashtable[(hash + shift) % hashtable->size]) {
        if (!strcmp(hashtable->hashtable[(hash + shift) % hashtable->size], key))
            return true;

        shift = shift ? shift * HASHTABLE_SHIFT_MODULE : 1;
    }
    return false;
}

// Добавление ключа в хештаблицу
void hashtable_add(HashTable* hashtable, char* key) {
    if (!hashtable || !hashtable->hashtable)
        return; // Таблица не создана

    if (hashtable_search(hashtable, key))
        return; // Запись уже есть
    hashtable->filled++;

    if (hashtable->filled > hashtable->size * HASHTABLE_FILLING_DEGREE) {
        HashTable* new_hashtable = hashtable_create(hashtable->size*HASHTABLE_SHIFT_MODULE);
        for (int i = 0;i < hashtable->size;i++) {
            if (hashtable->occupied[i]) {
                hashtable_add(new_hashtable, hashtable->hashtable[i]);
            }
        }
        
        free(hashtable->hashtable);
        free(hashtable->occupied);
        hashtable->hashtable = new_hashtable->hashtable;
        hashtable->occupied = new_hashtable->occupied;
        hashtable->filled = new_hashtable->filled + 1;
        hashtable->size = new_hashtable->size;
        free(new_hashtable);
    }

    uint32_t hash = hash_crc32c(key) % hashtable->size;
    uint32_t shift = 0;

    while (hashtable->occupied[(hash + shift) % hashtable->size])
        shift = shift ? shift * HASHTABLE_SHIFT_MODULE : 1;

    size_t len = strlen(key) + 1;
    hashtable->hashtable[(hash + shift) % hashtable->size] = (char*)malloc(sizeof(char) * len);
    strcpy(hashtable->hashtable[(hash + shift) % hashtable->size], key);
    hashtable->occupied[(hash + shift) % hashtable->size] = true;
}


void hashtable_delete(HashTable* hashtable, char* key) {
    if (!hashtable || !hashtable->hashtable)
        return; // Таблица не создана

    uint32_t hash = hash_crc32c(key) % hashtable->size;
    uint32_t shift = 0;

    while (hashtable->hashtable[(hash + shift) % hashtable->size]) {
        if (!strcmp(hashtable->hashtable[(hash + shift) % hashtable->size], key)) {
            hashtable->occupied[(hash + shift) % hashtable->size] = false;
            free(hashtable->hashtable[(hash + shift) % hashtable->size]);
            hashtable->hashtable[(hash + shift) % hashtable->size] = (char*)"false";

            hashtable->filled--;
            return;
        }

        shift = shift ? shift * HASHTABLE_SHIFT_MODULE : 1;
    }
    return;
}

void hashtable_show(HashTable* hashtable) {
    int counter = 0;
    for (int i = 0;i < hashtable->size;i++) {
        char* key = hashtable->hashtable[i];
        printf("%i %s", i, key == 0 ? "0\n" : key);
        counter += key != 0;
    }
    printf("Counter: %i\n", counter);
}

int main()
{
    create_hash_crc32c_table();

    HashTable* hashtable = hashtable_create();

    char command;

    while ((command = getchar()) != EOF)
    {
        int data = 0;
        scanf("%i", &data);

        
        char* _data = (char*)malloc(sizeof(int) + 1);
        memcpy(_data, &data, sizeof(int));
        _data[sizeof(int)] = '\0';
        

        if (command == 'a') {
            hashtable_add(hashtable, _data);
        }
        else if (command == 'f') {
            if (hashtable_search(hashtable, _data))
                printf("yes\n");
            else
                printf("no\n");
        }
        else if (command == 'r') {
            hashtable_delete(hashtable, _data);
        }

        free(_data);
    }

    return 0;
}
