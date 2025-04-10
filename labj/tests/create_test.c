#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../include/hash_table.h"

#define SIZE 10

hash_table *table = NULL;

void setup(void) { table = create_table(SIZE); }

void teardown(void) {
  if (table) {
    free_table(table);
  }
}

TestSuite(hash_table, .init = setup, .fini = teardown);

Test(hash_table, creation) {
  cr_assert_not_null(table, "Table creation failed");
  cr_assert_eq(table->size, SIZE, "Wrong table size");

  for (int i = 0; i < SIZE; i++) {
    cr_assert_null(table->buckets[i], "Bucket %d not NULL after creation", i);
  }
}

Test(hash_table, basic_insert_search) {
    insert(table, "test_key");
    cr_assert_eq(search(table, "test_key"), 1, "Key not found after insertion");
    cr_assert_eq(search(table, "non_existent"), 0, "Found non-existent key");
}

Test(hash_table, collision_handling) {
    insert(table, "abc");
    insert(table, "cba");
    
    cr_assert_eq(search(table, "abc"), 1, "First collision element not found");
    cr_assert_eq(search(table, "cba"), 1, "Second collision element not found");
}

Test(hash_table, deletion) {
    insert(table, "to_delete");
    cr_assert_eq(search(table, "to_delete"), 1, "Key not inserted");
    
    delete(table, "to_delete");
    cr_assert_eq(search(table, "to_delete"), 0, "Key still exists after deletion");
}

Test(hash_table, delete_from_chain) {
    insert(table, "a");
    insert(table, "b");
    insert(table, "c");
    
    delete(table, "b");
    cr_assert_eq(search(table, "a"), 1, "First element broken after delete");
    cr_assert_eq(search(table, "b"), 0, "Deleted element still exists");
    cr_assert_eq(search(table, "c"), 1, "Last element broken after delete");
}

Test(hash_table, duplicate_insert) {
    insert(table, "duplicate");
    insert(table, "duplicate");
    
    unsigned long idx = hash_func("duplicate", SIZE);
    int count = 0;
    node *current = table->buckets[idx];
    while (current) {
        count++;
        current = current->next;
    }
    cr_assert_eq(count, 1, "Duplicate inserted multiple times");
}
