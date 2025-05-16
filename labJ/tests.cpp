#include <gtest/gtest.h>

extern "C" {
    #include "hash_table.h"
}

TEST(HashTableTest, CreateDestroy) {
    HashTable* table = ht_create(10);
    ASSERT_TRUE(table != NULL);
    EXPECT_EQ(table->size, 0);
    EXPECT_EQ(table->capacity, 10);
    ht_destroy(table);
}

TEST(HashTableTest, InsertSearch) {
    HashTable* table = ht_create(5);

    ASSERT_TRUE(ht_insert(table, "key1", "value1"));
    ASSERT_TRUE(ht_insert(table, "key2", "value2"));

    EXPECT_STREQ(ht_search(table, "key1"), "value1");
    EXPECT_STREQ(ht_search(table, "key2"), "value2");
    EXPECT_EQ(ht_search(table, "key3"), nullptr);

    ht_destroy(table);
}

TEST(HashTableTest, InsertDuplicate) {
    HashTable* table = ht_create(5);

    ASSERT_TRUE(ht_insert(table, "key1", "value1"));
    ASSERT_TRUE(ht_insert(table, "key1", "value2")); // Обновление

    EXPECT_STREQ(ht_search(table, "key1"), "value2");
    EXPECT_EQ(table->size, 1);

    ht_destroy(table);
}

TEST(HashTableTest, Delete) {
    HashTable* table = ht_create(5);

    ht_insert(table, "key1", "value1");
    ht_insert(table, "key2", "value2");

    EXPECT_TRUE(ht_delete(table, "key1"));
    EXPECT_EQ(ht_search(table, "key1"), nullptr);
    EXPECT_EQ(table->size, 1);

    EXPECT_FALSE(ht_delete(table, "key3")); // Несуществующий ключ

    ht_destroy(table);
}

TEST(HashTableTest, CollisionHandling) {
    HashTable* table = ht_create(1); // Все попадет в один бакет для теста коллизий

    ASSERT_TRUE(ht_insert(table, "key1", "value1"));
    ASSERT_TRUE(ht_insert(table, "key2", "value2"));

    EXPECT_STREQ(ht_search(table, "key1"), "value1");
    EXPECT_STREQ(ht_search(table, "key2"), "value2");
    EXPECT_EQ(table->size, 2);

    ht_destroy(table);
}

TEST(HashTableTest, NullInputs) {
    HashTable* table = ht_create(5);

    EXPECT_FALSE(ht_insert(NULL, "key", "value"));
    EXPECT_FALSE(ht_insert(table, NULL, "value"));
    EXPECT_FALSE(ht_insert(table, "key", NULL));

    EXPECT_EQ(ht_search(NULL, "key"), nullptr);
    EXPECT_EQ(ht_search(table, NULL), nullptr);

    EXPECT_FALSE(ht_delete(NULL, "key"));
    EXPECT_FALSE(ht_delete(table, NULL));

    ht_destroy(table);
}

TEST(HashTableTest, LargeInput) {
    HashTable* table = ht_create(100);
    const int count = 1000;

    for (int i = 0; i < count; i++) {
        char key[20], value[20];
        snprintf(key, sizeof(key), "key%d", i);
        snprintf(value, sizeof(value), "value%d", i);
        ASSERT_TRUE(ht_insert(table, key, value));
    }

    EXPECT_EQ(table->size, count);

    for (int i = 0; i < count; i++) {
        char key[20], expected_value[20];
        snprintf(key, sizeof(key), "key%d", i);
        snprintf(expected_value, sizeof(expected_value), "value%d", i);
        const char* value = ht_search(table, key);
        ASSERT_TRUE(value != NULL);
        EXPECT_STREQ(value, expected_value);
    }

    ht_destroy(table);
}

TEST(HashTableTest, EmptyStrings) {
    HashTable* table = ht_create(5);

    ASSERT_TRUE(ht_insert(table, "", "empty key"));
    ASSERT_TRUE(ht_insert(table, "empty value", ""));

    EXPECT_STREQ(ht_search(table, ""), "empty key");
    EXPECT_STREQ(ht_search(table, "empty value"), "");

    ht_destroy(table);
}

TEST(HashTableTest, SpecialCharacters) {
    HashTable* table = ht_create(5);

    const char* special_key = "!@#$%^&*()";
    const char* special_value = "\n\t\r\\\"'";

    ASSERT_TRUE(ht_insert(table, special_key, special_value));
    EXPECT_STREQ(ht_search(table, special_key), special_value);

    ht_destroy(table);
}

TEST(HashTableTest, MemoryAllocationFailure) {
    // Тест может быть нестабильным, так как зависит от окружения
    HashTable* table = ht_create(0x7FFFFFFF); // Очень большая таблица
    EXPECT_EQ(table, nullptr);

    ht_destroy(table);
}