// ����: topo_sort_test.cpp

#define TESTING
#include "topo_sort.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdio>  // ��� ������� remove

std::string read_output() {
    std::ifstream file("output.txt");
    std::string output;
    std::getline(file, output);
    return output;
}

// ������� ���������� ���� � `topo_sort.exe`, ���� ���������
const char* TOPO_SORT_PATH = "topo_sort.exe";

// ���� 1: ������ ����
TEST(TopoSortTest, EmptyInput_no1) {
    std::ofstream file("input.txt");
    file << "";
    file.close();

    remove("output.txt");  // �������� output.txt ����� �������� �����
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

// ���� 2: ���� �������, ���������� ������������
TEST(TopoSortTest, SingleElement_no2) {
    std::ofstream file("input.txt");
    file << "a";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "a ");
}

// ���� 3: ��������� ����������� ���������
TEST(TopoSortTest, IndependentElements_no3) {
    std::ofstream file("input.txt");
    file << "a b c";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "a b c ");
}

// ���� 4: ������� ����
TEST(TopoSortTest, SimpleCycle_no4) {
    std::ofstream file("input.txt");
    file << "a b\nb a";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

// ���� 5: ������������ ����
TEST(TopoSortTest, MultipleDependencies_no5) {
    std::ofstream file("input.txt");
    file << "a b c d e\nb c\nc d\na e\ne d";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "a b e c d ");
}

// ���� 6: ������ � ������������ ����������
TEST(TopoSortTest, DisconnectedGraphs_no6) {
    std::ofstream file("input.txt");
    file << "a b c d e\nb c\nd e";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "a b d c e ");
}

// ���� 7: �������� ������� ������������
TEST(TopoSortTest, LinearChain_no7) {
    std::ofstream file("input.txt");
    file << "a b c d\n a b\n b c\n c d";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "a b c d ");
}

// ���� 8: ���� � ����������� ���������� ���������
TEST(TopoSortTest, MultipleSolutions_no8) {
    std::ofstream file("input.txt");
    file << "a b c\n a b\n a c";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_TRUE(read_output() == "a b c " || read_output() == "a c b ");
}

// ���� 9: ������� ���� ��� ������������
TEST(TopoSortTest, LargeGraphNoDependencies_no9) {
    std::ofstream file("input.txt");
    file << "a b c d e f g h i j";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "a b c d e f g h i j ");
}

// ���� 10: ���� � ������ � ����� �� ���������
TEST(TopoSortTest, CycleInSubgraph_no10) {
    std::ofstream file("input.txt");
    file << "a b c d e\n a b\n b c\n c a\n d e";
    file.close();

    remove("output.txt");
    int result = system(TOPO_SORT_PATH);
    ASSERT_EQ(result, 0) << "������ ��� ������� topo_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
