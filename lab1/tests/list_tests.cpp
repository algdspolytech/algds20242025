#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <list.c>
#include <gtest/gtest.h>

TEST(nodeTest, initNodeNullCharsReturnsNull_no1) {
    EXPECT_EQ(initNode(NULL, NULL), nullptr);
}

TEST(nodeTest, initNodeEmptyStringReturnsNull_no2) {
    EXPECT_EQ(initNode("", NULL), nullptr);
}

TEST(nodeTest, initNodeEmptyStringReturnsNull_no3) {
    Node* node = initNode("abcd", NULL);
    printNode(node);
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list,"aaa");
    addSorted(list,"b");
    addSorted(list,"baa");
    printLongerWords(list,1);
    EXPECT_EQ(initNode("", NULL), nullptr);
}
