#include <gtest/gtest.h>

extern "C" {
#include "labD.h"
}

TEST(LabDTEST, findHamiltonianPath_EmptyGraph_NoPath) {
    //Arrange
    resetGraph();

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 0);
}

TEST(LabDTEST, findHamiltonianPath_SingleVertex_Path) {
    //Arrange
    resetGraph();
    n = 1;

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 1);
}

TEST(LabDTEST, findHamiltonianPath_TwoVerticesConnected_Path) {
    //Arrange
    resetGraph();
    n = 2;
    addGraphEdge(1, 2);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 1);
}

TEST(LabDTEST, findHamiltonianPath_TwoVerticesDisconnected_NoPath) {
    //Arrange
    resetGraph();
    n = 2;

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 0);
}

TEST(LabDTEST, findHamiltonianPath_ThreeVerticesCycle_Path) {
    //Arrange
    resetGraph();
    n = 3;
    addGraphEdge(1, 2);
    addGraphEdge(2, 3);
    addGraphEdge(3, 1);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 1);
}

TEST(LabDTEST, findHamiltonianPath_ThreeVerticesPath_Path) {
    //Arrange
    resetGraph();
    n = 3;
    addGraphEdge(1, 2);
    addGraphEdge(2, 3);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 1);
}

TEST(LabDTEST, findHamiltonianPath_FourVerticesCycle_Path) {
    //Arrange
    resetGraph();
    n = 4;
    addGraphEdge(1, 2);
    addGraphEdge(2, 3);
    addGraphEdge(3, 4);
    addGraphEdge(4, 1);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 1);
}

TEST(LabDTEST, findHamiltonianPath_FourVerticesPath_Path) {
    //Arrange
    resetGraph();
    n = 4;
    addGraphEdge(1, 2);
    addGraphEdge(2, 3);
    addGraphEdge(3, 4);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 1);
}

TEST(LabDTEST, findHamiltonianPath_FourVerticesNoPath_NoPath) {
    //Arrange
    resetGraph();
    n = 4;
    addGraphEdge(2, 4);
    addGraphEdge(1,3);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(), 0);
}

TEST(LabDTEST, findHamiltonianPath_FiveVerticesNoPath_NoPath) {
    //Arrange
    resetGraph();
    n = 5;
    addGraphEdge(1,2);
    addGraphEdge(2,3);
    addGraphEdge(3,4);

    //Act & Assert
    ASSERT_EQ(findHamiltonianPath(),0);
}

