#include "gtest/gtest.h"

extern "C"
{
    #include "list.h"
}

TEST(join_check, ok)
{
    List* list = initList();
    ASSERT_EQ(addToList(list, "AsjdfhjashdjasjkdhaS"), 1);
    }