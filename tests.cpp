#include "pch.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "C:\Users\Khan\source\repos\example\main.h"
#pragma warning(disable:4996)


// Функция для запуска программы и проверки результата
void runKnapsackTest(const std::string& inputData, const std::string& expectedOutput) {
    // Перезаписываем input.txt
    std::ofstream inputFile("input.txt");
    ASSERT_TRUE(inputFile.is_open()) << "Не удалось открыть input.txt для записи";
    inputFile << inputData;
    inputFile.close();

    // Запускаем программу через системный вызов
    int exitCode = system("lab_d.exe");
    ASSERT_EQ(exitCode, 0) << "Ошибка запуска программы";

    // Читаем содержимое output.txt
    std::ifstream outputFile("output.txt");
    ASSERT_TRUE(outputFile.is_open()) << "Не удалось открыть output.txt для чтения";
    std::string actualOutput;
    std::getline(outputFile, actualOutput);
    outputFile.close();

    // Удаляем возможные лишние пробелы
    actualOutput.erase(actualOutput.find_last_not_of(" \n\r\t") + 1);

    // Сравниваем с ожидаемым результатом
    EXPECT_EQ(actualOutput, expectedOutput);
}




// Тест 1: Нет решения
TEST(KnapsackTest, NoSolution) {
    runKnapsackTest("5 5 20\n1 2 2 2 3\n7 1 1 4 10\n", "0");
}

// Тест 2: Одно решение
TEST(KnapsackTest, SingleItemSolution) {
    runKnapsackTest("5 5 10\n1 2 2 2 3\n7 1 1 4 10\n", "5");
}

// Тест 3: Множество решений
TEST(KnapsackTest, MultipleSolutions) {
    runKnapsackTest("4 6 8\n2 3 1 4\n5 6 2 7\n", "1 2");
}

// Тест 4: Все предметы помещаются
TEST(KnapsackTest, AllItemsFit) {
    runKnapsackTest("3 15 15\n3 5 7\n3 5 7\n", "1 2 3");
}

// Тест 5: Идеальное соответствие
TEST(KnapsackTest, PerfectMatch) {
    runKnapsackTest("4 10 10\n5 6 7 10\n1 2 3 10\n", "4");
}

// Тест 6: Минимальный случай
TEST(KnapsackTest, MinimalCase) {
    runKnapsackTest("1 1 1\n1\n1\n", "1");
}

// Тест 7: Большие значения
TEST(KnapsackTest, LargeValues) {
    runKnapsackTest("5 50 100\n10 20 30 40 50\n20 30 40 50 60\n", "0");
}

// Тест 8: Невозможно достичь K
TEST(KnapsackTest, ImpossibleK) {
    runKnapsackTest("4 15 100\n5 5 5 5\n10 10 10 10\n", "0");
}

// Тест 9: Вместимость слишком мала
TEST(KnapsackTest, TooSmallCapacity) {
    runKnapsackTest("3 1 10\n2 3 4\n5 6 7\n", "0");
}

// Тест 10: Точное соответствие вместимости
TEST(KnapsackTest, ExactCapacity) { 
    runKnapsackTest("5 10 15\n2 3 5 7 1\n1 2 3 4 5\n", "0");
} 

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}