#include <gtest/gtest.h>
#include "graph.h" // ���������� ��� ������������ ���� � ����������� �������

class GraphTest : public ::testing::Test {
protected:
    Graph graph;
    int V = 6; // ����� ������ �����

    void SetUp() override {
        initGraph(&graph, V); // ������������� �����
    }

    void TearDown() override {
        for (int i = 0; i < V; i++) {
            free(graph.adj[i]); // ������������ ������
        }
    }
};

// ���� 1: ���� ����������
TEST_F(GraphTest, PathExists) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 3, 3, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 4); // ����: 1 -> 2 -> 3 -> 4
}

// ���� 2: ���� �����������
TEST_F(GraphTest, PathNotExists) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 5, 3, 0, path, &pathLength);

    EXPECT_FALSE(result);
    EXPECT_EQ(pathLength, 0);
}

// ���� 3: ����������� ����
TEST_F(GraphTest, CyclicGraph) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 0);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 1, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 2); // ����: 1 -> 2
}

// ���� 4: �������� ����
TEST_F(GraphTest, LinearGraph) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 5, 5, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 6); // ����: 1 -> 2 -> 3 -> 4 -> 5 -> 6
}

// ���� 5: ��������� ����
TEST_F(GraphTest, DisconnectedGraph) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 2, 3);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 3, 2, 0, path, &pathLength);

    EXPECT_FALSE(result);
    EXPECT_EQ(pathLength, 0);
}

// ���� 6: ����������� ����� ����
TEST_F(GraphTest, MinLengthPath) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 1, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 3); // ����: 1 -> 2 -> 3
}

// ���� 7: ���� � �������
TEST_F(GraphTest, GraphWithLoops) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 2); // �����

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 2, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 3); // ����: 1 -> 2 -> 3
}

// ���� 8: ������� K
TEST_F(GraphTest, LargeK) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 5, 0, path, &pathLength);

    EXPECT_FALSE(result); // ���� ������ >= 5 ���
}

// ���� 9: ��������� �����
TEST_F(GraphTest, MultiplePaths) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 0, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 1, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 2); // ���������� ������ ����: 1 -> 3
}

// ���� 10: �������� �������
TEST_F(GraphTest, SingleNode) {
    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 0, 1, 0, path, &pathLength);

    EXPECT_FALSE(result); // ���� ���
    EXPECT_EQ(pathLength, 0);
}