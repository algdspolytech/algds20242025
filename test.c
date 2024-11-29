#include "Header.h"

int Assert_eq(int val1, int val2)
{
	if (val1 != val2)
		return 0;
	return 1;
}


void CheckMethod() {
    tree* root = NULL;
    int k = 3;

    addElement(&root, 5); addElement(&root, 3);
    addElement(&root, 7); addElement(&root, 2);
    addElement(&root, 4); addElement(&root, 6);
              addElement(&root, 8);

    int count = 0;
    int result = 0;

   findKthSmallest(root, k, &count, &result);

    int res = 1;
	res &= Assert_eq(result, 4);

	if (res) printf("Test1  passed\n");
	else     printf("Test1  failed\n");

}

void Test(){
    tree* root = NULL;
    int k = 5;

   addElement(&root, 12);
   addElement(&root, 11);
   addElement(&root, 10);
   addElement(&root, 9);
   addElement(&root, 8);
   addElement(&root, 6);
   addElement(&root, 7);
              
    int count = 0;
    int result = 0;
    findKthSmallest(root, k, &count, &result);

    int res = 1;
	res &= Assert_eq(result, 10);

	if (res) printf("Test2  passed\n");
	else     printf("Test2  failed\n");

}

void test_insert_into_empty_tree() {
    tree* root = NULL;

    addElement(&root, 5);
    int res = 1;
	res &= Assert_eq(root->data, 5);

	if (res) printf("Test3  passed\n");
	else     printf("Test3  failed\n");
}

void test_findKthSmallest_in_empty_tree() {
    tree* root = NULL;
    int k = 1;
    int count = 0;
    int result = 0;

    findKthSmallest(root, k, &count, &result);

    int res = 1;
	res &= Assert_eq(result, 0);

	if (res) printf("Test4  passed\n");
	else     printf("Test4  failed\n");
}

void test_findKthSmallest_k_greater_than_tree_size() {
    tree* root = NULL;
    int k = 10;

    addElement(&root, 5);
    addElement(&root, 3);
    addElement(&root, 7);
    addElement(&root, 2);
    addElement(&root, 4);
    addElement(&root, 6);
    addElement(&root, 8);

    int count = 0;
    int result = 0;

    findKthSmallest(root, k, &count, &result);

    int res = 1;
	res &= Assert_eq(result, 0);

	if (res) printf("Test5  passed\n");
	else     printf("Test5  failed\n");
}
void test_findKthSmallest_k_equals_() {
    tree* root = NULL;
    int k = 1;

    addElement(&root, 5);
    addElement(&root, 3);
    addElement(&root, 7);
    addElement(&root, 2);
    addElement(&root, 4);
    addElement(&root, 6);
    addElement(&root, 8);

    int count = 0;
    int result = 0;

    findKthSmallest(root, k, &count, &result);

     int res = 1;
	res &= Assert_eq(result, 2);

	if (res) printf("Test6 passed\n");
	else     printf("Test6  failed\n");

}



int main() {
    CheckMethod();
    Test();
    test_insert_into_empty_tree();
    test_findKthSmallest_in_empty_tree();
    test_findKthSmallest_k_greater_than_tree_size();
    test_findKthSmallest_k_equals_();
    
    return 0;
}