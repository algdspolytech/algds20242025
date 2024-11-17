#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "xorlist.h"



int StrLength(char* strptr) // возвращает длину строки
{ 
    if (strptr == NULL)
    {
        return 0;
    }
    int i = 0;
    for (; strptr[i] != '\0'; i++) 
    {
    };
    return i;
}

int StrEqual(char* strptr1, char* strptr2) // возвращает единицу, если строки равны, иначе ноль
{ 
    if (strptr1 == NULL || strptr2 == NULL)
    {
        return NULL;
    }
    int len = StrLength(strptr1);
    if (len != StrLength(strptr2))
    {
        return 0;
    }
    for (int i = 0; i < len; i++) 
    {
        if (strptr1[i] != strptr2[i])
        {
            return 0;
        }
    }
    return 1;
}

void CopyStr(char* res, char* orig, int len) // копирует строки
{
    if (orig == NULL) 
    {
        res = NULL;
    }
    else 
    {
        for (int i = StrLength(orig) - len; i < len; i++)
        {
            res[i] = orig[i];
        }
        res[len] = '\0';
    }
}

elem_t* OpXor(elem_t* a, elem_t* b) // выполняет побитовое исключающее или с адресами элементов
{
    if (a == NULL) 
    {
        return b;
    }
    else if (b == NULL) 
    {
        return a;
    }
    else 
    {
        return (elem_t*)((uintptr_t)a^(uintptr_t)b);
    }


}

elem_t* ListElem(list_t* list, int num) // возвращает адрес i-го элемента списка (NULL, если элемент не существует)
{
    elem_t* cur = list->Plist;
    elem_t* prev = NULL;
    elem_t* next = NULL;
    if (num == 0) 
    {
        return cur;
    }
    else if (num < 0 || num > list->size-1|| cur == NULL)
    {
        return next;
    }
    for (; num > 0; num--) 
    {
        if (cur == NULL)
        {
            return NULL;
        }
        next = OpXor(prev, cur-> xor);
        prev = cur;
        cur = next;
    }
    return cur;
}

elem_t* CreateElem(char* string) // создает элемент 
{
    int len = StrLength(string);
    if (len > 0)
    {
        elem_t* new = malloc(sizeof(elem_t));
        (*new).str = malloc(len + 1);
        CopyStr((*new).str, string, len);
        (*new). xor;
        return new;
    }
    return NULL;
}

list_t* ListCreate(char* string) // создает список
{
    elem_t* first = CreateElem(string);
    list_t* list = malloc(sizeof(list_t));

    if (list && string != NULL) 
    {
        list->Plist = first;
        list->size = 1;
        return list;
    }

    free(list);

    return NULL;
}

void ListAdd(list_t* list, char* string) // добавляет элемент в список
{
    if (string == NULL)
        return NULL;
    elem_t* new = CreateElem(string);
    int size = ++list->size;
    elem_t* last = ListElem(list, size-2);
    elem_t* prelast = last-> xor;
    new -> xor = last;
    if (last != list->Plist)
    {
        last -> xor = OpXor(new, prelast);
    }
    else
    {
        last -> xor = new;
    }
}
elem_t* FindElem(list_t* list, char* string, int* pindex) // находит элемент с данной строкой
{
    elem_t* cur = list->Plist;
    elem_t* prev = NULL;
    elem_t* buff = NULL;
    for (int i = 0; i < list->size; i++)
    {
        if (StrEqual(string, cur->str)) 
        {
            if (pindex != NULL) *pindex = i;
            return cur;
        }
        buff = cur;
        cur = OpXor(prev, cur-> xor);
        prev = buff;
    }
    return NULL;
}

void RejoinElem(list_t* list, int index) // соединяет два элемента, элемент между которыми будет удален
{
    elem_t* pprev=ListElem(list, index - 2);
    elem_t* prev = ListElem(list, index - 1);
    elem_t* next = ListElem(list, index + 1);
    elem_t* nnext = ListElem(list, index + 2);
    if (prev != NULL) 
    {
        prev-> xor = OpXor(pprev, next);
    }
    if (next != NULL) 
    {
        next-> xor = OpXor(prev, nnext);
    }
}

void DeleteElem(list_t* list, char* string, int delindex) // удаляет элемент по номеру или по строке
{
    int index = -1;
    elem_t* del = NULL;
    if (string == NULL && delindex == NULL) 
    {
        return NULL;
    }
    if (delindex == NULL) 
    {
        del = FindElem(list, string, &index);
    }
    if (string == NULL) 
    {
        index = delindex;
        del = ListElem(list,index);
    }
    if (del != NULL) 
    {
        RejoinElem(list, index);
        if (index == 0) 
        {
            list->Plist = list->Plist-> xor;
        }
        free(del->str);
        free(del);
        if (--list->size == 0)
        {
            free(list);
        }
    }
    return NULL;
}


void PrintList(list_t* list) // печатает список
{
    elem_t* cur = list->Plist;
    elem_t* prev = NULL;
    elem_t* buff = NULL;
    for (int i = 0; i < list->size; i++)
    {
        printf("%s %p\n", cur->str,(char*) cur-> xor);
        buff = cur;
        cur = OpXor(cur->xor, prev);
        prev = buff;
    }
}
