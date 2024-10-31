#include "xor_linked_list.h"


int main() {
    Node* list = NULL;
    list = add(list, "alpha\0");
    list = add(list, "beta\0");
    list = add(list, "gamma\0");

    iterate(list); // Should print: alpha beta gamma

    Node* found = find(list, "beta\0");
    if (found != NULL) printf("Found: %s\n", found->data); // Should print: Found: beta

    list = deleteByKey(list, "beta\0");
    iterate(list); // Should print: alpha gamma

    found = find(list, "beta\0");
    if (found == NULL) printf("Not found: beta\n"); // Should print: Not found: beta

    list = deleteNode(list, list);
    iterate(list); // Should print: gamma

    return 0;
}