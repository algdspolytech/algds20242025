#include "UnitTests.h"
#include "list.h"

// Test: StringComparison when first > second
int Test_StringComparison_no1(void)
{
    const char *first = "abc";
    const char *second = "abc";
    int res = StringComparison(first, second);
    int status = 1;

    status *= ASSERT_INT_EQ(0, res, "res must be 0", "Test_StringComparison_no1");

    testing_result(status, "Test_StringComparison_no1");
    return status;
}

// Test: StringComparison when first <= second
int Test_StringComparison_no2(void)
{
    const char *first = "abd";
    const char *second = "abc";
    int res = StringComparison(first, second);
    int status = 1;

    status *= ASSERT_INT_EQ(1, res, "res must be 1", "Test_StringComparison_no2");

    testing_result(status, "Test_StringComparison_no2");
    return status;
}

// Test: ListAdd to empty list
int Test_AddToEmptyList_no3(void)
{
    list *tmp = NULL;
    ListAdd(&tmp, "abc");
    int status = 1;

    status *= ASSERT_PTR_NE(NULL, tmp, "tmp must be !NULL", "Test_AddToEmptyList_no3");
    status *= ASSERT_PTR_EQ(NULL, tmp->next, "tmp->next must be NULL", "Test_AddToEmptyList_no3");
    status *= ASSERT_STR_EQ("abc", tmp->str, "tmp->str must be abc", "Test_AddToEmptyList_no3");

    testing_result(status, "Test_AddToEmptyList_no3");
    return status;
}

int Test_AddToNotEmptyList_no4(void)
{
    list *tmp = (list *)malloc(sizeof(list));
    tmp->str = "abc";
    tmp->next = NULL;
    ListAdd(&tmp, "def");
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp->next->next, "tmp->next->next must be NULL", "Test_AddToNotEmptyList_no4");
    status *= ASSERT_STR_EQ("abc", tmp->str, "tmp->str must be abc", "Test_AddToNotEmptyList_no4");
    status *= ASSERT_STR_EQ("def", tmp->next->str, "tmp->next->str must be def", "Test_AddToNotEmptyList_no4");

    testing_result(status, "Test_AddToEmptyList_no4");
    return status;
}

int Test_ListDestr_no5(void)
{
    list *tmp = (list *)malloc(sizeof(list));
    tmp->str = "abc";
    tmp->next = NULL;
    ListDestr(&tmp);
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp, "tmp must be NULL", "Test_ListDestr_no5");

    testing_result(status, "Test_ListDestr_no5");
    return status;
}

int Test_SortOnEmptyList_no6(void)
{
    list *tmp = NULL;
    ListSort(tmp);
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp, "tmp must be NULL", "Test_SortOnEmptyList_no6");

    testing_result(status, "Test_SortOnEmptyList_no6");
    return status;
}

int Test_SortOnSingleElement_no7(void)
{
    list *tmp = (list *)malloc(sizeof(list));
    tmp->str = "abc";
    tmp->next = NULL;
    ListSort(tmp);
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp->next, "tmp->next must be NULL", "Test_SortOnSingleElement_no7");
    status *= ASSERT_STR_EQ("abc", tmp->str, "tmp->str must be abc", "Test_SortOnSingleElement_no7");

    ListDestr(&tmp);
    testing_result(status, "Test_SortOnSingleElement_no7");
    return status;
}

int Test_SortOnNormalList_no8(void)
{
    list *tmp = (list *)malloc(sizeof(list));
    tmp->str = "abd";
    tmp->next = (list *)malloc(sizeof(list));
    tmp->next->next = NULL;
    tmp->next->str = "abc";
    ListSort(tmp);
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp->next->next, "tmp->next->next must be NULL", "Test_SortOnNormalList_no8");
    status *= ASSERT_STR_EQ("abc", tmp->str, "tmp->str must be abc", "Test_SortOnNormalList_no8");
    status *= ASSERT_STR_EQ("abd", tmp->next->str, "tmp->next->str must be abd", "Test_SortOnNormalList_no8");

    ListDestr(&tmp);
    testing_result(status, "Test_SortOnNormalList_no8");
    return status;
}

int Test_ListFromEmptyFile_no9(void)
{
    list *tmp = ListFromFile("test9.txt");
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp->next, "tmp->next must be NULL", "Test_SortOnSingleElement_no7");
    status *= ASSERT_STR_EQ("", tmp->str, "tmp->str must be empty string", "Test_SortOnSingleElement_no7");

    ListDestr(&tmp);
    testing_result(status, "Test_ListFromEmptyFile_no9");
    return status;
}

int Test_ListFromNonEmptyFile_no10(void)
{
    list *tmp = ListFromFile("test10.txt");
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, tmp->next->next, "tmp->next->next must be NULL", "ListFromNonEmptyFile_no10");
    status *= ASSERT_STR_EQ("abc", tmp->str, "tmp->str must be abc", "ListFromNonEmptyFile_no104");
    status *= ASSERT_STR_EQ("def", tmp->next->str, "tmp->next->str must be def", "ListFromNonEmptyFile_no10");

    ListDestr(&tmp);
    testing_result(status, "ListFromNonEmptyFile_no10");
    return status;
}

int main(void)
{
    int status = 1;
    status *= Test_StringComparison_no1();
    status *= Test_StringComparison_no2();
    status *= Test_AddToEmptyList_no3();
    status *= Test_AddToNotEmptyList_no4();
    status *= Test_ListDestr_no5();
    status *= Test_SortOnEmptyList_no6();
    status *= Test_SortOnSingleElement_no7();
    status *= Test_SortOnNormalList_no8();
    status *= Test_ListFromEmptyFile_no9();
    status *= Test_ListFromNonEmptyFile_no10();

    testing_result(status, "Total_Tests");

    return 0;
}