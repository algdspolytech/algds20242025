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
}TEST(HashMapTest, CreateDestroy) {
    const unsigned int size = 10;
    struct node** map = createHashMap(size);
    ASSERT_NE(map, nullptr);
    
    // Проверка инициализации buckets
    for (unsigned int i = 0; i < size; ++i) {
        ASSERT_NE(map[i], nullptr);
        EXPECT_EQ(map[i]->key, nullptr);
        EXPECT_EQ(map[i]->value, 0);
        EXPECT_EQ(map[i]->next, nullptr);
    }
    
    deleteHashMap(map, size);
}

TEST(HashMapTest, InsertAndGet) {
    const unsigned int size = 10;
    struct node** map = createHashMap(size);
    ASSERT_NE(map, nullptr);

    // Тест на вставку и получение
    insertValue(map, size, "key1", 42);
    struct node* result = getVal(map, size, "key1");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->key, "key1");
    EXPECT_EQ(result->value, 42);

    // Проверка обновления значения
    insertValue(map, size, "key1", 100);
    result = getVal(map, size, "key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 100);

    deleteHashMap(map, size);
}

TEST(HashMapTest, GetNonExistent) {
    const unsigned int size = 10;
    struct node** map = createHashMap(size);
    ASSERT_NE(map, nullptr);

    struct node* result = getVal(map, size, "nonexistent");
    EXPECT_EQ(result, nullptr);

    deleteHashMap(map, size);
}

TEST(HashMapTest, HandleCollisions) {
    const unsigned int size = 1; 
    struct node** map = createHashMap(size);
    ASSERT_NE(map, nullptr);

    insertValue(map, size, "key1", 1);
    insertValue(map, size, "key2", 2);

    struct node* result1 = getVal(map, size, "key1");
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->value, 1);

    struct node* result2 = getVal(map, size, "key2");
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->value, 2);

    deleteHashMap(map, size);
}

TEST(HashMapDeathTest, InsertEmptyKey) {
    const unsigned int size = 10;
    struct node** map = createHashMap(size);
    ASSERT_NE(map, nullptr);

    EXPECT_DEATH(insertValue(map, size, "", 42), "Assertion.*failed");
    
    deleteHashMap(map, size);
}