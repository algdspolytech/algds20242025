#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum {
	EMPTY,
	OCCUPIED,
	DELETED
} SlotState;


typedef struct {
	char* key;
	SlotState state;
} HashTableEntry;


typedef struct {
	HashTableEntry* table;
	int size;
	int count;
	int deleted_count;
	double load_factor_threshold;
} HashTable;

bool is_prime(int n);

int get_next_prime(int n);

HashTable* create_table(int initial_size, double load_factor_threshold);

void destroy_table(HashTable* ht);

int insert(HashTable* ht, const char* key);

const char* search(HashTable* ht, const char* key);  

int delete_key(HashTable* ht, const char* key);

static int rehash(HashTable* ht);

void print_table(const HashTable* ht);

int get_hash_table_size(const HashTable* ht);

int get_hash_table_count(const HashTable* ht);

int get_hash_table_deleted_count(const HashTable* ht);