#pragma once

//хеш-таблица
typedef struct {
	char** data; //массив строк
	int size; //размер массива
} HashTable_t;

//хеш-функция
int HashFunc(char* element, int table_size);

//создание хеш-таблицы
HashTable_t CreateTable(int size);

//поиск элемента
int Find(char* element, HashTable_t table);

//добавление элемента
void Insert(char* element, HashTable_t table);

//удаление элемента
void Delete(char* element, HashTable_t table);
