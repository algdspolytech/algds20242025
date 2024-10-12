#define _CRT_SECURE_NO_WARNINGS
#include "UnrolledLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

//Создание структуры типа ULList_t по значениям полей
ULList_t Create(int count, int* data, ULList_t* next) {
	ULList_t list;
	list.count = count;
	for (int i = 0; i < count; i++) {
		list.data[i] = data[i];
	}
	list.next = next;
	return list;
}

//Добавление элемента
void Add(ULList_t* list, int element) {
	while (list->count == N) {
		if (list->next == NULL) {
			ULList_t* newList = (ULList_t*)malloc(sizeof(ULList_t));
			newList->count = 0;
			newList->next = NULL;
			list->next = newList;
		}
		list = list->next;
	}
	list->data[list->count] = element;
	list->count++;
}

//Поиск номера элемента по ключу
int Index(ULList_t* list, int key) {
	int k = 0;
	do {
		for (int i = 0; i < list->count; i++) {
			if (list->data[i] == key) {
				return k + i;
			}
		}
		k += list->count;
		list = list->next;
	} while (list != NULL);
	printf("Index: element %d not found\n", key);
	return -1;
}

/*Вспомогательная функция - поиск блока, содержащего элемент с данным номером,
и его индекса внутри блока*/
ULList_t* Find(ULList_t* list, int index, int* ptr) {
	int k = 0;
	while (k + list->count <= index) {
		k += list->count;
		if (list->next == NULL) {
			printf("Index out of range\n");
			*ptr = -1;
			return NULL;
		}
		list = list->next;
	}
	*ptr = k;
	return list;
}

//Поиск элемента с заданным номером
Element_t Element(ULList_t* list, int index) {
	int k;
	list = Find(list, index, &k);
	if (list == NULL) {
		Element_t elem = { NULL, -1 };
		return elem;
	}
	Element_t elem = { list, index - k };
	return elem;
}

//Удаление элемента с заданным номером 
void Delete(ULList_t* list, int index) {
	int k;
	list = Find(list, index, &k);
	int i = index - k + 1;
	if (list != NULL) {
		for (i; i < list->count; i++) {
			list->data[i - 1] = list->data[i];
		}
		list->count--;
	}
}

//Подсчет количества элементов
int ElementCount(ULList_t* list) {
	int k = 0;
	do {
		k += list->count;
		list = list->next;
	} while (list != NULL);
	return k;
}

//Итерирование
Element_t Next(Element_t elem) {
	Element_t next;
	if (elem.index == (elem.list->count - 1)) {
		if (elem.list->next == NULL) {
			printf("Next element not found\n");
			next.list = NULL;
			next.index = -1;
			return next;
		}
		next.list = elem.list->next;
		next.index = 0;
	}
	else {
		next.list = elem.list;
		next.index = elem.index + 1;
	}
	return next;
}