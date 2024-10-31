#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <graph.c>
#include <gtest/gtest.h>

#define SIZE 1

TEST(nodeTest, initNodeNullCountVertReturnsNull_no1) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    EXPECT_EQ(initNode(1,0,vertices),nullptr);
}

TEST(nodeTest, initNodeEmptyArrayReturnsNull_no2) {
    EXPECT_EQ(initNode(1,SIZE,NULL),nullptr);
}

TEST(nodeTest, initNodeArrayReturnsPtr_no3) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    EXPECT_EQ(node->vertices[0],vertices[0]);
    EXPECT_EQ(node->vertexNumber,1);
    EXPECT_EQ(node->next,nullptr);
    freeNode(node);
}

TEST(listTest, addNodeNullPtrNodeReturnsFalse_no4) {
    AdjacencyList* list=(AdjacencyList*)malloc(sizeof(AdjacencyList));
    list->head=NULL;
    EXPECT_FALSE(addNode(list,NULL));
    free(list);
}

TEST(listTest, addNodeNullListReturnsFalse_no5) {
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    EXPECT_FALSE(addNode(NULL,node));
    freeNode(node);
}

TEST(listTest, addNodeNormalNodeReturnsTrue_no6) {
    AdjacencyList* list=(AdjacencyList*)malloc(sizeof(AdjacencyList));
    list->head=NULL;
    int* vertices=(int*)malloc(SIZE*sizeof(int));
    vertices[0]=1;
    Node* node=initNode(1,SIZE,vertices);
    EXPECT_TRUE(addNode(list,node));
    free(list);
    freeNode(node);
}

TEST(readFileTest, readAdjacencyMatrixNonexistentPathReturnsNull_no7) {
    size_t size;
    EXPECT_EQ(readAdjacencyMatrix("null",&size),nullptr);
}
