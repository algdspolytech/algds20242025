#include "list.h"

int StringComparison(const char *first, const char *second) // returns 1 if first > second, otherwise returns 0;
{
    unsigned int i = 0;
    while (first[i] == second[i] && first[i] != '\0')
    {
        ++i;
    }
    return first[i] > second[i] ? 1 : 0;
}

void ListAdd(list **first, char *string)
{
    if (*first)
    {
        while ((*first)->next != NULL)
        {
            *first = (*first)->next;
        }
        list *addition = (list *)malloc(sizeof(list));
        addition->next = NULL;
        addition->str = string;
        (*first)->next = addition;
    }
    else
    {
        *first = (list *)malloc(sizeof(list));
        (*first)->next = NULL;
        (*first)->str = string;
    }
}

void ListDestr(list **first)
{
    while (*first)
    {
        list *tmp = *first;
        *first = (*first)->next;
        free(tmp->str);
        free(tmp);
    }
}

void ListSort(list *first)
{
    if (first)
    {
        list *copy = first;
        int len = 0;
        while (copy->next != NULL)
        {
            ++len;
            copy = copy->next;
        }
        for (int i = 0; i < len; ++i)
        {
            copy = first;
            while (copy->next != NULL)
            {
                if (StringComparison(copy->str, copy->next->str))
                {
                    char *tmp = copy->str;
                    copy->str = copy->next->str;
                    copy->next->str = tmp;
                }
                copy = copy->next;
            }
        }
    }
}

list *ListFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char c = '0';
    int len = 0;
    list *first = NULL;
    while (c != EOF)
    {
        int strlen = 0;
        do
        {
            c = getc(file);
            ++strlen;
        } while (c != '\n' && c != EOF);
        fseek(file, len, SEEK_SET);
        char *string = (char *)malloc(sizeof(char) * strlen + 1);
        fgets(string, strlen, file);
        string[strlen] = '\0';
        if (!first)
        {
            first = (list *)malloc(sizeof(list));
            first->next = NULL;
            first->str = string;
        }
        else
        {
            ListAdd(&first, string);
        }
        len += ++strlen;
        c = getc(file);
    }
    return first;
}