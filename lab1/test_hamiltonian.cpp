#include "gtest/gtest.h"
#include "hamiltonian.h"

#include <vector>

void adjacencyListToMatrix(const std::vector<std::vector<int>>& adjList, int adjMatrix[][MAX_VERTICES], int num_vertices) {
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < num_vertices; ++i) {
        for (int neighbor : adjList[i]) {
            adjMatrix[i][neighbor - 1] = 1;
            adjMatrix[neighbor - 1][i] = 1;
        }
    }
}

TEST(HamiltonianPathTest, HasHamiltonianPathSimple) {
    int num_vertices = 4;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2, 3},
        {1, 4},
        {1, 4},
        {2, 3}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, NoHamiltonianPathDisconnected) {
    int num_vertices = 4;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2},
        {1},
        {4},
        {3}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_FALSE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, SingleVertex) {
    int num_vertices = 1;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int path[MAX_VERTICES];

    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, CompleteGraph) {
    int num_vertices = 5;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            adjMatrix[i][j] = (i != j) ? 1 : 0;
        }
    }
    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, EmptyGraph) {
    int num_vertices = 5;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            adjMatrix[i][j] = 0;
        }
    }

    if (num_vertices > 1) {
        ASSERT_FALSE(hamiltonian_path(num_vertices, adjMatrix, path));
    }
    else {
        ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
    }
}

TEST(HamiltonianPathTest, LongerHamiltonianPath) {
    int num_vertices = 6;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2, 6},
        {1, 3},
        {2, 4},
        {3, 5},
        {4, 6},
        {1, 5}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, AlmostHamiltonianPath) {
    int num_vertices = 5;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2, 3},
        {1, 4},
        {1, 5},
        {2},
        {3}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_FALSE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, SmallCycle) {
    int num_vertices = 3;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2, 3},
        {1, 3},
        {1, 2}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, ComplexHamiltonianPath) {
    int num_vertices = 7;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2, 3, 4},
        {1, 5},
        {1, 6},
        {1, 7},
        {2},
        {3},
        {4}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, LargerDisconnected) {
    int num_vertices = 8;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2},
        {1},
        {4},
        {3},
        {6},
        {5},
        {},
        {}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_FALSE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, NoHamiltonianPathExample2) {
    int num_vertices = 5;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];

    std::vector<std::vector<int>> adjList = {
        {2, 3},
        {1},
        {1, 4},
        {3, 5},
        {4}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_FALSE(hamiltonian_path(num_vertices, adjMatrix, path));
}

TEST(HamiltonianPathTest, DirectHamiltonianPath) {
    int num_vertices = 4;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES];
    std::vector<std::vector<int>> adjList = {
        {2},
        {1, 3},
        {2, 4},
        {3}
    };

    adjacencyListToMatrix(adjList, adjMatrix, num_vertices);
    ASSERT_TRUE(hamiltonian_path(num_vertices, adjMatrix, path));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}