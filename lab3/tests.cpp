#include <gtest/gtest.h>

extern "C" {
#include "sudoku_solver.h"
}

// Тест 1: Решение стандартной сетки судоку
TEST(GridSolverTest, SolveExampleGrid_no1) {
    GridStatus result = solve_grid("./tests/example.txt", "./tests/output.txt");
    ASSERT_EQ(result, GRID_SUCCESS);
    Grid grid = read_grid_from_file("./tests/output.txt");
    ASSERT_EQ(is_grid_complete(grid), 1);
    destroy_grid(grid);
}

// Тест 2: Неправильный входной файл
TEST(GridSolverTest, SolveInvalidInput_no2) {
    GridStatus result = solve_grid("./tests/nonexistent.txt", "./tests/output.txt");
    ASSERT_EQ(result, GRID_INPUT_ERROR);
}

// Тест 3: Неправильный выходной файл
TEST(GridSolverTest, SolveInvalidOutput_no3) {
    GridStatus result = solve_grid("./tests/example.txt", "?invalid/output.txt");
    ASSERT_EQ(result, GRID_OUTPUT_ERROR);
}

// Тест 4: Нерешаемая сетка судоку
TEST(GridSolverTest, SolveUnsolvableGrid_no4) {
    GridStatus result = solve_grid("./tests/unsolvable.txt", "./tests/output.txt");
    ASSERT_EQ(result, GRID_NO_SOLUTION);
}

// Тест 5: Загрузка пустой сетки судоку
TEST(GridSolverTest, LoadEmptyGrid_no5) {
    Grid grid = read_grid_from_file("./tests/empty.txt");
    ASSERT_EQ(grid.block_size, 3);
    destroy_grid(grid);
}

// Тест 6: Загрузка сетки с малым размером блока
TEST(GridSolverTest, LoadSmallGrid_no6) {
    Grid grid = read_grid_from_file("./tests/small.txt");
    ASSERT_EQ(grid.block_size, -1);  
}

// Тест 7: Загрузка некорректных данных
TEST(GridSolverTest, LoadInvalidGridData_no7) {
    Grid grid = read_grid_from_file("./tests/invaliddata.txt");
    ASSERT_EQ(grid.cells == nullptr, true);
    ASSERT_EQ(grid.block_size, -1);
}

// Тест 8: Решение сложной сетки судоку
TEST(GridSolverTest, SolveHardGrid_no8) {
    GridStatus result = solve_grid("./tests/hard.txt", "./tests/output.txt");
    ASSERT_EQ(result, GRID_SUCCESS);
    Grid grid = read_grid_from_file("./tests/output.txt");
    ASSERT_EQ(is_grid_complete(grid), 1);
    destroy_grid(grid);
}

// Тест 9: Проверка валидной сетки судоку
TEST(GridSolverTest, ValidateCorrectGrid_no9) {
    Grid grid = read_grid_from_file("./tests/solved.txt");
    ASSERT_EQ(is_grid_valid(grid), 1);
    destroy_grid(grid);
}

// Тест 10: Решение сетки судоку с одной пропущенной ячейкой
TEST(GridSolverTest, SolveOneMissingCell_no10) {
    GridStatus result = solve_grid("./tests/onemissing.txt", "./tests/output.txt");
    ASSERT_EQ(result, GRID_SUCCESS);
    Grid grid = read_grid_from_file("./tests/output.txt");
    ASSERT_EQ(is_grid_complete(grid), 1);
    destroy_grid(grid);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
