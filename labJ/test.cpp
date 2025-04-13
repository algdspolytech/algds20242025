#include "hash_table.h"
#include <assert.h>
#include <stdio.h>

node_t* test_table[TABLE_SIZE];

void reset_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        node_t* current = test_table[i];
        while (current) {
            node_t* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        test_table[i] = NULL;
    }
}

void TestAddToEmptyTable_no1() {
    reset_table();
    addNode(test_table, "apple");
    assert(findNode(test_table, "apple") == 1);
    printf("TestAddToEmptyTable_no1 passed\n");
}

void TestAddTwoDifferent_no2() {
    reset_table();
    addNode(test_table, "apple");
    addNode(test_table, "banana");
    assert(findNode(test_table, "apple"));
    assert(findNode(test_table, "banana"));
    printf("TestAddTwoDifferent_no2 passed\n");
}

void TestFindExisting_no3() {
    reset_table();
    addNode(test_table, "cat");
    assert(findNode(test_table, "cat"));
    printf("TestFindExisting_no3 passed\n");
}

void TestFindNonExisting_no4() {
    reset_table();
    assert(findNode(test_table, "ghost") == 0);
    printf("TestFindNonExisting_no4 passed\n");
}

void TestDeleteExisting_no5() {
    reset_table();
    addNode(test_table, "delete_me");
    deleteNode(test_table, "delete_me");
    assert(findNode(test_table, "delete_me") == 0);
    printf("TestDeleteExisting_no5 passed\n");
}

void TestDeleteNonExisting_no6() {
    reset_table();
    deleteNode(test_table, "not_here");
    assert(1); 
    printf("TestDeleteNonExisting_no6 passed\n");
}

void TestAddDuplicate_no7() {
    reset_table();
    addNode(test_table, "dup");
    addNode(test_table, "dup");
    int count = 0;
    node_t* list = test_table[hash("dup")];
    while (list) {
        if (strcmp(list->key, "dup") == 0) count++;
        list = list->next;
    }
    assert(count == 1);
    printf("TestAddDuplicate_no7 passed\n");
}

void TestCollision_no8() {
    reset_table();
    addNode(test_table, "abc"); // hash = sum('a','b','c') = 294
    addNode(test_table, "cab"); // hash = sum('c','a','b') = 294
    unsigned int index = hash("abc");
    assert(test_table[index] != NULL);
    assert(test_table[index]->next != NULL);
    printf("TestCollision_no8 passed\n");
}

void TestDeleteFromChain_no9() {
    reset_table();
    addNode(test_table, "abc");
    addNode(test_table, "cab"); 
    deleteNode(test_table, "cab");
    assert(findNode(test_table, "abc"));
    assert(findNode(test_table, "cab") == 0);
    printf("TestDeleteFromChain_no9 passed\n");
}

void TestDeleteTailInChain_no10() {
    reset_table();
    addNode(test_table, "abc");
    addNode(test_table, "cab");
    deleteNode(test_table, "abc"); 
    assert(findNode(test_table, "cab"));
    assert(findNode(test_table, "abc") == 0);
    printf("TestDeleteTailInChain_no10 passed\n");
}

void TestAddDeleteAdd_no11() {
    reset_table();
    addNode(test_table, "temp");
    deleteNode(test_table, "temp");
    addNode(test_table, "temp");
    assert(findNode(test_table, "temp"));
    printf("TestAddDeleteAdd_no11 passed\n");
}

void TestEmptyTable_no12() {
    reset_table();
    for (int i = 0; i < TABLE_SIZE; i++) {
        assert(test_table[i] == NULL);
    }
    printf("TestEmptyTable_no12 passed\n");
}

void TestLongString_no13() {
    reset_table();
    char longstr[MAX_LEN];
    memset(longstr, 'x', MAX_LEN - 1);
    longstr[MAX_LEN - 1] = '\0';
    addNode(test_table, longstr);
    assert(findNode(test_table, longstr));
    printf("TestLongString_no13 passed\n");
}


void TestMassiveAdd_no14() {
    reset_table();
    for (int i = 0; i < 1000; i++) {
        char buffer[32];
        sprintf(buffer, "word%d", i);
        addNode(test_table, buffer);
    }

    for (int i = 0; i < 1000; i++) {
        char buffer[32];
        sprintf(buffer, "word%d", i);
        assert(findNode(test_table, buffer));
    }

    printf("TestMassiveAdd_no16 passed\n");
}

int main() {
    TestAddToEmptyTable_no1();
    TestAddTwoDifferent_no2();
    TestFindExisting_no3();
    TestFindNonExisting_no4();
    TestDeleteExisting_no5();
    TestDeleteNonExisting_no6();
    TestAddDuplicate_no7();
    TestCollision_no8();
    TestDeleteFromChain_no9();
    TestDeleteTailInChain_no10();
    TestAddDeleteAdd_no11();
    TestEmptyTable_no12();
    TestLongString_no13();
    TestMassiveAdd_no14();
    return 0;
}
