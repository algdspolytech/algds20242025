
#include <gtest/gtest.h>
#include "sudoku.h"

// Тест чтения данных
TEST(SudokuTest, ReadInput) {
    std::string testFile = "test_input.txt";
    std::ofstream outFile(testFile);
    outFile << "3\n";
    outFile << "0 0 5 3 0 0 0 0 0\n";
    outFile << "8 0 0 0 0 0 0 2 0\n";
    outFile << "0 7 0 0 1 0 5 0 0\n";
    outFile << "4 0 0 0 0 5 3 0 0\n";
    outFile << "0 1 0 0 7 0 0 0 6\n";
    outFile << "0 0 3 2 0 0 0 8 0\n";
    outFile << "0 6 0 5 0 0 0 0 9\n";
    outFile << "0 0 4 0 0 0 0 3 0\n";
    outFile << "0 0 0 0 0 9 7 0 0\n";
    outFile.close();

    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE));
    readInput(testFile, grid);

    EXPECT_EQ(grid[0][2], 5);
    EXPECT_EQ(grid[1][0], 8);
    EXPECT_EQ(grid[8][8], 0);

    std::remove(testFile.c_str());
}

// Тест записи результатов
TEST(SudokuTest, WriteOutput) {
    std::string testFile = "test_output.txt";
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    grid[0][0] = 5;

    writeOutput(testFile, grid, true);

    std::ifstream inFile(testFile);
    ASSERT_TRUE(inFile.is_open());

    std::string line;
    std::getline(inFile, line);
    EXPECT_EQ(line, "3");

    std::getline(inFile, line);
    EXPECT_EQ(line, "5 0 0 0 0 0 0 0 0");

    inFile.close();
    std::remove(testFile.c_str());
}

// Тест решения судоку
TEST(SudokuTest, SolveSudoku) {
    std::vector<std::vector<int>> grid = {
        {0, 0, 5, 3, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 7, 0, 0, 1, 0, 5, 0, 0},
        {4, 0, 0, 0, 0, 5, 3, 0, 0},
        {0, 1, 0, 0, 7, 0, 0, 0, 6},
        {0, 0, 3, 2, 0, 0, 0, 8, 0},
        {0, 6, 0, 5, 0, 0, 0, 0, 9},
        {0, 0, 4, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 9, 7, 0, 0}
    };

    bool solved = solveSudokuWithDancingLinks(grid);
    EXPECT_TRUE(solved);

    // Проверяем, что все ячейки заполнены корректно
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            EXPECT_NE(grid[i][j], 0);
        }
    }
}

// Тест на отсутствие решения
TEST(SudokuTest, NoSolution) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    bool solved = solveSudokuWithDancingLinks(grid);
    EXPECT_FALSE(solved);
}