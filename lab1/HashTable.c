#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

//хеш-функция
int HashFunc(char* element, int table_size) {
	int index = 0;
	int i = 0;
	while (element[i] != '\0') {
		index += element[i];
		i++;
	}
	index %= table_size;
	return index;
}

//создание пустой хеш-таблицы размера size
HashTable_t CreateTable(int size) {
	char** data = (char**)malloc(size * sizeof(char*));
	for (int i = 0; i < size; i++) {
		data[i] = NULL;
	}
	HashTable_t table = { data, size };
	return table;
}

//attempt-ый индекс из квадратичной последовательности проб с начальным индексом start_index
int QuadraticProbing(int start_index, int table_size, int attempt) {
	int index = (start_index + attempt * attempt) % table_size;
	return index;
}

//проверка строк на равенство
int AreEqual(char* c1, char* c2) {
	if (c1 == NULL || c2 == NULL) {
		if (c1 == NULL && c2 == NULL) {
			return 1;
		}
		else {
			return 0;
		}
	}
	int i = 0;
	while (c1[i] != '\0' && c2[i] != '\0') {
		if (c1[i] != c2[i]) {
			return 0;
		}
		i++;
	}
	if (c1[i] == c2[i]) {
		return 1;
	}
	else {
		return 0;
	}
}

//длина строки
int Len(char* c) {
	if (c == NULL) {
		return 0;
	}
	int i = 0;
	while (c[i] != '\0') {
		i++;
	}
	return i;
}

//поиск элемента в хеш-таблице
int Find(char* element, HashTable_t table) {
	int index = HashFunc(element, table.size);
	int start_index = index;
	int attempt = 1;
	while (AreEqual(element, table.data[index]) == 0 && attempt < table.size) {
		index = QuadraticProbing(start_index, table.size, attempt);
		attempt++;
	}
	if (attempt = table.size && AreEqual(element, table.data[index]) == 0) {
		printf("find: element not found!\n");
		return -1;
	}
	else {
		return index;
	}
}

//добавление элемента в хеш-таблицу
void Insert(char* element, HashTable_t table) {
	int index = HashFunc(element, table.size);
	int start_index = index;
	int attempt = 1;
	while (table.data[index] != NULL && attempt < table.size) {
		index = QuadraticProbing(start_index, table.size, attempt);
		attempt++;
	}
	if (attempt = table.size && table.data[index] != NULL) {
		printf("insert: error! no space for element!\n");
	}
	else {
		int len = Len(element) + 1;
		table.data[index] = (char*)malloc(len * sizeof(char));
		for (int i = 0; i < len; i++) {
			table.data[index][i] = element[i];
		}
	}
}

//удаление элемента из хеш-таблицы
void Delete(char* element, HashTable_t table) {
	int index = Find(element, table);
	if (index == -1) {
		printf("delete: no such element in table!\n");
	}
	else {
		free(table.data[index]);
		table.data[index] = NULL;
	}
}