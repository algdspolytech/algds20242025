#include <gtest/gtest.h>

extern "C"
{
    #include "join.h"
    #include "list.h"
}


TEST(join_check, normal_case_n1)
{
    List* list = initList();
    addToList(list, "What");
    addToList(list, " a");
    addToList(list, " beautiful");
    addToList(list, " world!");
    char* res = join(list);
    char exp[] = "What a beautiful world!";
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, eq_strings_n2)
{
    List* list = initList();
    addToList(list, "Hello ");
    addToList(list, "Hello ");
    char exp[] = "Hello Hello ";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, empty_list_n3)
{
    List* list = initList();
    char exp[] = "";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, one_string_n4)
{
    List* list = initList();
    addToList(list, "Hello");
    char exp[] = "Hello";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, empty_string_n5)
{
    List* list = initList();
    addToList(list, "");
    char exp[] = "";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, empty_strings_n6)
{
    List* list = initList();
    addToList(list, "");
    addToList(list, "");
    char exp[] = "";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, special_symbols_n7)
{
    List* list = initList();
    addToList(list, "!@#$%^&*(){}|/~`");
    addToList(list, "!@#$%^&*(){}|/~`");
    char exp[] = "!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, different_lens_n8)
{
    List* list = initList();
    addToList(list, "Hello");
    addToList(list, " World!");
    char exp[] = "Hello World!";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, long_strings_n9)
{
    List* list = initList();
    addToList(list, "!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`");
    addToList(list, "!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`");
    char exp[] = "!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`!@#$%^&*(){}|/~`";
    char* res = join(list);
    ASSERT_EQ(strcmp(exp, res), 0);
}

TEST(join_check, many_strings_n10)
{
    List* list = initList();
    std::string exp1 = "";
    for(int i = 0; i < 100; ++i)
    {
         addToList(list, "Hello ");
         exp1 += "Hello ";
    }
    std::string res(join(list));
    ASSERT_EQ(res == exp1, true);
}