#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "..\LabJ\hash_table.h"
}

class HashTableTest : public ::testing::Test {
protected:
    HashTable* ht;
    void SetUp() override {
        ht = create_table(5, 0.7);
        ASSERT_NE(ht, nullptr);
        ASSERT_EQ(get_hash_table_count(ht), 0);
        ASSERT_EQ(get_hash_table_deleted_count(ht), 0);
    }

    void TearDown() override {
        destroy_table(ht);
    }
};


TEST_F(HashTableTest, HashTableCreationAndDestruction_no1) {
    ASSERT_GT(get_hash_table_size(ht), 0);
    ASSERT_EQ(get_hash_table_count(ht), 0);
    ASSERT_EQ(get_hash_table_deleted_count(ht), 0);
}

TEST_F(HashTableTest, InsertSingleElement_no2) {
    EXPECT_EQ(insert(ht, "apple"), 0);
    EXPECT_EQ(get_hash_table_count(ht), 1);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 0);
    EXPECT_STREQ(search(ht, "apple"), "apple");
}

TEST_F(HashTableTest, SearchNonExistingElement_no3) {
    insert(ht, "apple");
    EXPECT_EQ(search(ht, "banana"), nullptr);
}

TEST_F(HashTableTest, InsertDuplicateElement_no4) {
    insert(ht, "apple");
    EXPECT_EQ(insert(ht, "apple"), 1);
    EXPECT_EQ(get_hash_table_count(ht), 1);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 0);
    EXPECT_STREQ(search(ht, "apple"), "apple");
}

TEST_F(HashTableTest, DeleteExistingElement_no5) {
    insert(ht, "banana");
    EXPECT_EQ(delete_key(ht, "banana"), 0);
    EXPECT_EQ(get_hash_table_count(ht), 0);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 1);
    EXPECT_EQ(search(ht, "banana"), nullptr);
}

TEST_F(HashTableTest, DeleteNonExistingElement_no6) {
    insert(ht, "grape");
    EXPECT_EQ(delete_key(ht, "orange"), -1);
    EXPECT_EQ(get_hash_table_count(ht), 1);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 0);
}

TEST_F(HashTableTest, InsertElementsWithCollisions_no7) {
    EXPECT_EQ(insert(ht, "apple"), 0);
    EXPECT_EQ(insert(ht, "banana"), 0);
    EXPECT_EQ(insert(ht, "cherry"), 0);
    EXPECT_EQ(insert(ht, "date"), 0);

    EXPECT_EQ(get_hash_table_count(ht), 4);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 0);
    EXPECT_EQ(get_hash_table_size(ht), 11);

    EXPECT_STREQ(search(ht, "apple"), "apple");
    EXPECT_STREQ(search(ht, "banana"), "banana");
    EXPECT_STREQ(search(ht, "cherry"), "cherry");
    EXPECT_STREQ(search(ht, "date"), "date");

    EXPECT_EQ(insert(ht, "elderberry"), 0);
    EXPECT_EQ(insert(ht, "fig"), 0);
    EXPECT_EQ(get_hash_table_count(ht), 6);
    EXPECT_STREQ(search(ht, "elderberry"), "elderberry");
    EXPECT_STREQ(search(ht, "fig"), "fig");
}

TEST_F(HashTableTest, RehashingTriggered_no8) {
    EXPECT_EQ(insert(ht, "key1"), 0);
    EXPECT_EQ(insert(ht, "key2"), 0);
    EXPECT_EQ(insert(ht, "key3"), 0);
    int old_size = get_hash_table_size(ht);
    EXPECT_EQ(insert(ht, "key4"), 0);
    int new_size = get_hash_table_size(ht);

    EXPECT_GT(new_size, old_size);
    EXPECT_EQ(new_size, 11);

    EXPECT_EQ(get_hash_table_count(ht), 4);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 0);

    EXPECT_STREQ(search(ht, "key1"), "key1");
    EXPECT_STREQ(search(ht, "key2"), "key2");
    EXPECT_STREQ(search(ht, "key3"), "key3");
    EXPECT_STREQ(search(ht, "key4"), "key4");
}


TEST_F(HashTableTest, EmptyTableDelete_no9) {
    EXPECT_EQ(delete_key(ht, "any_key"), -1);
    EXPECT_EQ(get_hash_table_count(ht), 0);
    EXPECT_EQ(get_hash_table_deleted_count(ht), 0);
}

TEST(HashTableEdgeCases, NullParameters_no10) {
    HashTable* null_ht = nullptr;
    EXPECT_EQ(insert(null_ht, "test"), -1);
    EXPECT_EQ(insert(create_table(10, 0.7), nullptr), -1);
    EXPECT_EQ(create_table(0, 0.7), nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}