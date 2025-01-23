#include "gtest/gtest.h"
#include "graphcompare.h"

TEST(readListTest, readInvalidPathL) {
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	EXPECT_DEATH(readAdjList(NULL, graph, vertcount), "Invalid File Path");
}

TEST(readMatrixTest, readInvalidPathM) {
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	EXPECT_DEATH(readAdjMatrix(NULL, graph, vertcount), "Invalid File Path");
}

TEST(readListTest, readEmptyFileL) {
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	readAdjList("empty.txt", graph, vertcount);
	EXPECT_EQ(vertcount, 0);
}

TEST(readMatrixTest, readEmptyFileM) {
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	readAdjMatrix("empty.txt", graph, vertcount);
	EXPECT_EQ(vertcount, 0);
}

TEST(readListTest, readNoEdgesFileL) {
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	readAdjList("noedgeslist.txt", graph, vertcount);
	ASSERT_EQ(vertcount, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(graph[i][j], 0);
		}
	}
}

TEST(readMatrixTest, readNoEdgesFileM) {
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	readAdjMatrix("noedgesmatrix.txt", graph, vertcount);
	ASSERT_EQ(vertcount, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(graph[i][j], 0);
		}
	}
}

TEST(readListTest, readNormalFileL) {
	int manual[3][3] = { {0, 1, 1}, {1, 0, 0}, {1, 0, 0} };
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	readAdjList("normallist.txt", graph, vertcount);
	ASSERT_EQ(vertcount, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(graph[i][j], manual [i][j]);
		}
	}
}

TEST(readMatrixTest, readNormalFileM) {
	int manual[3][3] = { {0, 1, 1}, {1, 0, 0}, {1, 0, 0} };
	int graph[MAX_VERT][MAX_VERT];
	int* vertcount;
	readAdjMatrix("normalmatrix.txt", graph, vertcount);
	ASSERT_EQ(vertcount, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(graph[i][j], manual[i][j]);
		}
	}
}

TEST(GraphCompareTest, compareEmptyFiles) {
	EXPECT_EQ(graphEquals("empty.txt","empty.txt"), 1);
}

TEST(GraphCompareTest, compareNormalFiles) {
	EXPECT_EQ(graphEquals("normallist.txt", "normalmatrix.txt"), 1);
}