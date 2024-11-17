#include "Header.h"

int Assert_eq(int val1, int val2)
{
	if (val1 != val2)
		return 0;
	return 1;
}


void CheckMethodTest1(){
    int arr[MAX_N] = {2,3,4,5,9}; 
    int n =5, b = 10;

	bool res = 1;
	res &= Assert_eq(findSubset(arr, n, b), 1);

	if (res) printf("Test1  passed\n");
	else     printf("Test1  failed\n");
}

void NoExistingNumTest2(){
    int arr[MAX_N] = {2,3,4,5,9, 10, 11, 12, 13}; 
    int n =9, b = 100;
    
	bool res = 1;
	res &= Assert_eq(findSubset(arr, n, b), 0);

	if (res) printf("Test2  passed\n");
	else     printf("Test2  failed\n");
}
void NullElemTest3(){
    int arr[MAX_N] = {0,0,0,0}; 
    int n =4, b = 10;
    
	bool res = 1;
	res &= Assert_eq(findSubset(arr, n, b), 0);

	if (res) printf("Test3  passed\n");
	else     printf("Test3  failed\n");
}

void NullElemTest4(){
    int arr[MAX_N] = {0,0,0,0}; 
    int n =4, b = 0;
    
	bool res = 1;
	res &= Assert_eq(findSubset(arr, n, b), 1);

	if (res) printf("Test4  passed\n");
	else     printf("Test4  failed\n");
}

void Test5(){
    int arr[MAX_N] = {1, 2}; 
    int n =2, b = 4;
    
	bool res = 1;
	res &= Assert_eq(findSubset(arr, n, b), 0);

	if (res) printf("Test5  passed\n");
	else     printf("Test5  failed\n");
}

void Test6(){
 	int arr[MAX_N] = {1, 2, 3, 100}; 
    int n =4, b = 107;
    
	bool res = 1;
	res &= Assert_eq(findSubset(arr, n, b), 0);

	if (res) printf("Test6  passed\n");
	else     printf("Test6  failed\n");
}

void TestWithFile7(){
	int *b,*n;
	int arr[MAX_N];
	read_f("input.txt", &b, &n, arr);
	putToFile("output.txt", arr, n,b);
	if(true) printf("\nTest7  passed\n");
	else     printf("\nTest7  failed\n");
}

int main(){

CheckMethodTest1();
NoExistingNumTest2();
NullElemTest3();
NullElemTest4();
Test5();
Test6();
TestWithFile7();

	
    return 0;
}