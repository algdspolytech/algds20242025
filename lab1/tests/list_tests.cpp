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

TEST(listTest, getWordOfLengthEmptyListReturnsNull_no3) {
    List* list = NULL;
    EXPECT_EQ(getWordOfLength(list, 1), nullptr);
}

TEST(listTest, getWordOfLengthZeroLenReturnsNull_no4) {
    List* list = (List*)malloc(sizeof(List));
    list->head=NULL;
    addSorted(list,"s");
    EXPECT_EQ(getWordOfLength(list, 0), nullptr);
    freeList(list);
    free(list);
}

TEST(listTest, getWordOfLengthHasWordReturnsPtr_no5) {
    List* list = (List*)malloc(sizeof(List));
    list->head=NULL;
    addSorted(list,"s");
    EXPECT_STREQ(getWordOfLength(list, 1)->chars, "s");
    freeList(list);
    free(list);
}

TEST(listTest, getWordOfLengthHasntWordReturnsNull_no6) {
    List* list = (List*)malloc(sizeof(List));
    list->head=NULL;
    addSorted(list,"s");
    EXPECT_EQ(getWordOfLength(list, 2), nullptr);
    freeList(list);
    free(list);
}

TEST(listTest, hasWordOfLengthHasWordReturnsTrue_no7) {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list, "a");
    EXPECT_TRUE(hasWordOfLength(list, 1));
    freeList(list);
    free(list);
}

TEST(listTest, hasWordOfLengthHasntWordReturnsFalse_no8) {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list, "a");
    EXPECT_FALSE(hasWordOfLength(list, 2));
    freeList(list);
    free(list);
}

TEST(listTest, addSortedAddSingleWordReturnsNothing_no9) {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list, "a");
    ASSERT_NE(list->head, nullptr);
    EXPECT_EQ(list->head->countChars, 1);
    EXPECT_STREQ(list->head->chars, "a");
    freeList(list);
    free(list);
}

TEST(listTest, addSortedAddMultipleWordsReturnsNothing_no10) {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list, "a");
    addSorted(list, "k");
    ASSERT_NE(list->head, nullptr);
    EXPECT_STREQ(list->head->chars, "a");
    EXPECT_STREQ(list->head->next->chars, "k");
    freeList(list);
    free(list);
}

TEST(listTest, addSortedAddZeroLenReturnsNothing_no11) {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list, "");
    ASSERT_EQ(list->head, nullptr);
    freeList(list);
    free(list);
}

TEST(listTest, addSortedAddNullPtrReturnsNothing_no12) {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    addSorted(list, NULL);
    ASSERT_EQ(list->head, nullptr);
    freeList(list);
    free(list);
}
