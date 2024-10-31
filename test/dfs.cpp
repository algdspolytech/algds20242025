#include <gtest/gtest.h>

extern "C"
{
    #include "matrix.h"
    #include "method.h"
}


TEST(matrix_check, normal_case_n1)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n1.txt");
    int visited[2] = {0, 0};
    bool res = false;
    dfs(mat, 0, 1, visited, &res);
    ASSERT_EQ(true, res);
}


TEST(matrix_check, normal_case_n2)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n2.txt");
    int visited[2] = {0, 0};
    bool res = false;
    dfs(mat, 0, 1, visited, &res);
    ASSERT_EQ(false, res);
}


TEST(matrix_check, many_paths)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n3.txt");
    int visited[3] = {0, 0, 0};
    bool res = false;
    dfs(mat, 0, 2, visited, &res);
    ASSERT_EQ(true, res);
}


TEST(matrix_check, cyclic_graph)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n4.txt");
    int visited[3] = {0, 0, 0};
    bool res = false;
    dfs(mat, 0, 2, visited, &res);
    ASSERT_EQ(true, res);
}


TEST(matrix_check, no_paths)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n5.txt");
    int visited[3] = {0, 0, 0};
    bool res = false;
    dfs(mat, 0, 2, visited, &res);
    ASSERT_EQ(false, res);
}


TEST(matrix_check, long_path)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n6.txt");
    int visited[3] = {0, 0, 0};
    bool res = false;
    dfs(mat, 0, 2, visited, &res);
    ASSERT_EQ(true, res);
}


TEST(matrix_check, self_cycled)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n7.txt");
    int visited[2] = {0, 0};
    bool res = false;
    dfs(mat, 0, 1, visited, &res);
    ASSERT_EQ(true, res);
}


TEST(matrix_check, empty_graph)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n8.txt");
    int visited[2] = {0, 0};
    bool res = false;
    dfs(mat, 0, 1, visited, &res);
    ASSERT_EQ(false, res);
}



TEST(matrix_check, one_vertex)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n9.txt");
    int visited[2] = {0, 0};
    bool res = false;
    dfs(mat, 0, 0, visited, &res);
    ASSERT_EQ(true, res);
}


TEST(matrix_check, big_graph)
{
    matrix* mat = ReadFile("/home/egor/alg/algds20242025/tests_files/n10.txt");
    int visited[4] = {0, 0, 0, 0};
    bool res = false;
    dfs(mat, 0, 3, visited, &res);
    ASSERT_EQ(true, res);
}

