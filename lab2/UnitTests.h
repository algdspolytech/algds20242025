#pragma once
#include "stdio.h"

int ASSERT_INT_EQ(int expected, int actual, const char* message, char* test_name);
int ASSERT_INT_NE(int expected, int actual, const char *message, char *test_name);
int ASSERT_STR_EQ(const char *expected, const char *actual, const char *message, const char *test_name);
int ASSERT_STR_NE(const char *expected, const char *actual, const char *message, const char *test_name);
int ASSERT_PTR_EQ(void *expected, void *actual, const char *message, char *test_name);
int ASSERT_PTR_NE(void *expected, void *actual, const char *message, char *test_name);

void testing_result(int status, const char* test_name);