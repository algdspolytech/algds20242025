#include "xorLink.h"

void test() {
    xorList* list = createList();
    add(list, "1");
    add(list, "2");
    printf("Add: "); 
    iter(list); // Should print: 1 2 

    add(list, "y");
    iter(list); // Should print: 1 2 y
    add(list, "\n");

    printf("DelbyK: ");
    delByD(list, "2");
    iter(list);    //Should print : 1 y

    Node* node = createNode(NULL);
    node = find(list, "Hello");
    if (node == NULL) {
        printf("Found: Not found"); // Should print: Found: Not found
    }

    node = find(list, "1");
    if (node != NULL) {
        printf("Found: %s\n", node->data); // Should print: Found: 1
    }
    Node* new_list = createNode("new");
    printf("New list: ");
    iter(&new_list); //Should print: New list: new


    delByAd(&new_list, find(&new_list, "new")->link);
    if (new_list == NULL) {
        printf("delete by Add Ok");// Should print: delete by Add Ok
    }

    list = delByD(list, "y");
    printf("Delete by data with assignment: ");
    iter(list); // Should print: Delete by data with assignment: 1 

    list = add(list, "one");
    printf("Add with assignment: ");
    iter(list); //  Should print: Add with assignment: 1 one

    if (freeList(list) == NULL) {
        printf("del Ok\n"); //  // Should print: del Ok
    }
}
