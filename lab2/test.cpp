#include "pch.h"

extern "C" {
#include "Lab_C.h" // Подключаем ваш код с функциями
}

TEST(LongNumberTest, Creating_matrix) {
    int n = 5;
    int** matrix = Create_Matrix_adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            EXPECT_EQ(matrix[i][j], 0) << "Ожидалось 0";
        }
    }
    Free_Matrix_adj(matrix, n);
}

TEST(LongNumberTest, Counting_vertices) { 
    EXPECT_EQ(Count_Vertices("test_1.txt"), 2) << "Ожидалось 2";
}

TEST(LongNumberTest, Parsing) {
    int n = 2;
    int** matrix = Create_Matrix_adj(n);
    Parsing_Matrix_adj("test_1.txt", matrix, n);
    EXPECT_EQ(matrix[0][0], 0) << "Ожидалось 0";
    EXPECT_EQ(matrix[0][1], 1) << "Ожидалось 1";
    EXPECT_EQ(matrix[1][0], 1) << "Ожидалось 1";
    EXPECT_EQ(matrix[1][1], 0) << "Ожидалось 0";
    Free_Matrix_adj(matrix, n);
}

TEST(LongNumberTest, Readline) {
    FILE* file = fopen("test_1.txt", "r");
    char* line = Read_line(file);
    EXPECT_EQ(line[0], '0') << "Ожидалось 0";
    EXPECT_EQ(line[1], ':') << "Ожидалось :";
    EXPECT_EQ(line[2], ' ') << "Ожидалось " "";
    EXPECT_EQ(line[3], '1') << "Ожидалось 1";
    EXPECT_EQ(line[4], '\0') << "Ожидалось \\0";
    fclose(file);
    free(line);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); // Запуск всех тестов
}
