#include "gtest/gtest.h"
#include "memallocator.h"
#include <cstdlib>

TEST(MemAllocatorTest, Initialization) {
    int pool_size = 1024;
    void* pool = malloc(pool_size);
    ASSERT_NE(pool, nullptr);

    ASSERT_EQ(meminit(pool, pool_size), 1);

    memdone();
    free(pool);
}

TEST(MemAllocatorTest, AllocationAndFree) {
    int pool_size = 1024;
    void* pool = malloc(pool_size);
    ASSERT_NE(pool, nullptr);

    meminit(pool, pool_size);

    void* ptr1 = memalloc(128);
    ASSERT_NE(ptr1, nullptr);

    void* ptr2 = memalloc(256);
    ASSERT_NE(ptr2, nullptr);

    memfree(ptr1);
    memfree(ptr2);

    memdone();
    free(pool);
}

TEST(MemAllocatorTest, MinimumSizeCheck) {
    ASSERT_GE(memgetminimumsize(), sizeof(MemoryBlock));
}

TEST(MemAllocatorTest, BlockSizeCheck) {
    ASSERT_EQ(memgetblocksize(), sizeof(MemoryBlock));
}

TEST(MemAllocatorTest, AllocationTooLarge) {
    int pool_size = 1024;
    void* pool = malloc(pool_size);
    ASSERT_NE(pool, nullptr);

    meminit(pool, pool_size);

    void* ptr = memalloc(2000); // Запрос больше доступной памяти
    ASSERT_EQ(ptr, nullptr);

    memdone();
    free(pool);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}