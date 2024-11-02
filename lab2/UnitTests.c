#include "UnitTests.h"

int ASSERT_INT_EQ(int expected, int actual, const char *message, char *test_name)
{
    if (expected != actual)
    {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
    }
    return expected == actual;
}

int ASSERT_INT_NE(int expected, int actual, const char *message, char *test_name)
{
    if (expected == actual)
    {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
    }
    return expected != actual;
}

int ASSERT_STR_EQ(const char *expected, const char *actual, const char *message, const char *test_name)
{
    unsigned int i = 0;
    while (expected[i] == actual[i] && expected[i] != '\0')
    {
        ++i;
    }
    if (expected[i] != actual[i])
    {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
    }
    return expected[i] == actual[i];
}

int ASSERT_STR_NE(const char *expected, const char *actual, const char *message, const char *test_name)
{
    unsigned int i = 0;
    while (expected[i] == actual[i] && expected[i] != '\0')
    {
        ++i;
    }
    if (expected[i] == actual[i])
    {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
    }
    return expected[i] != actual[i];
}

int ASSERT_PTR_EQ(void *expected, void *actual, const char *message, char *test_name)
{
    if (expected != actual)
    {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %p, Actual: %p\n", expected, actual);
    }
    return expected == actual;
}

int ASSERT_PTR_NE(void *expected, void *actual, const char *message, char *test_name)
{
    if (expected == actual)
    {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %p, Actual: %p\n", expected, actual);
    }
    return expected != actual;
}

void testing_result(int status, const char* test_name)
{
    if(status)
    {
        printf("%s - Success\n", test_name);
    }
    else
    {
        printf("%s - Failure\n", test_name);
    }
}