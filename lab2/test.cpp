#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../Algosi2/main.h"
}

TEST(CorrectNumOfPointCheckTest, LessThanOrEqualToMaxVertices_no1) {
    EXPECT_EQ(CorrectNumOfPointCheck(0), 1);
}
TEST(CorrectNumOfPointCheckTest, GreaterThanMaxVertices_no2) {
    EXPECT_EQ(CorrectNumOfPointCheck(1000), 0);
}

TEST(MatrixCheckTest, ValidInputs0_no3) { EXPECT_EQ(MatrixCheck(0), 1); }

TEST(MatrixCheckTest, ValidInputs1_no4) { EXPECT_EQ(MatrixCheck(1), 1); }

TEST(MatrixCheckTest, InvalidInputs_no5) { EXPECT_EQ(MatrixCheck(-1), 0); }

TEST(PointsCheckTest, TestValidVertices_no6) {
    EXPECT_EQ(PointsCheck(5, 0, 1), 1);
}

TEST(PointsCheckTest, TestInvalidU_no7) { EXPECT_EQ(PointsCheck(5, -1, 1), 0); }

TEST(PointsCheckTest, TestInvalidV_no8) { EXPECT_EQ(PointsCheck(5, 1, 5), 0); }

TEST(PointsCheckTest, TestBothInvalid_no9) {
    EXPECT_EQ(PointsCheck(5, -1, 5), 0);
}

class DFSTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < MAX_VERTICES; ++i) {
            visited[i] = 0;
        }
    }

    void TearDown() override {
        for (int i = 0; i < MAX_VERTICES; ++i) {
            for (int j = 0; j < MAX_VERTICES; ++j) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }
};

TEST_F(DFSTest, PathExists_no10) {
    numVertices = 5;

    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[1][2] = 1;
    adjacencyMatrix[2][3] = 1;
    adjacencyMatrix[3][4] = 1;

    EXPECT_EQ(dfs(0, 4), 1);
}

TEST_F(DFSTest, NoPathExists_no11) {
    numVertices = 5;

    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[1][2] = 1;

    EXPECT_EQ(dfs(0, 4), 0);
}

TEST_F(DFSTest, SelfLoop_no12) {
    numVertices = 3;

    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[1][0] = 1;
    adjacencyMatrix[1][2] = 1;

    EXPECT_EQ(dfs(1, 2), 1);
}

TEST_F(DFSTest, IsolatedVertex_no13) {
    numVertices = 4;

    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[1][0] = 1;
    adjacencyMatrix[0][2] = 1;

    EXPECT_EQ(dfs(0, 3), 0);
}

TEST_F(DFSTest, BacktrackingPathExists_no14) {
    numVertices = 6;

    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[1][2] = 1;
    adjacencyMatrix[2][3] = 1;
    adjacencyMatrix[1][4] = 1;
    adjacencyMatrix[4][5] = 1;

    EXPECT_EQ(dfs(0, 5), 1);
}

TEST_F(DFSTest, SameVertexPathExists_no15) { EXPECT_EQ(dfs(0, 0), 1); }