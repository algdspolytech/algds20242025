#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS
#define INITIAL_SIZE 1000

typedef enum { FREE, USED, REMOVED } EntryState;

typedef struct {
    char* data;
    EntryState state;
} TableEntry;

typedef struct {
    int tableSize;
    int itemCount;
    TableEntry* entries;
} StringHashTable;

StringHashTable* createStringTable(int initialCapacity);
void freeStringTable(StringHashTable* ht);
void insertEntry(StringHashTable* ht, const char* str);
void deleteEntry(StringHashTable* ht, const char* str);
int containsEntry(StringHashTable* ht, const char* str);
void resizeTable(StringHashTable* ht);
int locateEntryPosition(StringHashTable* ht, const char* str, int* foundFlag);
long long calculateHashValue(const char* text);
int parseCommand(char* input, char* cmd, char* buffer);

long long calculateHashValue(const char* text) {
    long long hash = 5381;
    int c;

    while ((c = *text++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}

StringHashTable* createStringTable(int initialCapacity) {
    if (initialCapacity <= 0) return NULL;

    StringHashTable* ht = (StringHashTable*)malloc(sizeof(StringHashTable));
    if (!ht) return NULL;

    ht->tableSize = initialCapacity;
    ht->itemCount = 0;
    ht->entries = (TableEntry*)calloc(initialCapacity, sizeof(TableEntry));
    if (!ht->entries) {
        free(ht);
        return NULL;
    }

    for (int i = 0; i < initialCapacity; i++) {
        ht->entries[i].data = NULL;
        ht->entries[i].state = FREE;
    }

    return ht;
}

void freeStringTable(StringHashTable* ht) {
    if (!ht) return;

    for (int i = 0; i < ht->tableSize; i++) {
        free(ht->entries[i].data);
    }
    free(ht->entries);
    free(ht);
}

int locateEntryPosition(StringHashTable* ht, const char* str, int* foundFlag) {
    long long hash = calculateHashValue(str);
    int capacity = ht->tableSize;
    *foundFlag = 0;

    for (int i = 0; i < capacity; i++) {
        int pos = (hash + i * i) % capacity;
        TableEntry* entry = &ht->entries[pos];

        if (entry->state == FREE) {
            return pos;
        }

        if (entry->state == USED && strcmp(entry->data, str) == 0) {
            *foundFlag = 1;
            return pos;
        }
    }

    return -1;
}

void resizeTable(StringHashTable* ht) {
    int oldCapacity = ht->tableSize;
    TableEntry* oldEntries = ht->entries;

    int newCapacity = oldCapacity * 2;
    TableEntry* newEntries = (TableEntry*)calloc(newCapacity, sizeof(TableEntry));
    for (int i = 0; i < newCapacity; i++) {
        newEntries[i].data = NULL;
        newEntries[i].state = FREE;
    }

    ht->entries = newEntries;
    ht->tableSize = newCapacity;
    ht->itemCount = 0;

    for (int i = 0; i < oldCapacity; i++) {
        if (oldEntries[i].state == USED) {
            insertEntry(ht, oldEntries[i].data);
        }
        free(oldEntries[i].data);
    }

    free(oldEntries);
}

void insertEntry(StringHashTable* ht, const char* str) {
    if (!str) return;

    if ((double)ht->itemCount / (double)ht->tableSize >= 0.7) {
        resizeTable(ht);
    }

    int exists;
    int pos = locateEntryPosition(ht, str, &exists);
    if (pos == -1 || exists) return;

    ht->entries[pos].data = strdup(str);
    ht->entries[pos].state = USED;
    ht->itemCount++;
}

void deleteEntry(StringHashTable* ht, const char* str) {
    if (!str) return;

    int exists;
    int pos = locateEntryPosition(ht, str, &exists);
    if (pos == -1 || !exists) return;

    free(ht->entries[pos].data);
    ht->entries[pos].data = NULL;
    ht->entries[pos].state = REMOVED;
    ht->itemCount--;
}

int containsEntry(StringHashTable* ht, const char* str) {
    if (!str) return 0;

    int exists;
    locateEntryPosition(ht, str, &exists);
    return exists;
}

int parseCommand(char* input, char* cmd, char* buffer) {
    return sscanf(input, " %c %s", cmd, buffer) == 2 && isalpha(*cmd);
}

int main() {
    StringHashTable* stringTable = createStringTable(INITIAL_SIZE);
    char inputLine[1000];
    char operation, textBuffer[1000];

    while (fgets(inputLine, sizeof(inputLine), stdin)) {
        inputLine[strcspn(inputLine, "\n")] = '\0';
        if (strlen(inputLine) == 0) break;

        if (parseCommand(inputLine, &operation, textBuffer)) {
            switch (operation) {
            case 'a':
                insertEntry(stringTable, textBuffer);
                break;
            case 'r':
                deleteEntry(stringTable, textBuffer);
                break;
            case 'f':
                printf(containsEntry(stringTable, textBuffer) ? "yes\n" : "no\n");
                break;
            default:
                break;
            }
        }
    }

    freeStringTable(stringTable);
    return 0;
}