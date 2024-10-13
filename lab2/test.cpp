#include "headers/main.h"
#include <gtest/gtest.h>
using namespace std;

TEST(Comparing, NotDirectedEqualGraphs_no1) {
  char f1[23] = "testfiles/test_1_l.csv";
  char f2[23] = "testfiles/test_1_m.csv";
  char result = CompareGraphs(f1, f2);

  EXPECT_EQ(result, 1);
}

TEST(Comparing, NotDirectedNotEqualGraphs_no2) {
  char f1[30] = "testfiles/test_2_l.csv";
  char f2[30] = "testfiles/test_2_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 0);
}

TEST(Comparing, EmptyGraphs_no3) {
  char f1[30] = "testfiles/test_3_l.csv";
  char f2[30] = "testfiles/test_3_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 1);
}

TEST(Comparing, EqualDirectedGraphs_no4) {
  char f1[30] = "testfiles/test_4_l.csv";
  char f2[30] = "testfiles/test_4_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 1);
}

TEST(Comparing, NotEqualDirectedGraphs_no5) {
  char f1[30] = "testfiles/test_5_l.csv";
  char f2[30] = "testfiles/test_5_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 0);
}

TEST(Comparing, OppositeDirectedGraphs_no6) {
  char f1[30] = "testfiles/test_6_l.csv";
  char f2[30] = "testfiles/test_6_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 0);
}

TEST(Comparing, WithDifferentVertexesGraphs_no7) {
  char f1[30] = "testfiles/test_7_l.csv";
  char f2[30] = "testfiles/test_7_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 0);
}

TEST(Comparing, OneVertexWithoutEdgeGraphs_no8) {
  char f1[30] = "testfiles/test_8_l.csv";
  char f2[30] = "testfiles/test_8_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 1);
}

TEST(Comparing, OneVertexWithLoopGraphs_no9) {
  char f1[30] = "testfiles/test_9_l.csv";
  char f2[30] = "testfiles/test_9_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 1);
}

TEST(Comparing, WeighetdNotDirectedEqualGraphs_no10) {
  char f1[30] = "testfiles/test_10_l.csv";
  char f2[30] = "testfiles/test_10_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 1);
}

TEST(Comparing, WeighetdDirectedNotEqualGraphs_no11) {
  char f1[30] = "testfiles/test_11_l.csv";
  char f2[30] = "testfiles/test_11_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 0);
}

TEST(Comparing, WithotEdgesEqualGraphs_no1) {
  char f1[30] = "testfiles/test_12_l.csv";
  char f2[30] = "testfiles/test_12_m.csv";
  char result = CompareGraphs(f1, f2);
  EXPECT_EQ(result, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}