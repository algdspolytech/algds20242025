#include "gtest/gtest.h"

extern "C"
{
    #include "list.h"
}

TEST(join_check, add_one)
{
    List* list = initList();
    ASSERT_EQ(addToList(list, "AsjdfhjashdjasjkdhaS"), 1);
}

TEST(join_check, add_second)
{
    List* list = initList();
    addToList(list, "AsjdfhjashdjasjkdhaS");
    ASSERT_EQ(addToList(list, "AsjdfhjashdjasjkdhaS"), 1);
}

TEST(join_check, add_many)
{
    List* list = initList();
    ASSERT_EQ(addToList(list, "Hello"), 1);
    ASSERT_EQ(addToList(list, "beautiful"), 1);
    ASSERT_EQ(addToList(list, "world!"), 1);
}

TEST(join_check, len_correct)
{
    List* list = initList();
    char elem[] = "Hello";
    addToList(list, elem);
    ASSERT_EQ(list->len == 5, true);
}

TEST(join_check, add_equal)
{
    List* list = initList();
    ASSERT_EQ(addToList(list, "duplicate"), 1);
    ASSERT_EQ(addToList(list, "duplicate"), 1);

}