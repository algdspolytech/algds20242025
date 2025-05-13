#include "hashtable.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void TestCreateEmptyTable_HappyPath_no1() {
    HashTable* table = create_table();
    assert(table != NULL);
    assert(table->size == TABLE_SIZE);
    assert(table->count == 0);
    free_table(table);
    printf("TestCreateEmptyTable_HappyPath_no1: PASSED\n");
}

void TestInsertToEmptyTable_HappyPath_no2() {
    HashTable* table = create_table();
    bool result = insert(table, "first");
    assert(result == true);
    assert(table->count == 1);
    assert(search(table, "first") == true);
    free_table(table);
    printf("TestInsertToEmptyTable_HappyPath_no2: PASSED\n");
}

void TestInsertDuplicate_ErrorCase_no3() {
    HashTable* table = create_table();
    insert(table, "duplicate");
    bool result = insert(table, "duplicate");
    assert(result == false);
    assert(table->count == 1);
    free_table(table);
    printf("TestInsertDuplicate_ErrorCase_no3: PASSED\n");
}

void TestSearchNonExistent_ErrorCase_no4() {
    HashTable* table = create_table();
    assert(search(table, "ghost") == false);
    free_table(table);
    printf("TestSearchNonExistent_ErrorCase_no4: PASSED\n");
}

void TestDeleteExisting_HappyPath_no5() {
    HashTable* table = create_table();
    insert(table, "todelete");
    bool result = delete(table, "todelete");
    assert(result == true);
    assert(table->count == 0);
    assert(search(table, "todelete") == false);
    free_table(table);
    printf("TestDeleteExisting_HappyPath_no5: PASSED\n");
}

void TestDeleteNonExistent_ErrorCase_no6() {
    HashTable* table = create_table();
    bool result = delete(table, "nonexistent");
    assert(result == false);
    free_table(table);
    printf("TestDeleteNonExistent_ErrorCase_no6: PASSED\n");
}

void TestCollisionHandling_HappyPath_no7() {
    HashTable* table = create_table();
    table->size = 2;
    assert(insert(table, "a") == true);
    assert(insert(table, "b") == true);
    assert(table->count == 2);
    assert(search(table, "a") == true);
    assert(search(table, "b") == true);
    free_table(table);
    printf("TestCollisionHandling_HappyPath_no7: PASSED\n");
}

void TestTableFull_ErrorCase_no8() {
    HashTable* table = create_table();
    table->size = 2;
    assert(insert(table, "first") == true);
    assert(insert(table, "second") == true);
    bool result = insert(table, "third");
    assert(result == false);
    free_table(table);
    printf("TestTableFull_ErrorCase_no8: PASSED\n");
}

void TestReuseDeletedSlot_HappyPath_no9() {
    HashTable* table = create_table();
    insert(table, "temp");
    delete(table, "temp");
    assert(insert(table, "reused") == true);
    assert(search(table, "reused") == true);
    assert(table->count == 1);
    free_table(table);
    printf("TestReuseDeletedSlot_HappyPath_no9: PASSED\n");
}

void TestMultipleOperations_ComplexCase_no10() {
    HashTable* table = create_table();
    assert(insert(table, "one") == true);
    assert(insert(table, "two") == true);
    assert(insert(table, "three") == true);
    assert(table->count == 3);
    
    assert(delete(table, "two") == true);
    assert(table->count == 2);
    assert(search(table, "two") == false);
    
    assert(insert(table, "four") == true);
    assert(table->count == 3);
    
    free_table(table);
    printf("TestMultipleOperations_ComplexCase_no10: PASSED\n");
}

int main() {
    TestCreateEmptyTable_HappyPath_no1();
    TestInsertToEmptyTable_HappyPath_no2();
    TestInsertDuplicate_ErrorCase_no3();
    TestSearchNonExistent_ErrorCase_no4();
    TestDeleteExisting_HappyPath_no5();
    TestDeleteNonExistent_ErrorCase_no6();
    TestCollisionHandling_HappyPath_no7();
    TestTableFull_ErrorCase_no8();
    TestReuseDeletedSlot_HappyPath_no9();
    TestMultipleOperations_ComplexCase_no10();
    
    printf("\nAll 10 tests passed successfully!\n");
    return 0;
}