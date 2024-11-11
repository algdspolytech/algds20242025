#define _CRT_SECURE_NO_WARNINGS

#include "funcs.h"

#include "tests.h"

#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif


int main()
{
	setlocale(LC_ALL, "Russian");

	Full_name people[MAX_LEN_FILE];
	
	FILE* file = init("data.txt");

	int n = adding(file, people);
	if (n < 0)
	{
		return 1;
	}

	qsort(people, n, sizeof(Full_name), compare);

	for (int i = 0; i < n; i++)
	{
		printf("%s\n", people[i].surname);
	}

	// 2 part
	printf("Введите первые буквы ФИО, которое хотите найти:\n");

#ifdef _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif

	find(people, n);

	// Tests
	printf("Тесты:\n\n");

	Test_init_file_is_null_No1();
	Test_adding_count_more_than_const_No2();
	Test_adding_empty_file_No3();
	Test_compare_patronymic_No4();
	Test_compare_name_No5();
	Test_compare_surname_No6();
	Test_find_surname_Iv_No7();
	Test_find_complete_match_No8();
	Test_find_no_matches_No9();
	Test_adding_invalid_format_string_No10();

	
	return 0;
}
