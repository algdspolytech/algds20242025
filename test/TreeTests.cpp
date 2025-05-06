#include <gtest/gtest.h>
extern "C" {
#include "hash_table.h"
}

TEST(HashTableTest, InsertAndSearch) {
    ht_init();
    ASSERT_EQ(ht_insert("apple"), HT_OK);
    ASSERT_EQ(ht_search("apple"), HT_OK);
    ht_free();
}

TEST(HashTableTest, InsertDuplicate) {
    ht_init();
    ASSERT_EQ(ht_insert("banana"), HT_OK);
    ASSERT_EQ(ht_insert("banana"), HT_ALREADY_EXISTS);
    ht_free();
}

TEST(HashTableTest, SearchNotFound) {
    ht_init();
    ASSERT_EQ(ht_search("missing"), HT_NOT_FOUND);
    ht_free();
}

TEST(HashTableTest, DeleteExisting) {
    ht_init();
    ht_insert("carrot");
    ASSERT_EQ(ht_delete("carrot"), HT_OK);
    ASSERT_EQ(ht_search("carrot"), HT_NOT_FOUND);
    ht_free();
}

TEST(HashTableTest, DeleteNonExisting) {
    ht_init();
    ASSERT_EQ(ht_delete("ghost"), HT_NOT_FOUND);
    ht_free();
}

TEST(HashTableTest, InsertAfterDelete) {
    ht_init();
    ht_insert("date");
    ht_delete("date");
    ASSERT_EQ(ht_insert("date"), HT_OK);
    ht_free();
}

TEST(HashTableTest, TableFull) {
    ht_init();
    int filled = 0;
    char buf[16];
    for (int i = 0; i < TABLE_SIZE; ++i) {
        snprintf(buf, sizeof(buf), "key%d", i);
        if (ht_insert(buf) == HT_OK) filled++;
    }
    ASSERT_EQ(filled, TABLE_SIZE);
    ASSERT_EQ(ht_insert("overflow"), HT_FULL);
    ht_free();
}

TEST(HashTableTest, CollisionHandling) {
    ht_init();
    ht_insert("abc");
    ht_insert("acb");  // likely to collide
    ASSERT_EQ(ht_search("abc"), HT_OK);
    ASSERT_EQ(ht_search("acb"), HT_OK);
    ht_free();
}

TEST(HashTableTest, LongString) {
    ht_init();
    char long_str[MAX_STRING_LEN];
    memset(long_str, 'a', MAX_STRING_LEN - 1);
    long_str[MAX_STRING_LEN - 1] = '\0';
    ASSERT_EQ(ht_insert(long_str), HT_OK);
    ASSERT_EQ(ht_search(long_str), HT_OK);
    ht_free();
}

TEST(HashTableTest, StressInsertDelete) {
    ht_init();
    char key[16];
    for (int i = 0; i < 50; ++i) {
        snprintf(key, sizeof(key), "s%d", i);
        ht_insert(key);
    }
    for (int i = 0; i < 50; ++i) {
        snprintf(key, sizeof(key), "s%d", i);
        ASSERT_EQ(ht_delete(key), HT_OK);
    }
    for (int i = 0; i < 50; ++i) {
        snprintf(key, sizeof(key), "s%d", i);
        ASSERT_EQ(ht_search(key), HT_NOT_FOUND);
    }
    ht_free();
}
