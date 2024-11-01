#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
	#include "..\labC\labC.h"
}

TEST(Lab_C_Tests, EmptyGraph_DisplayError) {
	const char* filename = "empty_graph.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, NoPathBetweenVertices_ReturnMinus1) {
	const char* filename = "no_path.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, MultiplePathsBetweenVertices_ReturnValidVal) {
	const char* filename = "multiple_paths.txt";
	ASSERT_EQ(shortestPath(filename), 2);
}

TEST(Lab_C_Tests, EqualStartAndEndVertices_Return0) {
	const char* filename = "same_start_and_end.txt";
	ASSERT_EQ(shortestPath(filename), 0);
}

TEST(Lab_C_Tests, NotAppropriateTextFile_DisplayError) {
	const char* filename = "not_appropriate_format.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, InvalidStartVertex_ReturnMinus1) {
	const char* filename = "invalid_start_vertex.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, InvalidNumberOfVertices_ReturnMinus1) {
	const char* filename = "invalid_num_of_vertices.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, InvalidEndVertex_ReturnMinus1) {
	const char* filename = "invalid_end_vertex.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, InvalidAdjacencyMatrix_DisplayError) {
	const char* filename = "invalid_adjacency_matrix.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}

TEST(Lab_C_Tests, InvalidFileName_DisplayError) {
	const char* filename = "invalid_file_name_hehehehehe.txt";
	ASSERT_EQ(shortestPath(filename), -1);
}