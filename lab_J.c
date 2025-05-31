#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAPACITY 1000
#define MAX_LOAD_FACTOR 0.7

typedef enum { SLOT_EMPTY, SLOT_USED, SLOT_DELETED } SlotState;

typedef struct {
    char* data;
    SlotState state;
} TableEntry;

typedef struct {
    int total_slots;
    int used_slots;
    TableEntry* entries;
} StringHashTable;


StringHashTable* createStringTable(int initial_capacity);
void destroyStringTable(StringHashTable* table);
void addToTable(StringHashTable* table, const char* string);
void removeFromTable(StringHashTable* table, const char* string);
int containsInTable(StringHashTable* table, const char* string);
void resizeTable(StringHashTable* table);


unsigned long calculateHash(const char* str);
int isNumberPrime(int num);
int findNextPrime(int num);
int locateEntry(StringHashTable* table, const char* str, int for_insertion);


unsigned long calculateHash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}


int isNumberPrime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;

    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;

    return 1;
}


int findNextPrime(int num) {
    if (num <= 1) return 2;

    int prime = num;
    while (!isNumberPrime(prime))
        prime++;

    return prime;
}


StringHashTable* createStringTable(int initial_capacity) {
    StringHashTable* new_table = (StringHashTable*)malloc(sizeof(StringHashTable));
    if (!new_table) return NULL;

    new_table->total_slots = findNextPrime(initial_capacity);
    new_table->used_slots = 0;
    new_table->entries = (TableEntry*)calloc(new_table->total_slots, sizeof(TableEntry));

    if (!new_table->entries) {
        free(new_table);
        return NULL;
    }

    for (int i = 0; i < new_table->total_slots; i++) {
        new_table->entries[i].data = NULL;
        new_table->entries[i].state = SLOT_EMPTY;
    }

    return new_table;
}


void destroyStringTable(StringHashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->total_slots; i++) {
        if (table->entries[i].state == SLOT_USED) {
            free(table->entries[i].data);
        }
    }

    free(table->entries);
    free(table);
}


int locateEntry(StringHashTable* table, const char* str, int for_insertion) {
    unsigned long hash_value = calculateHash(str);
    int capacity = table->total_slots;
    int position, first_deleted = -1;


    for (int i = 0; i < capacity; i++) {
        position = (hash_value + i * i) % capacity;

        if (table->entries[position].state == SLOT_EMPTY) {
            return for_insertion ? (first_deleted != -1 ? first_deleted : position) : -1;
        }

        if (table->entries[position].state == SLOT_DELETED) {
            if (first_deleted == -1) {
                first_deleted = position;
            }
        }
        else if (strcmp(table->entries[position].data, str) == 0) {
            return position;
        }
    }

    return -1;
}


void resizeTable(StringHashTable* table) {
    int old_capacity = table->total_slots;
    TableEntry* old_entries = table->entries;

    table->total_slots = findNextPrime(table->total_slots * 2);
    table->used_slots = 0;
    table->entries = (TableEntry*)calloc(table->total_slots, sizeof(TableEntry));

    for (int i = 0; i < table->total_slots; i++) {
        table->entries[i].data = NULL;
        table->entries[i].state = SLOT_EMPTY;
    }

    for (int i = 0; i < old_capacity; i++) {
        if (old_entries[i].state == SLOT_USED) {
            addToTable(table, old_entries[i].data);
            free(old_entries[i].data);
        }
    }

    free(old_entries);
}


void addToTable(StringHashTable* table, const char* string) {
    if (!string) return;


    if ((double)table->used_slots / table->total_slots >= MAX_LOAD_FACTOR) {
        resizeTable(table);
    }


    int position = locateEntry(table, string, 0);
    if (position != -1) return;


    position = locateEntry(table, string, 1);
    if (position == -1) return;


    table->entries[position].data = strdup(string);
    table->entries[position].state = SLOT_USED;
    table->used_slots++;
}


void removeFromTable(StringHashTable* table, const char* string) {
    if (!string) return;

    int position = locateEntry(table, string, 0);
    if (position == -1) return;

    free(table->entries[position].data);
    table->entries[position].data = NULL;
    table->entries[position].state = SLOT_DELETED;
    table->used_slots--;
}

int containsInTable(StringHashTable* table, const char* string) {
    if (!string) return 0;
    return locateEntry(table, string, 0) != -1;
}


int parseUserInput(char* input, char* command, char* word) {
    return sscanf(input, " %c %s", command, word) == 2 && isalpha(*command);
}


int main() {
    StringHashTable* hash_table = createStringTable(INITIAL_CAPACITY);
    char input[1000];
    char command, word[1000];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) break;

        if (parseUserInput(input, &command, word)) {
            switch (command) {
            case 'a':
                addToTable(hash_table, word);
                break;
            case 'r':
                removeFromTable(hash_table, word);
                break;
            case 'f':
                printf(containsInTable(hash_table, word) ? "yes\n" : "no\n");
                break;
            default:
                break;
            }
        }
    }

    destroyStringTable(hash_table);
    return 0;
}