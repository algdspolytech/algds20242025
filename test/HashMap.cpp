#include <gtest/gtest.h>

extern "C"
{
    #include "hashmap.h"
}

TEST(HashTableTest, InsertAndRetrieve) {
    const unsigned int size = 10;
    node** map = createHashMap(size);
    insertValue(map, size, "key1", 42);
    node* result = getVal(map, size, "key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 42);
    deleteHashMap(map, size);
}

TEST(HashTableTest, HandleCollision) {
    const unsigned int size = 1;
    node** map = createHashMap(size);
    insertValue(map, size, "ab", 1);
    insertValue(map, size, "ba", 2);
    node* first = getVal(map, size, "ab");
    node* second = getVal(map, size, "ba");
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(first->value, 1);
    EXPECT_EQ(second->value, 2);
    deleteHashMap(map, size);
}

TEST(HashTableTest, MultipleInserts) {
    const unsigned int size = 5;
    node** map = createHashMap(size);
    for (int i = 0; i < 5; ++i) {
        std::string key = "key" + std::to_string(i);
        insertValue(map, size, const_cast<char*>(key.c_str()), i);
    }
    for (int i = 0; i < 5; ++i) {
        std::string key = "key" + std::to_string(i);
        node* result = getVal(map, size, key.c_str());
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->value, i);
    }
    deleteHashMap(map, size);
}

TEST(HashTableTest, MissingKeyDeathTest) {
    const unsigned int size = 10;
    node** map = createHashMap(size);
    EXPECT_DEATH({
        getVal(map, size, "missing_key");
    }, "");
    deleteHashMap(map, size);
}

TEST(HashTableTest, HashFunction) {
    unsigned int size = 100;
    const char* key = "test";
    unsigned int expected = ('t' + 'e' + 's' + 't') % size;
    EXPECT_EQ(hash(key, size), expected);
}

TEST(HashTableTest, OverwriteKey) {
    const unsigned int size = 10;
    node** map = createHashMap(size);
    insertValue(map, size, "key", 1);
    insertValue(map, size, "key", 2);
    node* first = getVal(map, size, "key");
    ASSERT_NE(first->next, nullptr);
    EXPECT_EQ(first->next->value, 2);
    deleteHashMap(map, size);
}

TEST(HashTableTest, InsertEmptyKey) {
    const unsigned int size = 10;
    node** map = createHashMap(size);
    EXPECT_DEATH({
        insertValue(map, size, "", 123);
        getVal(map, size, "");
    }, "");
    deleteHashMap(map, size);
}

TEST(HashTableTest, LargeMap) {
    const unsigned int size = 1000;
    node** map = createHashMap(size);
    for (int i = 0; i < 100; ++i) {
        std::string key = "key" + std::to_string(i);
        insertValue(map, size, const_cast<char*>(key.c_str()), i);
    }
    for (int i = 0; i < 100; ++i) {
        std::string key = "key" + std::to_string(i);
        node* result = getVal(map, size, key.c_str());
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->value, i);
    }
    deleteHashMap(map, size);
}

TEST(HashTableTest, ChainOrder) {
    const unsigned int size = 1;
    node** map = createHashMap(size);
    insertValue(map, size, "a", 1);
    insertValue(map, size, "b", 2);
    node* head = map[0];
    ASSERT_NE(head->next, nullptr);
    EXPECT_EQ(head->next->value, 1);
    ASSERT_NE(head->next->next, nullptr);
    EXPECT_EQ(head->next->next->value, 2);
    deleteHashMap(map, size);
}

TEST(HashTableTest, DeleteMap) {
    const unsigned int size = 10;
    node** map = createHashMap(size);
    ASSERT_NO_FATAL_FAILURE(deleteHashMap(map, size));
}