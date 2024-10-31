#include <cstddef>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <graph.c>
#include <gtest/gtest.h>

TEST(nodeTest, initNodeNullCountVertReturnsNull_no1) {
    int* vertices=(int*)malloc(1*sizeof(int));
    vertices[0]=1;
    EXPECT_EQ(initNode(1,0,vertices),nullptr);
}

TEST(nodeTest, initNodeEmptyArrayReturnsNull_no2) {
    EXPECT_EQ(initNode(1,2,NULL),nullptr);
}
