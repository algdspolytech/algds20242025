#include <gtest/gtest.h>

extern "C"
{
    #include "join.h"
    #include "list.h"
}

TEST(join_check, hello_world)
{
    List* list = initList();
    addToList(list, "Hello ");
    addToList(list, "World!");
    char exp[] = "Hello World!";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}