#include "pch.h"  
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

extern "C" {
#include "C:\Users\marse\OneDrive\Рабочий стол\c\Project2\Project2\Source.h"  
}

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        num = 0;
        memset(matrix, 0, sizeof(matrix));
        memset(visited, 0, sizeof(visited));
    }
    void TearDown() override {
    }
};

TEST_F(GraphTest, CorrectNum_ValidNum_no1) {
    num = 500;
    EXPECT_TRUE(CorrectNum(num));
}

TEST_F(GraphTest, CorrectNum_TooBigNum_no2) {
    num = MAX_TOPs + 1;
    EXPECT_FALSE(CorrectNum(num));
}

TEST_F(GraphTest, MatrixCheck_ValidValues_no3) {
    EXPECT_TRUE(MatrixCheck(0));
    EXPECT_TRUE(MatrixCheck(1));
}

TEST_F(GraphTest, MatrixCheck_InvalidValue_no4) {
    EXPECT_FALSE(MatrixCheck(-1));
    EXPECT_FALSE(MatrixCheck(2));
    EXPECT_FALSE(MatrixCheck(100));
}

TEST_F(GraphTest, TopCheck_ValidIndices_no5) {
    num = 5;
    EXPECT_TRUE(TopCheck(num, 0, 4));
    EXPECT_TRUE(TopCheck(num, 2, 3));
}

TEST_F(GraphTest, TopCheck_InvalidIndices_no6) {
    num = 5;
    EXPECT_FALSE(TopCheck(num, -1, 2));
    EXPECT_FALSE(TopCheck(num, 5, 0));
    EXPECT_FALSE(TopCheck(num, 3, 5));
}

TEST_F(GraphTest, DFS_NoEdges_no7) {
    num = 3;
    int testMatrix[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    memcpy(matrix, testMatrix, sizeof(testMatrix));
    memset(visited, 0, sizeof(visited));

    EXPECT_FALSE(DFS(0, 2));
}

TEST_F(GraphTest, DFS_SingleEdge_no8) {
    num = 2;
    int testMatrix[2][2] = {
        {0, 1},
        {1, 0}
    };
    memcpy(matrix, testMatrix, sizeof(testMatrix));
    memset(visited, 0, sizeof(visited));

    EXPECT_TRUE(DFS(0, 1));
}

TEST_F(GraphTest, DFS_CyclicGraph_no9) {
    num = 4;
    int testMatrix[4][4] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };
    memcpy(matrix, testMatrix, sizeof(testMatrix));
    memset(visited, 0, sizeof(visited));

    EXPECT_TRUE(DFS(0, 3));
}

TEST_F(GraphTest, DFS_IsolatedVertex_no10) {
    num = 4;
    int testMatrix[4][4] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0} 
    };
    memcpy(matrix, testMatrix, sizeof(testMatrix));
    memset(visited, 0, sizeof(visited));

    EXPECT_FALSE(DFS(0, 3));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}