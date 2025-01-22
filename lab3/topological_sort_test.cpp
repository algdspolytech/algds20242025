#define TESTING
#include "topological_sort.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdio>  

std::string read_output() {
    std::ifstream file("output.txt");
    std::string output;
    std::getline(file, output);
    return output;
}

const char* TOPOLOGICAL_SORT_PATH = "topological_sort.exe";

TEST(TopologicalSortTest, EmptyInput_no1) {
    std::ofstream file("input.txt");
    file << "";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

TEST(TopologicalSortTest, SingleElement_no2) {
    std::ofstream file("input.txt");
    file << "a";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "a");
}

TEST(TopologicalSortTest, IndependentElements_no3) {
    std::ofstream file("input.txt");
    file << "a b c";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "a b c ");
}

TEST(TopologicalSortTest, SimpleCycle_no4) {
    std::ofstream file("input.txt");
    file << "a b\nb a";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

TEST(TopologicalSortTest, MultipleDependencies_no5) {
    std::ofstream file("input.txt");
    file << "a b c d e\nb c\nc d\na e\ne d";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "a b e c d ");
}

TEST(TopologicalSortTest, DisconnectedGraphs_no6) {
    std::ofstream file("input.txt");
    file << "a b c d e\nb c\nd e";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "a b d c e ");
}

TEST(TopologicalSortTest, LinearChain_no7) {
    std::ofstream file("input.txt");
    file << "a b c d\n a b\n b c\n c d";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "a b c d ");
}

TEST(TopologicalSortTest, MultipleSolutions_no8) {
    std::ofstream file("input.txt");
    file << "a b c\n a b\n a c";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_TRUE(read_output() == "a b c " || read_output() == "a c b ");
}

TEST(TopologicalSortTest, LargeGraphNoDependencies_no9) {
    std::ofstream file("input.txt");
    file << "a b c d e f g h i j";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "a b c d e f g h i j ");
}

TEST(TopologicalSortTest, CycleInSubgraph_no10) {
    std::ofstream file("input.txt");
    file << "a b c d e\n a b\n b c\n c a\n d e";
    file.close();

    remove("output.txt");
    int res = system(TOPOLOGICAL_SORT_PATH);
    ASSERT_EQ(res, 0) << "topological_sort.exe";
    EXPECT_EQ(read_output(), "[Error]");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
