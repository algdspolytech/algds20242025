#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "..\wagon\wagon.h"
}


TEST(Lab_D_Tests, NormalInput_Return1_no1) {
	const char* filename = "normal_input.txt";
	ASSERT_EQ(wagons_sort(filename, "normal_input_output.txt"), 1);
}

TEST(Lab_D_Tests, EmptyGraph_ReturnMinus1_no2) {
	const char* filename = "empty_graph.txt";
	ASSERT_EQ(wagons_sort(filename, "empty_graph_output.txt"), -1);
}

TEST(Lab_D_Tests, CantBuildSequenceBeforeDeparture_Return0_no3) {
	const char* filename = "cannot_build_sequence_intime.txt";
	ASSERT_EQ(wagons_sort(filename, "cannot_build_sequence_intime_output.txt"), 0);
}

TEST(Lab_D_Tests, InvalidTimeValues_ReturnMinus1_no4) {
	const char* filename = "invalid_times.txt";
	ASSERT_EQ(wagons_sort(filename, "invalid_times_output.txt"), -1);
}

TEST(Lab_D_Tests, w1_Equals_w2_ReturnValidVal_no5) {
	const char* filename = "w1_eq_w2.txt";
	ASSERT_EQ(wagons_sort(filename, "w1_eq_w2_output.txt"), 1);
}

TEST(Lab_D_Tests, NotAppropriateTextFile_DisplayError_no6) {
	const char* filename = "not_appropriate_format.txt";
	ASSERT_EQ(wagons_sort(filename, "w1_eq_w2_output.txt"), -1);
}

TEST(Lab_D_Tests, Invalid_w1_ReturnMinus1_no7) {
	const char* filename = "invalid_w1.txt";
	ASSERT_EQ(wagons_sort(filename, "invalid_w1_output.txt"), -1);
}

TEST(Lab_D_Tests, InvalidNumberOfWagons_ReturnMinus1_no8) {
	const char* filename = "invalid_num_of_wagons.txt";
	ASSERT_EQ(wagons_sort(filename, "invalid_num_of_wagons_output.txt"), -1);
}

TEST(Lab_D_Tests, Invalid_w2_ReturnMinus1_no9) {
	const char* filename = "invalid_w2.txt";
	ASSERT_EQ(wagons_sort(filename, "invalid_w2_output.txt"), -1);
}

TEST(Lab_D_Tests, Invalid_K_ReturnMinus1_no10) {
	const char* filename = "invalid_K.txt";
	ASSERT_EQ(wagons_sort(filename, "invalid_K_output.txt"), -1);
}

TEST(Lab_D_Tests, Invalid_D_ReturnMinus1_no11) {
	const char* filename = "invalid_D.txt";
	ASSERT_EQ(wagons_sort(filename, "invalid_D_output.txt"), -1);
}