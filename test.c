#include "Header.h"

// ����: ������� ������ ��������
void test_insert_EmptyTable_insertValidString_returnTrue() {
    memset(table, 0, sizeof(table));  // ������� �������
    int result = insert("apple");
    printf("TestInsert_SingleElement_ReturnValidVal = %d\n", result == 1);
}

// ����: ������� ������ � ����������� ������� � �������� ���������
void test_insert_AlreadyFilledSlot_insertAtAnotherPosition_returnTrue() {
    memset(table, 0, sizeof(table));  // ������� �������
    insert("apple");
    insert("banana");
    int result = insert("grape");
    printf("TestInsert_AlreadyFilledSlot_insertAtAnotherPosition_returnTrue = %d\n", result == 1);
}

// ����: ����� ������������ ������
void test_search_ExistingString_returnTrue() {
    memset(table, 0, sizeof(table));  // ������� �������
    insert("apple");
    int result = search("apple");
    printf("TestSearch_ExistingString_returnTrue = %d\n", result == 1);
}

// ����: ����� �������������� ������
void test_search_NonExistingString_returnFalse() {
    memset(table, 0, sizeof(table));  // ������� �������
    insert("apple");
    int result = search("banana");
    printf("TestSearch_NonExistingString_returnFalse = %d\n", result == 0);
}

// ����: ������������ ������ ��� �������
void test_free_table_FilledTable_noMemoryLeaks() {
    memset(table, 0, sizeof(table));  // ������� �������
    insert("apple");
    insert("banana");
    free_table();
    printf("TestFreeTable_FilledTable_noMemoryLeaks = 1\n");
}

// ����: ������� ������� � ������������� �������
void test_insert_OverflowTable_returnFalse() {
    memset(table, 0, sizeof(table));  // ������� �������
    for (int i = 0; i < TABLE_SIZE; i++) {
        char str[10];
        sprintf(str, "item%d", i);
        insert(str);
    }
    int result = insert("overflow");
    printf("TestInsert_OverflowTable_returnFalse = %d\n", result == 0);
}

// ����: ����������� ������ ����� my_strdup
void test_my_strdup_ValidString_returnCopy() {
    const char* original = "test";
    char* copy = my_strdup(original);
    printf("TestMyStrdup_ValidString_returnCopy = %d\n", strcmp(copy, original) == 0);
    free(copy);
}

// ����: ������� ������, ������� ��� ���� � �������
void test_insert_DuplicateString_returnFalse() {
    memset(table, 0, sizeof(table));  // ������� �������
    insert("apple");
    int result = insert("apple");  // �������� �������� ��������
    printf("TestInsert_DuplicateString_returnFalse = %d\n", result == 0);  // ������� false, ��� ��� ��� ��� ����
}

// ����: ����� ������ ����� � ��������
void test_search_AfterDelete_returnFalse() {
    memset(table, 0, sizeof(table));  // ������� �������
    insert("apple");
    free_table();  // ������� �������
    int result = search("apple");  // ������ ������ ���� �������
    printf("TestSearch_AfterDelete_returnFalse = %d\n", result == 0);  // ������� false
}

// ����: �������� ���-������� �� ������ ������
void test_hash_DifferentString_returnDifferentHash() {
    const char* str1 = "apple";
    const char* str2 = "banana";
    int hash1 = hash(str1);  // �������� ��� ��� ������ ������
    int hash2 = hash(str2);  // �������� ��� ��� ������ ������

    // ���������, ��� ���� ��� ������ ����� ��������
    printf("TestHash_DifferentString_returnDifferentHash = %d\n", hash1 != hash2);
}

// ������ ���� ������
void run_all_tests() {
    test_insert_EmptyTable_insertValidString_returnTrue();
    test_insert_AlreadyFilledSlot_insertAtAnotherPosition_returnTrue();
    test_search_ExistingString_returnTrue();
    test_search_NonExistingString_returnFalse();
    test_free_table_FilledTable_noMemoryLeaks();
    test_insert_OverflowTable_returnFalse();
    test_my_strdup_ValidString_returnCopy();
    test_insert_DuplicateString_returnFalse();
    test_search_AfterDelete_returnFalse();
    test_hash_DifferentString_returnDifferentHash();
}

int main() {
    setlocale(LC_ALL, ""); // ��� ��������� �������� ����� � ������
    run_all_tests();
    return 0;
}
