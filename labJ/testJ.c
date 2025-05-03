#include "testJ.h"
#include "labJ.h"
#include <assert.h>

void TestInsert_EmptyTable_ReturnSuccess() {
    free_table(); // Сброс предыдущего состояния
    assert(insert("test") == 1);
    assert(search("test") == 1);
}

void TestInsert_DuplicateKey_ReturnFailure() {
    free_table();
    insert("apple");
    assert(insert("apple") == 0);
}

void TestSearch_NonExistentKey_ReturnFailure() {
    free_table();
    assert(search("ghost") == 0);
}

void TestDelete_ExistingKey_ReturnSuccess() {
    free_table();
    insert("data");
    assert(del("data") == 1);
    assert(search("data") == 0);
}

void TestDelete_NonExistentKey_ReturnFailure() {
    free_table();
    assert(del("nothing") == 0);
}

void TestCollisionHandling_TwoKeysSameHash_ReturnBothExist() {
    free_table();
    // Подбираем строки с одинаковым хешом
    const char* key1 = "abc";
    const char* key2 = "cba"; // Предполагаем коллизию для hash()

    insert(key1);
    insert(key2);

    assert(search(key1) == 1);
    assert(search(key2) == 1);
}

void TestFullTable_InsertBeyondCapacity_ReturnFailure() {
    free_table();
    // Заполняем таблицу
    for(int i = 0; i < TABLE_SIZE; i++) {
        char str[20];
        sprintf(str, "key%d", i);
        assert(insert(str) == 1);
    }
    assert(insert("overflow") == 0);
}

void TestReuseDeletedSlot_InsertAfterDelete_ReturnSuccess() {
    free_table();
    insert("first");
    del("first");
    assert(insert("second") == 1);
    assert(search("second") == 1);
}

void TestFreeTable_ClearMemory_AllSlotsEmpty() {
    insert("temp1");
    insert("temp2");
    free_table();

    for(int i = 0; i < TABLE_SIZE; i++) {
        assert(table[i] == NULL);
    }
}

void TestComplexScenario_MultipleOperations_ReturnConsistent() {
    free_table();
    // Серия операций
    insert("start");
    insert("middle");
    insert("end");

    assert(del("middle") == 1);
    assert(search("start") == 1);
    assert(search("end") == 1);
    assert(insert("new") == 1);
    assert(del("non-existent") == 0);
}

void test() {
    TestInsert_EmptyTable_ReturnSuccess();
    TestInsert_DuplicateKey_ReturnFailure();
    TestSearch_NonExistentKey_ReturnFailure();
    TestDelete_ExistingKey_ReturnSuccess();
    TestDelete_NonExistentKey_ReturnFailure();
    TestCollisionHandling_TwoKeysSameHash_ReturnBothExist();
    TestFullTable_InsertBeyondCapacity_ReturnFailure();
    TestReuseDeletedSlot_InsertAfterDelete_ReturnSuccess();
    TestFreeTable_ClearMemory_AllSlotsEmpty();
    TestComplexScenario_MultipleOperations_ReturnConsistent();

    printf("\nAll hash table tests passed successfully!\n");
}