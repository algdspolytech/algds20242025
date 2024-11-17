#pragma once
#define sizeofadd sizeof(char*)

struct eeelem {
    char* str;
    struct eeelem* xor;
};
typedef struct eeelem elem_t;

struct lllist {
    int size;
    elem_t* Plist;
};
typedef struct lllist list_t;

int StrLength(char* strptr);// возвращает длину строки

int StrEqual(char* strptr1, char* strptr2);// возвращает единицу, если строки равны, иначе ноль

void CopyStr(char* res, char* orig, int len);// копирует строки

elem_t* OpXor(elem_t* a, elem_t* b); // выполняет побитовое исключающее или с адресами элементов

elem_t* ListElem(list_t* list, int num); // возвращает адрес i-го элемента списка (NULL, если элемент не существует)

elem_t* CreateElem(char* string); // создает элемент 

list_t* ListCreate(char* string);// создает список

void ListAdd(list_t* list, char* string); // добавляет элемент в список

elem_t* FindElem(list_t* list, char* string, int* pindex); // находит элемент с данной строкой

void RejoinElem(list_t* list, int index); // соединяет два элемента, элемент между которыми будет удален

void DeleteElem(list_t* list, char* string, int delindex); // удаляет элемент по номеру или по строке

void PrintList(list_t* list); // печатает список
