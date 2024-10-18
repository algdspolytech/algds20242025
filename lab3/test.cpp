#include "headers/main.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

TEST(HamiltonTests, GraphWithHamiltonPath_no1) {
  FindHamiltonPathStart("testfiles/test_1.txt", "outputfiles/test_1.txt");
}

TEST(HamiltonTests, GraphWithHamiltonCycle_no2) {
  FindHamiltonPathStart("testfiles/test_2.txt", "outputfiles/test_2.txt");
}

TEST(HamiltonTests, GraphWithoutHamiltonPath_no3) {
  FindHamiltonPathStart("testfiles/test_3.txt", "outputfiles/test_3.txt");
}

TEST(HamiltonTests, TwoGraphsInOne_no4) {
  FindHamiltonPathStart("testfiles/test_4.txt", "outputfiles/test_4.txt");
}

TEST(HamiltonTests, GraphWithManyVertexes_no5) {
  FindHamiltonPathStart("testfiles/test_5.txt", "outputfiles/test_5.txt");
}

TEST(HamiltonTests, EmptyGraph_no6) {
  FindHamiltonPathStart("testfiles/test_6.txt", "outputfiles/test_6.txt");
}

TEST(HamiltonTests, GraphWithCycle_no7) {
  FindHamiltonPathStart("testfiles/test_7.txt", "outputfiles/test_7.txt");
}

TEST(HamiltonTests, CompleteGraph_no8) {
  FindHamiltonPathStart("testfiles/test_8.txt", "outputfiles/test_8.txt");
}

TEST(HamiltonTests, LinearGraph_no9) {
  FindHamiltonPathStart("testfiles/test_9.txt", "outputfiles/test_9.txt");
}

TEST(HamiltonTests, GraphWithLoops_no10) {
  FindHamiltonPathStart("testfiles/test_10.txt", "outputfiles/test_10.txt");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}