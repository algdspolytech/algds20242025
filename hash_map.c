#include "hash_map.h"


unsigned int string_hash(const char* str) {
    const unsigned int BASIS = 0x811C9DC5;
    const unsigned int PRIME = 0x01000193;
    unsigned int value = BASIS;

    while (*str) {
        value ^= *str++;
        value *= PRIME;
    }
    return value % HASH_CAPACITY;
}

void map_init(StringHashMap* map) {
    map->capacity = HASH_CAPACITY;
    map->slots = (BucketEntry**)calloc(HASH_CAPACITY, sizeof(BucketEntry*));
}

void map_put(StringHashMap* map, const char* key) {
    unsigned int slot_idx = string_hash(key);
    BucketEntry* current = map->slots[slot_idx];

    while (current) {
        if (strcmp(current->data, key) == 0) return;
        current = current->chain;
    }

    BucketEntry* new_entry = (BucketEntry*)malloc(sizeof(BucketEntry));
    new_entry->data = strdup(key);
    new_entry->chain = map->slots[slot_idx];
    map->slots[slot_idx] = new_entry;
}

int map_contains(StringHashMap* map, const char* key) {
    unsigned int slot_idx = string_hash(key);
    BucketEntry* entry = map->slots[slot_idx];

    while (entry) {
        if (strcmp(entry->data, key) == 0) return 1;
        entry = entry->chain;
    }
    return 0;
}

void map_delete(StringHashMap* map, const char* key) {
    unsigned int slot_idx = string_hash(key);
    BucketEntry* entry = map->slots[slot_idx];
    BucketEntry* prev = NULL;

    while (entry) {
        if (strcmp(entry->data, key) == 0) {
            if (prev) {
                prev->chain = entry->chain;
            } else {
                map->slots[slot_idx] = entry->chain;
            }
            free(entry->data);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->chain;
    }
}

void map_cleanup(StringHashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        BucketEntry* entry = map->slots[i];
        while (entry) {
            BucketEntry* temp = entry;
            entry = entry->chain;
            free(temp->data);
            free(temp);
        }
    }
    free(map->slots);
}

// int main() {
//     StringHashMap str_map;
//     map_init(&str_map);
//
//     char operation[2];
//     char input_key[KEY_MAX_LEN + 1];
//
//     while (fscanf(stdin, "%1s %255s", operation, input_key) == 2) {
//         switch (operation[0]) {
//             case 'a':
//                 map_put(&str_map, input_key);
//                 break;
//             case 'r':
//                 map_delete(&str_map, input_key);
//                 break;
//             case 'f':
//                 printf("%s\n", map_contains(&str_map, input_key) ? "yes" : "no");
//                 break;
//             default:
//                 break;
//         }
//     }
//
//     map_cleanup(&str_map);
//     return 0;
// }