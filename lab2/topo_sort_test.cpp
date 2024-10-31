// Файл: topo_sort_test.cpp

#define TESTING
#include "topo_sort.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdio>  // Для функции remove

std::string read_output() {
    std::ifstream file("output.txt");
    std::string output;
    std::getline(file, output);
    return output;
}

// Укажите правильный путь к `topo_sort.exe`, если требуется
const char* TOPO_SORT_PATH = "topo_sort.exe";

// Тест 1: Пустой ввод
TEST(TopoSortTest, EmptyInput_no1) {
    std::ofstream file("input.txt");
    file << "";
    file.close();

    remove("output.txt");  // Удаление output.txt перед запуском теста
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

// Тест 2: Один элемент, отсутствие зависимостей
TEST(TopoSortTest, SingleElement_no2) {
    std::ofstream file("input.txt");
    file << "a";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "a ");
}

// Тест 3: Несколько независимых элементов
TEST(TopoSortTest, IndependentElements_no3) {
    std::ofstream file("input.txt");
    file << "a b c";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "a b c ");
}

// Тест 4: Простой цикл
TEST(TopoSortTest, SimpleCycle_no4) {
    std::ofstream file("input.txt");
    file << "a b\nb a";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

// Тест 5: Многосвязный граф
TEST(TopoSortTest, MultipleDependencies_no5) {
    std::ofstream file("input.txt");
    file << "a b c d e\nb c\nc d\na e\ne d";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "a b e c d ");
}

// Тест 6: Случай с несвязанными подграфами
TEST(TopoSortTest, DisconnectedGraphs_no6) {
    std::ofstream file("input.txt");
    file << "a b c d e\nb c\nd e";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "a b d c e ");
}

// Тест 7: Линейная цепочка зависимостей
TEST(TopoSortTest, LinearChain_no7) {
    std::ofstream file("input.txt");
    file << "a b c d\n a b\n b c\n c d";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "a b c d ");
}

// Тест 8: Граф с несколькими возможными решениями
TEST(TopoSortTest, MultipleSolutions_no8) {
    std::ofstream file("input.txt");
    file << "a b c\n a b\n a c";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_TRUE(read_output() == "a b c " || read_output() == "a c b ");
}

// Тест 9: Большой граф без зависимостей
TEST(TopoSortTest, LargeGraphNoDependencies_no9) {
    std::ofstream file("input.txt");
    file << "a b c d e f g h i j";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "a b c d e f g h i j ");
}

// Тест 10: Граф с циклом в одном из подграфов
TEST(TopoSortTest, CycleInSubgraph_no10) {
    std::ofstream file("input.txt");
    file << "a b c d e\n a b\n b c\n c a\n d e";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "Ошибка при запуске topo_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
