#include <stdio.h>
#include <list.h>
#include <list.h>


int main(int argc, char* argv)
{
    List* list = initList();
    addToList(list, "AsjdfhjashdjasjkdhaS");
    addToList(list, "AsjdfhjashdjasjkdhaS");
    addToList(list, "AsjdfhjashdjasjkdhaS");
    printList(list);
    char* str = join(list);
    printf(str);
    free(str);
    deleteList(list);
    return 0;
}