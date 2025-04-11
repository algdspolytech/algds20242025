#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int ASSERT_EQ(long long expected, long long actual, const char* message, char* test_name) {
    if (expected != actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %lld, Actual: %lld\n", expected, actual);
        return 0;
    }
    return 1;
}

int ASSERT_NE(long long expected, long long actual, const char* message, char* test_name) {
    if (expected == actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %lld, Actual: %lld\n", expected, actual);
        return 0;
    }
    return 1;
}

void print_result_testing(int status, char* test_name) {
    if (status) {
        printf("%s - Success\n", test_name);
    }
    else {
        printf("%s - Failed\n", test_name);
    }
}

int Test_CreateTable_no1() {
    HashTable* table = create_table();
    int status = 1;
    status *= ASSERT_EQ(table->size, TABLE_SIZE, "table->size should be TABLE_SIZE", "Test_CreateTable_no1");
    status *= ASSERT_EQ(table->count, 0, "table->count should be 0", "Test_CreateTable_no1");
    status *= ASSERT_NE((long long)table->items, (long long)NULL, "table->items should not be NULL", "Test_CreateTable_no1");
    free_table(table);
    print_result_testing(status, "Test_CreateTable_no1");
    return status;
}

int Test_InsertSingle_no2() {
    HashTable* table = create_table();
    int result = insert(table, "test");
    int status = 1;
    status *= ASSERT_EQ(result, 1, "insert should return 1", "Test_InsertSingle_no2");
    status *= ASSERT_EQ(table->count, 1, "table->count should be 1", "Test_InsertSingle_no2");
    free_table(table);
    print_result_testing(status, "Test_InsertSingle_no2");
    return status;
}

int Test_InsertDuplicate_no3() {
    HashTable* table = create_table();
    insert(table, "test");
    int result = insert(table, "test");
    int status = 1;
    status *= ASSERT_EQ(result, 0, "insert duplicate should return 0", "Test_InsertDuplicate_no3");
    status *= ASSERT_EQ(table->count, 1, "table->count should still be 1", "Test_InsertDuplicate_no3");
    free_table(table);
    print_result_testing(status, "Test_InsertDuplicate_no3");
    return status;
}

int Test_SearchExisting_no4() {
    HashTable* table = create_table();
    insert(table, "test");
    int index = search(table, "test");
    int status = 1;
    status *= ASSERT_NE(index, -1, "search should return valid index", "Test_SearchExisting_no4");
    status *= ASSERT_EQ(strcmp(table->items[index].str, "test"), 0, "found string should match", "Test_SearchExisting_no4");
    free_table(table);
    print_result_testing(status, "Test_SearchExisting_no4");
    return status;
}

int Test_SearchNonExisting_no5() {
    HashTable* table = create_table();
    insert(table, "test");
    int index = search(table, "other");
    int status = 1;
    status *= ASSERT_EQ(index, -1, "search should return -1 for non-existing", "Test_SearchNonExisting_no5");
    free_table(table);
    print_result_testing(status, "Test_SearchNonExisting_no5");
    return status;
}

int Test_DeleteExisting_no6() {
    HashTable* table = create_table();
    insert(table, "test");
    int result = delete(table, "test");
    int status = 1;
    status *= ASSERT_EQ(result, 1, "delete should return 1", "Test_DeleteExisting_no6");
    status *= ASSERT_EQ(table->count, 0, "table->count should be 0", "Test_DeleteExisting_no6");
    status *= ASSERT_EQ(search(table, "test"), -1, "search should return -1 after delete", "Test_DeleteExisting_no6");
    free_table(table);
    print_result_testing(status, "Test_DeleteExisting_no6");
    return status;
}

int Test_DeleteNonExisting_no7() {
    HashTable* table = create_table();
    int result = delete(table, "test");
    int status = 1;
    status *= ASSERT_EQ(result, 0, "delete should return 0 for non-existing", "Test_DeleteNonExisting_no7");
    free_table(table);
    print_result_testing(status, "Test_DeleteNonExisting_no7");
    return status;
}

int Test_MultipleInserts_no8() {
    HashTable* table = create_table();
    int status = 1;
    status *= ASSERT_EQ(insert(table, "test1"), 1, "insert test1 should return 1", "Test_MultipleInserts_no8");
    status *= ASSERT_EQ(insert(table, "test2"), 1, "insert test2 should return 1", "Test_MultipleInserts_no8");
    status *= ASSERT_EQ(insert(table, "test3"), 1, "insert test3 should return 1", "Test_MultipleInserts_no8");
    status *= ASSERT_EQ(table->count, 3, "table->count should be 3", "Test_MultipleInserts_no8");
    free_table(table);
    print_result_testing(status, "Test_MultipleInserts_no8");
    return status;
}

int Test_InsertAfterDelete_no9() {
    HashTable* table = create_table();
    insert(table, "test");
    delete(table, "test");
    int result = insert(table, "new");
    int status = 1;
    status *= ASSERT_EQ(result, 1, "insert after delete should return 1", "Test_InsertAfterDelete_no9");
    status *= ASSERT_EQ(table->count, 1, "table->count should be 1", "Test_InsertAfterDelete_no9");
    free_table(table);
    print_result_testing(status, "Test_InsertAfterDelete_no9");
    return status;
}

int Test_FreeTable_no10() {
    HashTable* table = create_table();
    insert(table, "test1");
    insert(table, "test2");
    free_table(table);
    int status = 1;
    print_result_testing(status, "Test_FreeTable_no10");
    return status;
}

int main() {
    int result_testing = 1;
    result_testing *= Test_CreateTable_no1();
    result_testing *= Test_InsertSingle_no2();
    result_testing *= Test_InsertDuplicate_no3();
    result_testing *= Test_SearchExisting_no4();
    result_testing *= Test_SearchNonExisting_no5();
    result_testing *= Test_DeleteExisting_no6();
    result_testing *= Test_DeleteNonExisting_no7();
    result_testing *= Test_MultipleInserts_no8();
    result_testing *= Test_InsertAfterDelete_no9();
    result_testing *= Test_FreeTable_no10();

    if (result_testing == 1) {
        printf("All tests passed!\n");
    }
    else {
        printf("Some tests failed\n");
    }
    return 0;
}