#include <check.h>
#include <stdlib.h>
#include "HashTable.h"

HashTable* table = NULL;

void setup(void) {
    table = create_hash_table(TABLE_SIZE);
}

void teardown(void) {
    free_hash_table(table);
}

START_TEST(test_create_free) {
    ck_assert_ptr_nonnull(table);
    ck_assert_int_eq(table->size, TABLE_SIZE);
    ck_assert_int_eq(table->count, 0);
}
END_TEST

START_TEST(test_insert_search) {
    insert_with_brent(table, "test_key");
    ck_assert_int_eq(search(table, "test_key") >= 0, 1);
    ck_assert_int_eq(search(table, "nonexistent") == -1, 1);
    ck_assert_int_eq(table->count, 1);
}
END_TEST

START_TEST(test_delete) {
    insert_with_brent(table, "to_delete");
    ck_assert_int_eq(search(table, "to_delete") >= 0, 1);
    del(table, "to_delete");
    ck_assert_int_eq(search(table, "to_delete") == -1, 1);
    ck_assert_int_eq(table->count, 0);
}
END_TEST

START_TEST(test_collisions) {
    insert_with_brent(table, "abc");
    insert_with_brent(table, "bca");
    insert_with_brent(table, "cab");
    
    ck_assert_int_eq(search(table, "abc") >= 0, 1);
    ck_assert_int_eq(search(table, "bca") >= 0, 1);
    ck_assert_int_eq(search(table, "cab") >= 0, 1);
    ck_assert_int_eq(table->count, 3);
}
END_TEST

START_TEST(test_duplicates) {
    insert_with_brent(table, "duplicate");
    insert_with_brent(table, "duplicate");
    ck_assert_int_eq(table->count, 1);
}
END_TEST

START_TEST(test_performance) {
    const int NUM_ITEMS = TABLE_SIZE / 2;
    char key[20];
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        sprintf(key, "key%d", i);
        insert_with_brent(table, key);
    }
    
    ck_assert_int_eq(table->count, NUM_ITEMS);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        sprintf(key, "key%d", i);
        ck_assert_int_eq(search(table, key) != 0, 1);
    }
}
END_TEST

Suite* hashtable_suite(void) {
    Suite* s;
    TCase* tc_core;
    TCase* tc_limits;

    s = suite_create("HashTable");

    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_create_free);
    tcase_add_test(tc_core, test_insert_search);
    tcase_add_test(tc_core, test_delete);
    tcase_add_test(tc_core, test_collisions);
    tcase_add_test(tc_core, test_duplicates);
    suite_add_tcase(s, tc_core);

    tc_limits = tcase_create("Limits");
    tcase_add_checked_fixture(tc_limits, setup, teardown);
    tcase_add_test(tc_limits, test_performance);
    suite_add_tcase(s, tc_limits);

    return s;
}

int main(void) {
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = hashtable_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}