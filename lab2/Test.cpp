#include <gtest/gtest.h>
extern "C" {
#include "graph.h"
}

// ���� 1: ���� ���������� ����� ��������� 0 � 3
TEST(GraphTest, PathExists) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);

    ASSERT_TRUE(hasPath(&g, 0, 3));
}

// ���� 2: ���� �� ���������� ����� ��������� 0 � 4
TEST(GraphTest, NoPathExists) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);

    ASSERT_FALSE(hasPath(&g, 0, 4));
}

// ���� 3: ���� ���������� ����� ��������� 1 � 2
TEST(GraphTest, DirectPathExists) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);

    ASSERT_TRUE(hasPath(&g, 1, 2));
}

// ���� 4: �������� �� ���� ��� ����
TEST(GraphTest, NoEdges) {
    Graph g;
    initGraph(&g, 5);

    ASSERT_FALSE(hasPath(&g, 0, 4));  // ��� ���� ���� �� ����������
}

// ���� 5: ���� ���������� � ����� � �����
TEST(GraphTest, PathWithLoop) {
    Graph g;
    initGraph(&g, 3);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 0);  // �����

    ASSERT_TRUE(hasPath(&g, 0, 2));
    ASSERT_TRUE(hasPath(&g, 2, 0));
}

// ���� 6: ���� ���������� ����� ���������, ������������ ����� ��������� ����
TEST(GraphTest, PathWithMultipleEdges) {
    Graph g;
    initGraph(&g, 6);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);

    ASSERT_TRUE(hasPath(&g, 0, 4));  // ���� ����� ��������� ����
}

// ���� 7: �������� �� ���� � ����������� ������������
TEST(GraphTest, MultipleComponents) {
    Graph g;
    initGraph(&g, 6);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 3, 4);

    ASSERT_FALSE(hasPath(&g, 2, 4));  // ���������� �� ���������
    ASSERT_TRUE(hasPath(&g, 0, 2));   // ���� ���������� � ����� ����������
}

// ���� 8: ���� ����������, �� ���� �������� �����
TEST(GraphTest, PathInGraphWithCycles) {
    Graph g;
    initGraph(&g, 4);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 0);  // ����

    ASSERT_TRUE(hasPath(&g, 0, 3));  // ���� ����������
}

// ���� 9: ���� ����� ����� � ��� �� �������� (�� ������ ���� ����)
TEST(GraphTest, SameStartEnd) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);

    ASSERT_TRUE(hasPath(&g, 2, 2));  // ���� ���������� (�� ����� ����)
}

// ���� 10: ���� � ������������ ������
TEST(GraphTest, SingleEdgeGraph) {
    Graph g;
    initGraph(&g, 2);
    addEdge(&g, 0, 1);

    ASSERT_TRUE(hasPath(&g, 0, 1));  // ���� ����������
    ASSERT_TRUE(hasPath(&g, 1, 0));  // ���� ���������� � ��� �������
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}