#include <gtest/gtest.h>

extern "C" {
#include "HashTable.h"
}

TEST(HashTableTest, InsertInEmptyTest1) {
    HashTable *ht = createHashTable(0);
    addHashTable(ht, "key", "value");
    EXPECT_STREQ(getHashTable(ht, "key"), "value");
    freeHashTable(ht);
}

TEST(HashTableTest, RetrieveNonExistentKeyTest2) {
    HashTable *ht = createHashTable(10);
    addHashTable(ht, "key1", "value1");
    char *value = getHashTable(ht, "nonexistent");
    EXPECT_EQ(value, nullptr);
    freeHashTable(ht);
}

TEST(HashTableTest, DeleteKeyTest3) {
    HashTable *ht = createHashTable(10);
    addHashTable(ht, "key1", "value1");
    int removed = removeHashTable(ht, "key1");
    EXPECT_EQ(removed, 1);
    char *value = getHashTable(ht, "key1");
    EXPECT_EQ(value, nullptr);
    freeHashTable(ht);
}

TEST(HashTableTest, ResizeTest4) {
    HashTable *ht = createHashTable(2);
    addHashTable(ht, "key1", "value1");
    addHashTable(ht, "key2", "value2");
    addHashTable(ht, "key3", "value3");
    EXPECT_TRUE(ht->capacity > 2 && ht->size > 2);
    EXPECT_STREQ(getHashTable(ht, "key1"), "value1");
    EXPECT_STREQ(getHashTable(ht, "key2"), "value2");
    EXPECT_STREQ(getHashTable(ht, "key3"), "value3");
    freeHashTable(ht);
}

TEST(HashTableTest, OverwriteTest5) {
    HashTable *ht = createHashTable(10);
    addHashTable(ht, "key1", "value1");
    addHashTable(ht, "key1", "new_value");
    char *value = getHashTable(ht, "key1");
    EXPECT_STREQ(value, "new_value");
    freeHashTable(ht);
}

TEST(HashTableTest, DeleteAndReinsertTest6) {
    HashTable *ht = createHashTable(10);
    addHashTable(ht, "key1", "value1");
    EXPECT_EQ(removeHashTable(ht, "key1"), 1);
    addHashTable(ht, "key1", "value2");
    char *value = getHashTable(ht, "key1");
    EXPECT_STREQ(value, "value2");
    freeHashTable(ht);
}

TEST(HashTableTest, DeleteNonExistingTest7) {
    HashTable *ht = createHashTable(10);
    addHashTable(ht, "key1", "value1");
    int removed = removeHashTable(ht, "key2");
    EXPECT_FALSE(removed);
    freeHashTable(ht);
}


TEST(HashTableTest, SameHashDifferentKeysTest8) {
    char *collision_key1 = "Ez";
    char *collision_key2 = "FY";

    ASSERT_EQ(djb2_hash(collision_key1), djb2_hash(collision_key2));

    HashTable *ht = createHashTable(5);
    addHashTable(ht, collision_key1, "value1");
    addHashTable(ht, collision_key2, "value2");

    EXPECT_STREQ(getHashTable(ht, collision_key1), "value1");
    EXPECT_STREQ(getHashTable(ht, collision_key2), "value2");

    freeHashTable(ht);
}

TEST(HashTableTest, TombstoneProbeChainTest9) {
    HashTable *ht = createHashTable(7);

    addHashTable(ht, "key1", "val1");
    addHashTable(ht, "key2", "val2");
    addHashTable(ht, "key3", "val3");

    removeHashTable(ht, "key2");

    EXPECT_STREQ(getHashTable(ht, "key1"), "val1");
    EXPECT_STREQ(getHashTable(ht, "key3"), "val3");

    addHashTable(ht, "key4", "val4");
    EXPECT_STREQ(getHashTable(ht, "key4"), "val4");
    EXPECT_STREQ(getHashTable(ht, "key1"), "val1");

    freeHashTable(ht);
}

TEST(HashTableTest, CaseSensitivityTest10) {
    HashTable *ht = createHashTable(5);

    addHashTable(ht, "KEY", "upper");
    addHashTable(ht, "key", "lower");

    EXPECT_STREQ(getHashTable(ht, "KEY"), "upper");
    EXPECT_STREQ(getHashTable(ht, "key"), "lower");
    EXPECT_NE(djb2_hash("KEY"), djb2_hash("key"));

    freeHashTable(ht);
}

TEST(HashTableTest, ResizeAfterDeletionTest11) {
    HashTable *ht = createHashTable(4);

    addHashTable(ht, "key1", "val1");
    addHashTable(ht, "key2", "val2");
    addHashTable(ht, "key3", "val3");

    removeHashTable(ht, "key2");

    EXPECT_STREQ(getHashTable(ht, "key1"), "val1");
    EXPECT_EQ(getHashTable(ht, "key2"), nullptr);
    EXPECT_STREQ(getHashTable(ht, "key3"), "val3");

    addHashTable(ht, "key4", "val4");

    EXPECT_GT(ht->capacity, 4);
    EXPECT_STREQ(getHashTable(ht, "key1"), "val1");
    EXPECT_EQ(getHashTable(ht, "key2"), nullptr);
    EXPECT_STREQ(getHashTable(ht, "key3"), "val3");
    EXPECT_STREQ(getHashTable(ht, "key4"), "val4");

    freeHashTable(ht);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
