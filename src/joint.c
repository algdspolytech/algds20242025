#include "join.h"


static unsigned int countLen(List* list)
{
    List* ptr = list;
    unsigned int res = 0;
    while (ptr != 0)
    {
        res += ptr->len;
        ptr = ptr->next;
    }
    return res;
}



char* join(List* list)
{
    unsigned int len = countLen(list);
    char* str = (char*)malloc(len + 1);
    int pos = 0;
    List* ptr = list;
    while (ptr != 0)
    {
        memcpy((str + pos), ptr->str, ptr->len);
        pos += ptr->len;
        ptr = ptr->next;
    }
    str[pos] = '\0';
    return str;
}
