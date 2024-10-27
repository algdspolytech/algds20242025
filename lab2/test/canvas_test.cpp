#include <gtest/gtest.h>

extern "C" {
    #include "canvas.h" 
}

// Тест для пустого холста (все клетки вырезаны)
TEST(CanvasComponentsTest, EmptyCanvas) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 0);  // Все клетки вырезаны
    EXPECT_EQ(countComponents(canvas, m, n), 0);
    freeCanvas(canvas, m);
}

// Тест для полностью целого холста (без вырезанных клеток)
TEST(CanvasComponentsTest, FullCanvas) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);  // Все клетки целые
    EXPECT_EQ(countComponents(canvas, m, n), 1);
    freeCanvas(canvas, m);
}

// Тест для одного выреза в центре холста
TEST(CanvasComponentsTest, SingleCutInCenter) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    canvas[2][2] = 0;  // Вырез в центре
    EXPECT_EQ(countComponents(canvas, m, n), 1);
    freeCanvas(canvas, m);
}

// Тест для двух несвязанных вырезов
TEST(CanvasComponentsTest, TwoSeparateCuts) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    canvas[1][1] = 0;
    canvas[3][3] = 0;
    EXPECT_EQ(countComponents(canvas, m, n), 1);
    freeCanvas(canvas, m);
}

// Тест для разбиения на две части (вырез по центру строки)
TEST(CanvasComponentsTest, SplitCanvasHorizontally) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    for (int i = 0; i < n; i++) {
        canvas[2][i] = 0;  // Вырез по центру строки
    }
    EXPECT_EQ(countComponents(canvas, m, n), 2);
    freeCanvas(canvas, m);
}

// Тест для разбиения на две части (вырез по центру столбца)
TEST(CanvasComponentsTest, SplitCanvasVertically) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    for (int i = 0; i < m; i++) {
        canvas[i][2] = 0;  // Вырез по центру столбца
    }
    EXPECT_EQ(countComponents(canvas, m, n), 2);
    freeCanvas(canvas, m);
}

// Тест для шахматного расположения вырезов
TEST(CanvasComponentsTest, ChessboardPattern) {
    int m = 4, n = 4;
    int** canvas = createCanvas(m, n, 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) % 2 == 0) {
                canvas[i][j] = 0;  // Вырез по шахматному узору
            }
        }
    }
    EXPECT_EQ(countComponents(canvas, m, n), 8);
    freeCanvas(canvas, m);
}

// Тест для одного выреза в углу холста
TEST(CanvasComponentsTest, SingleCutInCorner) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    canvas[0][0] = 0;  // Вырез в углу
    EXPECT_EQ(countComponents(canvas, m, n), 1);
    freeCanvas(canvas, m);
}

// Тест для вырезов по периметру холста
TEST(CanvasComponentsTest, CutsAroundPerimeter) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    for (int i = 0; i < n; i++) {
        canvas[0][i] = 0;
        canvas[m - 1][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        canvas[i][0] = 0;
        canvas[i][n - 1] = 0;
    }
    EXPECT_EQ(countComponents(canvas, m, n), 1);
    freeCanvas(canvas, m);
}

// Тест на большой холcт, что программа не упадёт
TEST(CanvasComponentsTest, LargeCanvas) {
    int m = 100, n = 100;
    int** canvas = createCanvas(m, n, 1);  // Полностью заполненный холст без вырезов
    EXPECT_EQ(countComponents(canvas, m, n), 1);
    freeCanvas(canvas, m);
}

// Тест с разрезом ввиде креста
TEST(CanvasComponentsTest, CrossShapeCut) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    for (int i = 0; i < m; ++i) {
        canvas[i][2] = 0;  // Вертикальный крест
    }
    for (int j = 0; j < n; ++j) {
        canvas[2][j] = 0;  // Горизонтальный крест
    }
    EXPECT_EQ(countComponents(canvas, m, n), 4);
    freeCanvas(canvas, m);
}

// Тест с диагональным разрезом
TEST(CanvasComponentsTest, DiagonalCuts) {
    int m = 5, n = 5;
    int** canvas = createCanvas(m, n, 1);
    for (int i = 0; i < m; ++i) {
        canvas[i][i] = 0;  // Диагональные вырезы
    }
    EXPECT_EQ(countComponents(canvas, m, n), 2);
    freeCanvas(canvas, m);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
