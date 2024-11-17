#include <gtest/gtest.h>

extern "C"
{
    #include "queen.h"
}


TEST(NQueens, normal_case_n1)
{
    char* res = solveNQueens(4);
    ASSERT_EQ(strcmp(res, "0 2\n1 0\n2 3\n3 1\n"), 0);
    
}

TEST(NQueens, wrong_input_n2)
{
    char* res = solveNQueens(0);
    ASSERT_EQ(res == NULL, 1);
    delete res;
}

TEST(NQueens, one_solution_n3)
{
    char* res = solveNQueens(1);
    ASSERT_EQ(strcmp(res, "0 0\n"), 0);
    delete res;
}

TEST(NQueens, wrong_input_n4)
{
    char* res = solveNQueens(20);
    ASSERT_EQ(res == NULL, 1);
    delete res;
}

TEST(NQueens, no_sollutions_n5)
{
    char* res = solveNQueens(2);
    ASSERT_EQ(res[0] == 'g', 1);
    delete res;
}

TEST(NQueens, normal_case_n6)
{
    char* res = solveNQueens(5);
    ASSERT_EQ(strcmp(res, "0 4\n1 2\n2 0\n3 3\n4 1\n"), 0);
    delete res;
}

TEST(NQueens, normal_case_n7)
{
    char* res = solveNQueens(6);
    ASSERT_EQ(strcmp(res, "0 4\n1 2\n2 0\n3 5\n4 3\n5 1\n"), 0);
    delete res;
}

TEST(NQueens, normal_case_n8)
{
    char* res = solveNQueens(7);
    ASSERT_EQ(strcmp(res, "0 6\n1 4\n2 2\n3 0\n4 5\n5 3\n6 1\n"), 0);
    delete res;
}


TEST(NQueens, wrong_input_n9)
{
    char* res = solveNQueens(-1);
    ASSERT_EQ(res == NULL, 1);
    delete res;
}

TEST(NQueens, deep_recurtion_n10)
{
    char* res = solveNQueens(11);
    ASSERT_EQ(1, 1);
    delete res;
}
