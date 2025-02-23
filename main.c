#include "FunctList.h"
#include <stdio.h>
#include <locale.h>
#pragma warning(disable:4996)

int main() {

	Node* Schedule = read_file("input.txt");
	print_filtered_list(Schedule, 8);
	free_all(&Schedule);

	return 0;
}