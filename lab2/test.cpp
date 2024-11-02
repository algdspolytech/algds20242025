#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\User\OneDrive\Desktop\lab c\graph\graph\main.h"


TEST(DFSTests, EmptyGraph) {
	std::vector<std::vector<int>> graph;
	EXPECT_FALSE(dfs(graph, 0, 1));
}

TEST(DFSTests, SingleNodeGraph) {
	std::vector<std::vector<int>> graph = { {} };
	EXPECT_TRUE(dfs(graph, 0, 0));
}

TEST(DFSTests, SimplePath) {
	std::vector<std::vector<int>> graph = { {1}, {2}, {} };
	EXPECT_TRUE(dfs(graph, 0, 2));
}

TEST(DFSTests, NoPath) {
	std::vector<std::vector<int>> graph = { {1}, {2}, {} };
	EXPECT_FALSE(dfs(graph, 0, 3));
}

TEST(DFSTests, CyclicGraph) {
	std::vector<std::vector<int>> graph = { {1}, {2, 0}, {} };
	EXPECT_TRUE(dfs(graph, 0, 2));
}

TEST(DFSTests, LargerGraphPathExists) {
	std::vector<std::vector<int>> graph = { {1, 2}, {3}, {4}, {5}, {} };
	EXPECT_TRUE(dfs(graph, 0, 4));
}

TEST(DFSTests, LargerGraphPathDoesNotExist) {
	std::vector<std::vector<int>> graph = { {1, 2}, {3}, {4}, {5}, {} };
	EXPECT_FALSE(dfs(graph, 0, 6));
}

TEST(DFSTests, DisconnectedGraph) {
	std::vector<std::vector<int>> graph = { {1}, {2}, {3}, {4}, {5} };
	EXPECT_FALSE(dfs(graph, 0, 4));
}

TEST(DFSTests, GraphWithSelfLoop) {
	std::vector<std::vector<int>> graph = { {0, 1}, {2}, {} };
	EXPECT_TRUE(dfs(graph, 0, 1));
}

TEST(DFSTests, GraphWithMultiplePaths) {
	std::vector<std::vector<int>> graph = { {1,2}, {3}, {3}, {} };
	EXPECT_TRUE(dfs(graph, 0, 3));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}