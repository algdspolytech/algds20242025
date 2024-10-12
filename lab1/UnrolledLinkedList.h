#pragma once
#define N 4

//Развернутый связный список

typedef struct List {
	int count; //количество заполненных ячеек массива
	int data[N]; //массив с данными
	struct List* next; //указатель на следующий блок
} ULList_t;

//Структура для хранения информации об элементе для быстрого доступа к нему

typedef struct {
	ULList_t* list; //указатель на блок, в котором содержится элемент
	int index; //индекс элемента внутри массива данных блока
} Element_t;

//Создание структуры типа ULList_t по значениям полей
ULList_t Create(int count, int* data, ULList_t* next); 

//Добавление элемента
void Add(ULList_t* list, int element);

//Поиск номера элемента по ключу
int Index(ULList_t* list, int key);

/*Вспомогательная функция - поиск блока, содержащего элемент с данным номером,
и его индекса внутри блока*/
ULList_t* Find(ULList_t* list, int index, int* ptr);

//Поиск элемента с заданным номером
Element_t Element(ULList_t* list, int index);

//Удаление элемента с заданным номером 
void Delete(ULList_t* list, int index);

//Подсчет количества элементов
int ElementCount(ULList_t* list);

//Итерирование
Element_t Next(Element_t elem);
