#include <gtest/gtest.h>

extern "C"
{
    #include "matrix.h"
}


TEST(matrix_check, normal_case_n1)
{
    std::cout << ReadFile("../matrix.txt");
    ASSERT_EQ(1, 1);
}
