#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "labJ.h"

void ht_create_ZeroCapacity_returnNull_no1() {
    HashTable* ht = ht_create(0);
    assert(ht == NULL);
}

void ht_create_ValidCapacity_returnValidVal_no2() {
    HashTable* ht = ht_create(5);
    assert(ht != NULL);
    ht_free(ht);
}

void ht_insert_InsertSingle_returnTrue_no3() {
    HashTable* ht = ht_create(5);
    int result = ht_insert(ht, "abc");
    assert(result == 1);
    ht_free(ht);
}

void ht_insert_InsertDuplicate_returnTrue_no4() {
    HashTable* ht = ht_create(5);
    ht_insert(ht, "abc");
    int result = ht_insert(ht, "abc");
    assert(result == 1);
    ht_free(ht);
}

void ht_insert_InsertUntilFull_returnFalse_no5() {
    HashTable* ht = ht_create(2);
    ht_insert(ht, "a");
    ht_insert(ht, "b");
    int result = ht_insert(ht, "c");
    assert(result == 0);
    ht_free(ht);
}

void ht_search_ExistingElement_returnTrue_no6() {
    HashTable* ht = ht_create(3);
    ht_insert(ht, "cat");
    int result = ht_search(ht, "cat");
    assert(result == 1);
    ht_free(ht);
}

void ht_search_NonExistingElement_returnFalse_no7() {
    HashTable* ht = ht_create(3);
    ht_insert(ht, "dog");
    int result = ht_search(ht, "wolf");
    assert(result == 0);
    ht_free(ht);
}

void ht_search_EmptyTable_returnFalse_no8() {
    HashTable* ht = ht_create(5);
    int result = ht_search(ht, "x");
    assert(result == 0);
    ht_free(ht);
}

void ht_free_ValidTable_returnValidVal_no9() {
    HashTable* ht = ht_create(4);
    ht_insert(ht, "alpha");
    ht_free(ht);
    assert(1); 
}

void ht_insert_StringCollision_returnTrue_no10() {
    HashTable* ht = ht_create(3);
    ht_insert(ht, "Aa");  
    int result = ht_insert(ht, "BB");
    assert(result == 1);
    ht_free(ht);
}

int main() {
    ht_create_ZeroCapacity_returnNull_no1();
    ht_create_ValidCapacity_returnValidVal_no2();
    ht_insert_InsertSingle_returnTrue_no3();
    ht_insert_InsertDuplicate_returnTrue_no4();
    ht_insert_InsertUntilFull_returnFalse_no5();
    ht_search_ExistingElement_returnTrue_no6();
    ht_search_NonExistingElement_returnFalse_no7();
    ht_search_EmptyTable_returnFalse_no8();
    ht_free_ValidTable_returnValidVal_no9();
    ht_insert_StringCollision_returnTrue_no10();

    printf("All tests passed successfully");

    return 0;
}