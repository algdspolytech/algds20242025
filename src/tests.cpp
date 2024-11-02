#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "graph.h"
}

FILE* CreateTempFile(const char* content) {
    FILE* file = fopen("tmp.txt", "w");
    if (file == nullptr) {
        exit(EXIT_FAILURE);
    }
    fputs(content, file);
    rewind(file);
    fclose(file);

    file = fopen("tmp.txt", "r");
    if (file == nullptr) {
        exit(EXIT_FAILURE);
    }

    return file;
}

TEST(GR_GetAssociationListTest, BasicFunctionality) {
    const char* content = "3\n"
                          "1 2\n"
                          "1 3\n"
                          "0\n";
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    ASSERT_EQ(n, 3);
    ASSERT_EQ(list[0].connectionCnt, 1);
    ASSERT_EQ(list[0].connectedTo[0], 2);
    ASSERT_EQ(list[1].connectionCnt, 1);
    ASSERT_EQ(list[1].connectedTo[0], 3);
    ASSERT_EQ(list[2].connectionCnt, 0);

    GR_DeleteAssociationList(list, n);
    fclose(file);
}

TEST(GR_WriteAssociationListTest, BasicWrite) {
    FILE* file = fopen("tmp.txt", "w");

    GR_Node_t list[2];
    list[0].connectionCnt = 2;
    list[0].connectedTo = new int[2]{2, 3};
    list[1].connectionCnt = 0;

    GR_WriteAssociationList(file, list, 2);

    rewind(file);
    fclose(file);

    file = fopen("tmp.txt", "r");

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    ASSERT_STREQ(buffer, "2\n");

    fgets(buffer, sizeof(buffer), file);
    ASSERT_STREQ(buffer, "2 2 3 \n");

    fgets(buffer, sizeof(buffer), file);
    ASSERT_STREQ(buffer, "0 \n");

    delete[] list[0].connectedTo;
    fclose(file);
}

TEST(GR_WriteAssociationListTest, WriteEmpty) {
    FILE* file = fopen("tmp.txt", "w");

    GR_Node_t list[0];

    GR_WriteAssociationList(file, list, 0);

    rewind(file);
    fclose(file);

    file = fopen("tmp.txt", "r");

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    ASSERT_STREQ(buffer, "0\n");

    fclose(file);
}

TEST(GR_AssociationToMatrixTest, ConvertToMatrix) {
    const char* content = "4\n"
                          "3 1 2 3\n"
                          "0\n"
                          "0\n"
                          "0\n";
    // A graph with one outgoing connection from node 1 to nodes 2, 3, and 4
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    int** matrix = GR_AssociationToMatrix(list, n);

    ASSERT_EQ(matrix[0][1], 1);
    ASSERT_EQ(matrix[0][2], 1);
    ASSERT_EQ(matrix[0][3], 1);
    ASSERT_EQ(matrix[1][0], 0);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    GR_DeleteAssociationList(list, n);
    fclose(file);
}

TEST(GR_WriteAssociationListTest, WriteEmptyList) {
    FILE* file = fopen("tmp.txt", "w");

    GR_Node_t* list = nullptr;
    GR_WriteAssociationList(file, list, 0);

    rewind(file);
    fclose(file);

    file = fopen("tmp.txt", "r");

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    ASSERT_STREQ(buffer, "0\n"); // Expecting a single line indicating zero nodes

    fclose(file);
}

TEST(GR_AssociationToMatrixTest, NoConnections) {
    const char* content = "5\n"
                          "0\n"
                          "0\n"
                          "0\n"
                          "0\n"
                          "0\n";
    // Five nodes with no connections
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    int** matrix = GR_AssociationToMatrix(list, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ASSERT_EQ(matrix[i][j], 0); // All should be zero
        }
        delete[] matrix[i];
    }

    delete[] matrix;

    delete[] list;
    fclose(file);
}

TEST(GR_AssociationToMatrixTest, KnGraph) {
    const char* content = "5\n"
                          "4 1 2 3 4\n"
                          "4 0 2 3 4\n"
                          "4 0 1 3 4\n"
                          "4 0 1 2 4\n"
                          "4 0 1 2 3\n";
    // Five nodes with no connections
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    int** matrix = GR_AssociationToMatrix(list, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i == j)
                ASSERT_EQ(matrix[i][j], 0); //Kn dont have self loops
            else
                ASSERT_EQ(matrix[i][j], 1); // All should be one
        }
        delete[] matrix[i];
    }

    delete[] matrix;

    delete[] list;
    fclose(file);
}

TEST(GR_AssociationToMatrixTest, OneWayConnection) {
    const char* content = "3\n"
                          "1 2\n"
                          "0\n"
                          "0\n";
    // Node 1 -> Node 2, not vice versa
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    int** matrix = GR_AssociationToMatrix(list, n);

    ASSERT_EQ(matrix[0][2], 1);
    ASSERT_EQ(matrix[2][0], 0);

    delete[] matrix;

    delete[] list;
    fclose(file);
}

TEST(GR_AssociationToMatrixTest, SelfLoop) {
    const char* content = "3\n3 0 1 2\n1 1\n0\n";
    // Node 1 has a self-loop and connections to Node 2 and Node 3
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    int** matrix = GR_AssociationToMatrix(list, n);

    ASSERT_EQ(matrix[0][0], 1);
    ASSERT_EQ(matrix[1][1], 1);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;

    GR_DeleteAssociationList(list, n);
    fclose(file);
}

TEST(GR_GetAssociationListTest, TwoWaysConnection) {
    const char* content = "4\n0\n2 2 3\n1 1\n0\n";
    // Node connections: Node 2 -> Node 3 and Node 4; Node 3 -> Node 2
    FILE* file = CreateTempFile(content);

    int n;
    GR_Node_t* list = GR_GetAssociationList(file, &n);

    ASSERT_EQ(n, 4);
    ASSERT_EQ(list[0].connectionCnt, 0);
    ASSERT_EQ(list[1].connectionCnt, 2);
    ASSERT_EQ(list[1].connectedTo[0], 2);
    ASSERT_EQ(list[1].connectedTo[1], 3);
    ASSERT_EQ(list[2].connectionCnt, 1);
    ASSERT_EQ(list[2].connectedTo[0], 1);
    ASSERT_EQ(list[3].connectionCnt, 0);

    GR_DeleteAssociationList(list, n);
    fclose(file);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}