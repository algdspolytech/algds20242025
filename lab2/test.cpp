#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <string>
#include "main.h"
using namespace std;

string readFileToString(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << std::endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TEST(GeneralTests, testForInit) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = 100;
    initMatrix(graph);
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            ASSERT_EQ(graph->matrix[i][j], 0);
        }
    }
    freeMatrix(graph);
}
TEST(GeneralTests, testForOutput) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = 4;
    initMatrix(graph);
    FILE* file = fopen("test.txt", "w");
    printMatrix(graph, file);
    fclose(file);
    string expectedOutput = "0 0 0 0 \n0 0 0 0 \n0 0 0 0 \n0 0 0 0 \n";
    string actualOutput = readFileToString("test.txt");
    ASSERT_EQ(expectedOutput, actualOutput);
    remove("test.txt");
    freeMatrix(graph);
}
TEST(GeneralTests, testForCopy) {
    int size = 900;
    int* row = (int*)malloc(sizeof(int) * size);
    int* input = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) input[i] = i * i;

    copyRow(row, input, size);
    for (int i = 0; i < size; ++i) ASSERT_EQ(row[i], input[i]);
}


TEST(GraphTests, normalGraph) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "4\n");
    fprintf(input, "1: 2 3\n");
    fprintf(input, "2: 1 4\n");
    fprintf(input, "3: 1 4\n");
    fprintf(input, "4: 2 3\n");
    fclose(input);

    input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(input);
    fclose(output);

    string expectedOutput = "0 1 1 0 \n1 0 0 1 \n1 0 0 1 \n0 1 1 0 \n";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("input.txt");
    remove("output.txt");
}
TEST(GraphTests, emptyGraph) {
    FILE* input = fopen("input.txt", "w");
    FILE* output = fopen("output.txt", "w");
    fprintf(input, "0\n");
    fclose(input);

    input = fopen("input.txt", "r");
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(output);
    fclose(input);

    string expectedOutput = "";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("input.txt");
    remove("output.txt");
}
TEST(GraphTests, SingleVertex) {
    FILE* input = fopen("input.txt", "w");
    FILE* output = fopen("output.txt", "w");
    fprintf(input, "1\n");
    fprintf(input, "1: 1\n");
    fclose(input);
    input = fopen("input.txt", "r");

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(input);
    fclose(output);

    string expectedOutput = "1 \n";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("input.txt");
    remove("output.txt");
}



TEST(GraphTests, oneWayGraph) {
    FILE* input = fopen("input.txt", "w");
    FILE* output = fopen("output.txt", "w");
    fprintf(input, "5\n");
    fprintf(input, "1: 2\n");
    fprintf(input, "2: 1, 3\n");
    fprintf(input, "3: 2, 4\n");
    fprintf(input, "4: 3, 5\n");
    fprintf(input, "5: 4\n");
    fclose(input);
    input = fopen("input.txt", "r");

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(input);
    fclose(output);

    string expectedOutput = "0 1 0 0 0 \n1 0 1 0 0 \n0 1 0 1 0 \n0 0 1 0 1 \n0 0 0 1 0 \n";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("input.txt");
    remove("output.txt");
}

TEST(GraphTests, manyVertex) {
    FILE* input = fopen("input.txt", "w");
    FILE* output = fopen("output.txt", "w");
    fprintf(input, "100\n");
    for (int i = 1; i < 101; ++i) fprintf(input, "%d:\n", i);
    fclose(input);
    input = fopen("input.txt", "r");

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(input);
    fclose(output);

    string expectedOutput;
    string zeros;
    for (int i = 0; i < 100; ++i) zeros += "0 ";
    for (int i = 0; i < 100; ++i) expectedOutput += zeros + "\n";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("output.txt");
}

TEST(GraphTests, allLinedGraph) {
    FILE* input = fopen("input.txt", "w");
    FILE* output = fopen("output.txt", "w");
    fprintf(input, "7\n");
    fprintf(input, "1: 7 2 3 4 5 6\n");
    fprintf(input, "2: 1 7 3 4 5 6\n");
    fprintf(input, "3: 1 2 7 4 5 6\n");
    fprintf(input, "4: 1 2 3 7 5 6\n");
    fprintf(input, "5: 1 2 3 4 7 6\n");
    fprintf(input, "6: 1 2 3 4 5 7\n");
    fprintf(input, "7: 1 2 3 4 5 6\n");
    fclose(input);
    input = fopen("input.txt", "r");

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(input);
    fclose(output);

    string expectedOutput = 
        "0 1 1 1 1 1 1 \n"
        "1 0 1 1 1 1 1 \n" 
        "1 1 0 1 1 1 1 \n"
        "1 1 1 0 1 1 1 \n"
        "1 1 1 1 0 1 1 \n"
        "1 1 1 1 1 0 1 \n"
        "1 1 1 1 1 1 0 \n";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("input.txt");
    remove("output.txt");
}

TEST(GraphTest, AllLinedAndCycledGraph) {
    FILE* input = fopen("input.txt", "w");
    FILE* output = fopen("output.txt", "w");
    fprintf(input, "7\n");
    fprintf(input, "1: 1 2 3 4 5 6 7\n");
    fprintf(input, "2: 1 2 3 4 5 6 7\n");
    fprintf(input, "3: 1 2 3 4 5 6 7\n");
    fprintf(input, "4: 1 2 3 4 5 6 7\n");
    fprintf(input, "5: 1 2 3 4 5 6 7\n");
    fprintf(input, "6: 1 2 3 4 5 6 7\n");
    fprintf(input, "7: 1 2 3 4 5 6 7\n");
    fclose(input);
    input = fopen("input.txt", "r");

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    readList(graph, input);
    printMatrix(graph, output);
    fclose(input);
    fclose(output);

    string expectedOutput = 
        "1 1 1 1 1 1 1 \n"
        "1 1 1 1 1 1 1 \n" 
        "1 1 1 1 1 1 1 \n"
        "1 1 1 1 1 1 1 \n"
        "1 1 1 1 1 1 1 \n"
        "1 1 1 1 1 1 1 \n"
        "1 1 1 1 1 1 1 \n";
    string actualOutput = readFileToString("output.txt");
    ASSERT_EQ(expectedOutput, actualOutput);

    freeMatrix(graph);
    remove("input.txt");
    remove("output.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
