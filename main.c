#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_TABLE_CAPACITY 1024
#define MAX_LOAD_THRESHOLD 0.75
#define GOLDEN_NUMBER 2654435789ul

typedef struct {
    int stored_value;
    char cell_status;
} HashCell;

typedef struct {
    HashCell* cells_array;
    int current_capacity;
    int occupied_count;
} HashDictionary;

HashDictionary* initializeHashDictionary(int initial_size) {
    if (initial_size <= 0) {
        fprintf(stderr, "Invalid initial size for hash table\n");
        exit(EXIT_FAILURE);
    }

    HashDictionary* dict = (HashDictionary*)malloc(sizeof(HashDictionary));
    if (!dict) {
        fprintf(stderr, "Memory allocation failed for hash dictionary\n");
        exit(EXIT_FAILURE);
    }

    dict->current_capacity = initial_size;
    dict->occupied_count = 0;
    dict->cells_array = (HashCell*)malloc(sizeof(HashCell) * initial_size);

    if (!dict->cells_array) {
        free(dict);
        fprintf(stderr, "Memory allocation failed for hash cells\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < initial_size; i++) {
        dict->cells_array[i].stored_value = 0;
        dict->cells_array[i].cell_status = 'E';
    }

    return dict;
}

void resizeHashDictionary(HashDictionary* dict);
bool addValueToDictionary(HashDictionary* dict, int value);

void releaseHashDictionary(HashDictionary* dict) {
    if (!dict) return;

    if (dict->cells_array) {
        free(dict->cells_array);
    }
    free(dict);
}

unsigned long computeHashValue(unsigned long input) {
    if (input == 0) {
        return 1; // Ensure we don't return 0 for input 0
    }
    return input * GOLDEN_NUMBER;
}

void resizeHashDictionary(HashDictionary* dict) {
    int previous_capacity = dict->current_capacity;
    int new_capacity = previous_capacity * 2 + 1;

    HashCell* old_cells = dict->cells_array;

    dict->current_capacity = new_capacity;
    dict->occupied_count = 0;
    dict->cells_array = (HashCell*)malloc(sizeof(HashCell) * new_capacity);

    if (!dict->cells_array) {
        fprintf(stderr, "Memory allocation failed during resizing\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < new_capacity; i++) {
        dict->cells_array[i].stored_value = 0;
        dict->cells_array[i].cell_status = 'E';
    }

    for (int i = 0; i < previous_capacity; i++) {
        if (old_cells[i].cell_status == 'U') {
            addValueToDictionary(dict, old_cells[i].stored_value);
        }
    }

    free(old_cells);
}

bool addValueToDictionary(HashDictionary* dict, int value) {
    if (!dict) return false;

    if ((double)(dict->occupied_count + 1) / dict->current_capacity > MAX_LOAD_THRESHOLD) {
        resizeHashDictionary(dict);
    }

    unsigned long hash_result = computeHashValue((unsigned long)value);
    int base_position = (int)(hash_result % dict->current_capacity);

    int first_deleted_slot = -1;

    for (int attempt = 0; attempt < dict->current_capacity; attempt++) {
        int current_position = (base_position + attempt) % dict->current_capacity;

        if (dict->cells_array[current_position].cell_status == 'E') {
            int insertion_position = (first_deleted_slot != -1) ? first_deleted_slot : current_position;
            dict->cells_array[insertion_position].stored_value = value;
            dict->cells_array[insertion_position].cell_status = 'U';
            dict->occupied_count++;
            return true;
        }
        else if (dict->cells_array[current_position].cell_status == 'D') {
            if (first_deleted_slot == -1) {
                first_deleted_slot = current_position;
            }
        }
        else if (dict->cells_array[current_position].cell_status == 'U' &&
            dict->cells_array[current_position].stored_value == value) {
            return false;
        }
    }
    return false;
}

bool containsValueInDictionary(HashDictionary* dict, int value) {
    if (!dict || dict->occupied_count == 0) return false;

    unsigned long hash_result = computeHashValue((unsigned long)value);
    int base_position = (int)(hash_result % dict->current_capacity);

    for (int attempt = 0; attempt < dict->current_capacity; attempt++) {
        int current_position = (base_position + attempt) % dict->current_capacity;

        if (dict->cells_array[current_position].cell_status == 'E') {
            return false;
        }

        if (dict->cells_array[current_position].cell_status == 'U' &&
            dict->cells_array[current_position].stored_value == value) {
            return true;
        }
    }
    return false;
}

bool removeValueFromDictionary(HashDictionary* dict, int value) {
    if (!dict || dict->occupied_count == 0) return false;

    unsigned long hash_result = computeHashValue((unsigned long)value);
    int base_position = (int)(hash_result % dict->current_capacity);

    for (int attempt = 0; attempt < dict->current_capacity; attempt++) {
        int current_position = (base_position + attempt) % dict->current_capacity;

        if (dict->cells_array[current_position].cell_status == 'E') {
            return false;
        }

        if (dict->cells_array[current_position].cell_status == 'U' &&
            dict->cells_array[current_position].stored_value == value) {
            dict->cells_array[current_position].cell_status = 'D';
            dict->occupied_count--;
            return true;
        }
    }
    return false;
}

int main(void) {
    HashDictionary* number_dict = initializeHashDictionary(INITIAL_TABLE_CAPACITY);

    char operation;
    int input_number;

    while (scanf(" %c %d", &operation, &input_number) == 2) {
        switch (operation) {
        case 'a':
            addValueToDictionary(number_dict, input_number);
            break;
        case 'r':
            removeValueFromDictionary(number_dict, input_number);
            break;
        case 'f':
            printf("%s\n", containsValueInDictionary(number_dict, input_number) ? "yes" : "no");
            break;
        default:
            fprintf(stderr, "Unknown operation: %c\n", operation);
            break;
        }
    }

    releaseHashDictionary(number_dict);
    return 0;
}