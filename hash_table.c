#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_table.h"


bool is_prime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}


int get_next_prime(int n) {
	if (n <= 2) return 2;
	if (n % 2 == 0) n++;

	while (!is_prime(n)) {
		n += 2;
	}
	return n;
}


char* my_strdup(const char* s) {
	if (s == NULL) return NULL;
	size_t len = strlen(s) + 1;
	char* new_s = (char*)malloc(len);
	if (new_s == NULL) {
		perror("Memory allocation error for strdup");
		return NULL;
	}
	memcpy(new_s, s, len);
	return new_s;
}


unsigned int hash_string(const char* str, int table_size) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash % table_size;
}

static int rehash(HashTable* ht);


HashTable* create_table(int initial_size, double load_factor_threshold) {
	if (initial_size <= 0) {
		fprintf(stderr, "Error: Initial size must be greater than zero.\n");
		return NULL;
	}

	initial_size = get_next_prime(initial_size);

	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
	if (!ht) {
		perror("Error allocating memory for the hash table structure");
		return NULL;
	}

	ht->table = (HashTableEntry*)malloc(sizeof(HashTableEntry) * initial_size);
	if (!ht->table) {
		perror("Memory allocation error for hash table array");
		free(ht);
		return NULL;
	}

	ht->size = initial_size;
	ht->count = 0;
	ht->deleted_count = 0;
	ht->load_factor_threshold = load_factor_threshold;

	for (int i = 0; i < ht->size; i++) {
		ht->table[i].key = NULL;
		ht->table[i].state = EMPTY;
	}

	printf("Created a Hash Table with size: %d (factual prime size)\n", ht->size);
	return ht;
}


void destroy_table(HashTable* ht) {
	if (!ht) return;

	for (int i = 0; i < ht->size; i++) {
		if (ht->table[i].state == OCCUPIED) {
			free(ht->table[i].key);
		}
	}
	free(ht->table);
	free(ht);
	printf("Hash Table has been destroyed.\n");
}


int insert(HashTable* ht, const char* key) {
	if (!ht || !key) {
		fprintf(stderr, "Error: Hash table or NULL key during insertion.\n");
		return -1;
	}

	// Check load factor BEFORE insertion
	if ((double)(ht->count + 1) / ht->size > ht->load_factor_threshold) {
		printf("The load factor will exceed threshold (%.2f > %.2f). Rehashing...\n",
			(double)(ht->count + 1) / ht->size, ht->load_factor_threshold);
		if (rehash(ht) != 0) {
			fprintf(stderr, "Error: Rehashing failed during insertion.\n");
			return -1;
		}
	}

	unsigned int initial_hash = hash_string(key, ht->size);
	int index;
	int i = 0;
	int first_deleted_slot = -1;

	while (i < ht->size) {
		index = (initial_hash + (unsigned long long)i * i) % ht->size;

		index = (initial_hash + (unsigned long long)i * i) % ht->size;

		if (ht->table[index].state == EMPTY) {
			// If we found a deleted slot earlier, use it
			int insert_idx = (first_deleted_slot != -1) ? first_deleted_slot : index;

			if (ht->table[insert_idx].state == DELETED) {
				ht->deleted_count--;  // Decrement when reusing deleted slot
			}

			ht->table[insert_idx].key = my_strdup(key);
			ht->table[insert_idx].state = OCCUPIED;
			ht->count++;
			printf("Inserted '%s' by index %d\n", key, insert_idx);
			return 0;
		}
		else if (ht->table[index].state == DELETED) {
			if (first_deleted_slot == -1) {
				first_deleted_slot = index;
			}
		}
		else if (ht->table[index].state == OCCUPIED) {
			if (strcmp(ht->table[index].key, key) == 0) {
				printf("The key '%s' already exists at the %d index. Insertion is not required.\n", key, index);
				return 1; // Ключ уже существует
			}
		}
		i++;
	}

	fprintf(stderr, "Error: The hash table is full or the sequence of samples could not find a place for '%s'.\n", key);
	return -1;
}


const char* search(HashTable* ht, const char* key) {
	if (!ht || !key) return NULL;

	unsigned int initial_hash = hash_string(key, ht->size);
	int index;
	int i = 0;

	while (i < ht->size) {
		index = (initial_hash + (unsigned long long)i * i) % ht->size;

		if (ht->table[index].state == EMPTY) {
			printf("The key '%s' was not found (an empty slot was found).\n", key);
			return NULL;
		}
		else if (ht->table[index].state == OCCUPIED) {
			if (strcmp(ht->table[index].key, key) == 0) {
				printf("The key '%s' was found by the index %d.\n", key, index);
				return ht->table[index].key;
			}
		}
		i++;
	}

	printf("The key '%s' was not found (all possible locations have been checked).\n", key);
	return NULL;
}


int delete_key(HashTable* ht, const char* key) {
	if (!ht || !key) {
		fprintf(stderr, "Error: Hash table or NULL key when deleting.\n");
		return -1;
	}
	if (ht->count == 0 && ht->deleted_count == 0) {
		printf("Table is empty, cannot delete '%s'.\n", key);
		return -1;
	}

	unsigned int initial_hash = hash_string(key, ht->size);
	int index;
	int i = 0;

	while (i < ht->size) {
		index = (initial_hash + (unsigned long long)i * i) % ht->size;

		if (ht->table[index].state == EMPTY) {
			printf("The key '%s' was not found for deletion (an empty slot was found).\n", key);
			return -1;
		}
		else if (ht->table[index].state == OCCUPIED) {
			if (strcmp(ht->table[index].key, key) == 0) {
				free(ht->table[index].key);
				ht->table[index].key = NULL;
				ht->table[index].state = DELETED;
				ht->count--;
				ht->deleted_count++;
				printf("The key '%s' has been removed from the %d index.\n", key, index);
				return 0;
			}
		}
		i++;
	}
	printf("The key '%s' was not found for deletion (all possible locations have been checked).\n", key);
	return -1;
}


static int rehash(HashTable* ht) {
	if (!ht) {
		fprintf(stderr, "Error: NULL hash table during rehashing.\n");
		return -1;
	}

	int old_size = ht->size;
	HashTableEntry* old_table = ht->table;

	// Calculate new size (next prime after doubling)
	int new_size = get_next_prime(old_size * 2);
	if (new_size <= old_size) {
		fprintf(stderr, "Error: Couldn't find larger prime size.\n");
		return -1;
	}

	// Create new table
	HashTableEntry* new_table = malloc(sizeof(HashTableEntry) * new_size);
	if (!new_table) {
		perror("Error allocating new table");
		return -1;
	}

	// Initialize new table
	for (int i = 0; i < new_size; i++) {
		new_table[i].key = NULL;
		new_table[i].state = EMPTY;
	}

	// Temporarily swap tables
	ht->table = new_table;
	int old_count = ht->count;
	ht->count = 0;
	ht->size = new_size;
	ht->deleted_count = 0;

	printf("Rehashing from %d to %d...\n", old_size, new_size);

	// Reinsert all active elements
	for (int i = 0; i < old_size; i++) {
		if (old_table[i].state == OCCUPIED) {
			if (insert(ht, old_table[i].key) != 0) {
				// Reinsert failed - restore old table
				free(new_table);
				ht->table = old_table;
				ht->size = old_size;
				ht->count = old_count;
				fprintf(stderr, "Error: Failed to reinsert key '%s'\n", old_table[i].key);
				return -1;
			}
			free(old_table[i].key); // Free old key
		}
	}
	ht->deleted_count = 0;

	free(old_table);
	printf("Rehash complete. New size: %d, elements: %d\n", ht->size, ht->count);
	return 0;
}


void print_table(const HashTable* ht) {
	if (!ht) return;

	printf("\n--- Hash Table State ---\n");
	printf("Size: %d, Active elements: %d, Deleted elements: %d\n", ht->size, ht->count, ht->deleted_count);
	printf("Current load factor: %.2f (Threshhold: %.2f)\n", (double)(ht->count + ht->deleted_count) / ht->size, ht->load_factor_threshold);
	for (int i = 0; i < ht->size; i++) {
		printf("[%d]: ", i);
		if (ht->table[i].state == EMPTY) {
			printf("EMPTY\n");
		}
		else if (ht->table[i].state == OCCUPIED) {
			printf("OCCUPIED - '%s'\n", ht->table[i].key);
		}
		else if (ht->table[i].state == DELETED) {
			printf("DELETED\n");
		}
	}
	printf("-----------------------------\n\n");
}


int get_hash_table_size(const HashTable* ht) {
	return ht->size;
}


int get_hash_table_count(const HashTable* ht) {
	return ht->count;
}


int get_hash_table_deleted_count(const HashTable* ht) {
	return ht->deleted_count;
}