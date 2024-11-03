#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <memory.h>


typedef struct item {
	char* key;
	int value;
} item;

// Структура хеш-таблицы
typedef struct HashMap {
	size_t size;
	item** items;

	size_t keys_size;
	char** keys;

	uint16_t mod;
} HashMap;

HashMap* CreateHashMap(uint16_t mod); // Функция создания хеш-таблицы
void AddItem(HashMap* hm, char* key, int value); // Функция добавления записы в хеш-таблицу
int GetValue(HashMap* hm, char* key); // Получаение значения по ключю
char* GetKeyByValue(HashMap* hm, int value); // Функция получения ключа по значению (просто перебирает все ключи пока не найдет нужный)
char** GetKeys(HashMap* hm); // Фунция получения списка всех ключей из хеш-таблицы

int cmp_str(char* s1, char* s2); // Функция сравнения строк