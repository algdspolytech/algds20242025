#include "pch.h"
#include <gtest/gtest.h>
#include "grid.h"

using namespace std;

static vector<vector<int>> grid;
static vector<vector<int>> visited;
static int m_size, n_size;
static vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void initialize_grid(int m, int n) {
    m_size = m;
    n_size = n;
    grid.assign(m, vector<int>(n, 0));
}

void remove_cell(int x, int y) {
    if (x >= 0 && x < m_size && y >= 0 && y < n_size) {
        grid[x][y] = 1;
    }
}

TEST(GridTests, IsAvailableTest) {
    initialize_grid(5, 5);
    ASSERT_EQ(isAvailable(2, 2), 1);
    remove_cell(2, 2);
    ASSERT_EQ(isAvailable(2, 2), 0);
}

TEST(GridTests, DFS_SingleComponent) {
    initialize_grid(5, 5);
    DFS(0, 0);
    ASSERT_EQ(visited[4][4], 1);
}

TEST(GridTests, DFS_Disconnected) {
    initialize_grid(5, 5);
    remove_cell(2, 2);
    DFS(0, 0);
    ASSERT_EQ(visited[2][2], 0);
}

TEST(GridTests, EmptyGridTest) {
    initialize_grid(5, 5);
    ASSERT_EQ(countDisconnectedAreas(), 1);
}

TEST(GridTests, FullGridTest) {
    initialize_grid(5, 5);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            remove_cell(i, j);
    ASSERT_EQ(countDisconnectedAreas(), 0);
}

TEST(GridTests, SingleCellRemoved) {
    initialize_grid(5, 5);
    remove_cell(2, 2);
    ASSERT_EQ(countDisconnectedAreas(), 1);
}

TEST(GridTests, MultipleCellsRemoved) {
    initialize_grid(5, 5);
    remove_cell(0, 0);
    remove_cell(4, 4);
    ASSERT_EQ(countDisconnectedAreas(), 2);
}

TEST(GridTests, HorizontalWall) {
    initialize_grid(5, 5);
    for (int i = 0; i < 5; i++)
        remove_cell(2, i);
    ASSERT_EQ(countDisconnectedAreas(), 2);
}

TEST(GridTests, VerticalWall) {
    initialize_grid(5, 5);
    for (int i = 0; i < 5; i++)
        remove_cell(i, 2);
    ASSERT_EQ(countDisconnectedAreas(), 2);
}

TEST(GridTests, ComplexShape) {
    initialize_grid(5, 5);
    remove_cell(1, 1);
    remove_cell(1, 2);
    remove_cell(2, 1);
    remove_cell(3, 3);
    remove_cell(3, 4);
    remove_cell(4, 3);
    ASSERT_EQ(countDisconnectedAreas(), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}