#include "xor_linked_list.h"

void test() {
    Node* test_list = NULL;

    test_list = add(test_list, "one");
    test_list = add(test_list, "two");
    test_list = add(test_list, "three");
    printf("Test Add: ");
    iterate(test_list); // Should print: one two three

    test_list = deleteByKey(test_list, "two");
    printf("Test Delete by Key: ");
    iterate(test_list); // Should print: one three

    Node* found = find(test_list, "three");
    printf("Test Find: ");
    if (found != NULL) printf("Found: %s\n", found->data); // Should print: Found: three

    found = find(test_list, "four");
    printf("Test Find Non-existent: ");
    if (found == NULL) printf("Not found: four\n"); // Should print: Not found: four

    Node* empty_list = NULL;
    printf("Empty list iteration: ");
    iterate(empty_list); // Should print nothing
    empty_list = add(empty_list, "first");
    printf("Add to Empty List: ");
    iterate(empty_list); // Should print: first

    empty_list = deleteByKey(empty_list, "first");
    printf("Delete Only Element: ");
    iterate(empty_list); // Should print nothing

    test_list = deleteByKey(test_list, "one");
    test_list = deleteByKey(test_list, "one");
    printf("Test Delete Similar: ");
    iterate(test_list); // Should print: three two

    test_list = deleteByKey(test_list, "non-existent");
    printf("Test Delete Non-existent: ");
    iterate(test_list); // Should print: three two

    test_list = add(test_list, "one");
    test_list = add(test_list, "two");
    printf("Test Add Similar: ");
    iterate(test_list); // Should print: one three one two

    
}

//int main() {
//    test();
//    return 0;
//}