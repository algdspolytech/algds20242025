#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <graph.c>
#include <gtest/gtest.h>

#define FILENAME "../input.txt"
#define SIZE 1

TEST(nodeTest, initNodeNullCountVertReturnsNull_no1) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    EXPECT_EQ(initNode(1,0,vertices),nullptr);
}

TEST(nodeTest, initNodeEmptyArrayReturnsNull_no2) {
    EXPECT_EQ(initNode(1,SIZE,NULL),nullptr);
}

TEST(nodeTest, freeNodeNormalNodeNoMemLeaks_no3) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    freeNode(node);
    SUCCEED();
}

TEST(nodeTest, initNodeArrayReturnsPtr_no4) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    EXPECT_EQ(node->vertices[0],vertices[0]);
    EXPECT_EQ(node->vertexNumber,1);
    EXPECT_EQ(node->next,nullptr);
    freeNode(node);
}

TEST(listTest, addNodeNullPtrNodeReturnsFalse_no5) {
    AdjacencyList* list=(AdjacencyList*)malloc(sizeof(AdjacencyList));
    list->head=NULL;
    EXPECT_FALSE(addNode(list,NULL));
    free(list);
}

TEST(listTest, addNodeNullListReturnsFalse_no6) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    EXPECT_FALSE(addNode(NULL,node));
    freeNode(node);
}

TEST(listTest, addNodeNormalNodeReturnsTrue_no7) {
    AdjacencyList* list=(AdjacencyList*)malloc(sizeof(AdjacencyList));
    list->head=NULL;
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    EXPECT_TRUE(addNode(list,node));
    free(list);
    freeNode(node);
}

TEST(listTest, addNodeAddNodesReturnsTrue_no8) {
    AdjacencyList* list=(AdjacencyList*)malloc(sizeof(AdjacencyList));
    list->head=NULL;
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    Node* node_2=initNode(2,SIZE,vertices);
    EXPECT_TRUE(addNode(list,node));
    EXPECT_TRUE(addNode(list,node_2));
    free(list);
    freeNode(node);
    freeNode(node_2);
}

TEST(readFileTest, readAdjacencyMatrixNonexistentPathReturnsNull_no9) {
    size_t size;
    EXPECT_EQ(readAdjacencyMatrix("null",&size),nullptr);
}

TEST(matrixTest, freeMatrixNormalMatrixNoMemLeaks_no10) {
    size_t size;
    int** matrix = readAdjacencyMatrix(FILENAME,&size);
    freeMatrix(matrix,size);
    SUCCEED();
}

TEST(graphTest, freeGraphNormalGraphNoMemLeaks_no11) {
    Graph* gr=initGraph(FILENAME);
    freeGraph(gr);
    SUCCEED();
}
