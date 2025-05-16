#include <gtest/gtest.h>
#include <fstream>
#include <vector>


extern "C" {
    void solve_problem(const char* input_file, const char* output_file);
}

std::vector<int> read_output(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> result;
    int value;

    while (file >> value) {
        result.push_back(value);
    }

    return result;
}

TEST(SubsetSumTest, TestAddToEmptyList_no1) {
    std::ofstream input("input.txt");
    input << "10\n5\n2 3 4 5 9\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

TEST(SubsetSumTest, TestNoSubset_no2) {
    std::ofstream input("input.txt");
    input << "20\n5\n1 2 3 4 5\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_EQ(output.size(), 0); 
}

TEST(SubsetSumTest, TestSingleElementEqualToTarget_no3) {
    std::ofstream input("input.txt");
    input << "5\n1\n5\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_EQ(output.size(), 1);
    EXPECT_EQ(output[0], 5); 
}

TEST(SubsetSumTest, TestMultipleElementsEqualToTarget_no4) {
    std::ofstream input("input.txt");
    input << "8\n6\n1 2 3 4 5 6\n";
    input.close();

    solve_problem("input.txt", "output.txt");
    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

TEST(SubsetSumTest, TestExactMatchWithMultipleCombinations_no5) {
    std::ofstream input("input.txt");
    input << "10\n5\n1 2 3 7 8\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

TEST(SubsetSumTest, TestEmptyInput_no6) {
    std::ofstream input("input.txt");
    input << "10\n0\n"; 
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_EQ(output.size(), 0); 
}

TEST(SubsetSumTest, TestSingleElementLessThanTarget_no7) {
    std::ofstream input("input.txt");
    input << "10\n1\n5\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_EQ(output.size(), 0); 
}

TEST(SubsetSumTest, TestSingleElementGreaterThanTarget_no8) {
    std::ofstream input("input.txt");
    input << "5\n1\n10\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_EQ(output.size(), 0); 
}

TEST(SubsetSumTest, TestMultipleSameElements_no9) {
    std::ofstream input("input.txt");
    input << "6\n4\n2 2 2 2\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

TEST(SubsetSumTest, TestLargeNumbers_no10) {
    std::ofstream input("input.txt");
    input << "65536\n4\n16384 32768 32768 8192\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

TEST(SubsetSumTest, TestAllElementsAreSame_no11) {
    std::ofstream input("input.txt");
    input << "12\n6\n4 4 4 4 4 4\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

TEST(SubsetSumTest, TestHighValueOfB_no12) {
    std::ofstream input("input.txt");
    input << "1000000000\n5\n200000000 300000000 500000000 400000000 600000000\n";
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_EQ(output.size(), 0); 
}

TEST(SubsetSumTest, TestLargeN_no13) {
    std::ofstream input("input.txt");
    input << "1000\n1000\n";
    for (int i = 1; i <= 1000; i++) {
        input << i << " ";
    }
    input.close();

    solve_problem("input.txt", "output.txt");

    auto output = read_output("output.txt");

    EXPECT_NE(output.size(), 0); 
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}