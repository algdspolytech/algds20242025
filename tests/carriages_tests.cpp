#include <cstdio>
#include <stdlib.h>
#include <carriages.c>
#include <gtest/gtest.h>

TEST(TopologicalSortTest, TopologicalSortBasicSortingValid) {
    int inDegrees[] = {0, 1, 1, 0};
    Pair pairs[] = {{0, 1}, {0, 2}, {1, 3}};
    int sortedOrder[4];
    int sortedCount = 0;

    topologicalSort(inDegrees, pairs, 3, 4, sortedOrder, &sortedCount);

    EXPECT_EQ(sortedCount, 4);
    EXPECT_TRUE(sortedOrder[0] == 0 || sortedOrder[1] == 0 || sortedOrder[2] == 0 || sortedOrder[3] == 0);
}


TEST(WriteFileTest, WriteFileValidOutput) {
    const char* filename = "output_test.txt";
    writeFile(filename);
    FILE* file = fopen(filename, "r");
    EXPECT_NE(file, nullptr);
    fclose(file);
    remove(filename);
}

TEST(WriteFileTest, WriteFileCheckOutputContent) {
    const char* filename = "output_test.txt";
    writeFile(filename);

    FILE* file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    EXPECT_STRNE(buffer, "");
    remove(filename);
}

TEST(MemoryTest, AllocateCarriages) {
    int countCarriages = 5;
    Carriage* carriages = (Carriage*)malloc(sizeof(Carriage) * countCarriages);
    EXPECT_NE(carriages, nullptr);
    free(carriages);
}

TEST(MemoryTest, AllocatePairs) {
    int countPairs = 5;
    Pair* pairs = (Pair*)malloc(sizeof(Pair) * countPairs);
    EXPECT_NE(pairs, nullptr);
    free(pairs);
}
