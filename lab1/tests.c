#define _CRT_SECURE_NO_WARNINGS


#include <assert.h>
#include "funcs.h"
#include <stdio.h>


void Test_init_file_is_null_No1(void)
{
	assert(init("test.exe"));
	printf("\n���� 1 �������\n");
}

void Test_adding_count_more_than_const_No2(void)
{
	FILE* file = init("data_to_test.txt");
	Full_name people_to_test[MAX_LEN_FILE];

	assert(adding(file, people_to_test));
	printf("\n���� 2 �������\n");
}

void Test_adding_empty_file_No3(void)
{
	FILE* file = init("empty.txt");
	Full_name people_to_test[MAX_LEN_FILE];

	assert(adding(file, people_to_test) == 0);
	printf("���� 3 �������\n");
}

void Test_compare_patronymic_No4(void)
{
	Full_name person1 = { "������", "����", "��������" };
	Full_name person2 = { "������", "����", "���������" };

	assert(compare(&person1, &person2) < 0);
	printf("���� 4 �������\n");
}

void Test_compare_name_No5(void)
{
	Full_name person1 = { "������", "����", "��������" };
	Full_name person2 = { "������", "�������", "���������" };

	assert(compare(&person1, &person2) > 0);
	printf("���� 5 �������\n");
}

void Test_compare_surname_No6(void)
{
	Full_name person1 = { "������", "����", "��������" };
	Full_name person2 = { "������", "�������", "���������" };

	assert(compare(&person1, &person2) > 0);
	printf("���� 6 �������\n");
}

void Test_find_surname_Iv_No7(void)
{
	Full_name people[] =
	{
	   {"������", "����", "��������"},
	   {"������", "����", "��������"},
	   {"�������", "������", "���������"},
	   {"�������", "����", "��������"}
	};
	int count = 4;
	char found_surnames[10][50];
	int found_count;

	found_count = find_testable(people, count, "��", "", "", found_surnames);

	assert(found_count == 2);
	assert(strcmp(found_surnames[0], "������") == 0);
	assert(strcmp(found_surnames[1], "�������") == 0);
	printf("���� 7 �������\n");
}

void Test_find_complete_match_No8(void)
{
	Full_name people[] =
	{
	   {"������", "����", "��������"},
	   {"������", "����", "��������"},
	   {"�������", "������", "���������"},
	   {"�������", "����", "��������"}
	};
	int count = 4;
	char found_surnames[10][50];
	int found_count;

	found_count = find_testable(people, count, "������", "����", "��������", found_surnames);

	assert(found_count == 1);
	assert(strcmp(found_surnames[0], "������") == 0);
	printf("���� 8 �������\n");
}

void Test_find_no_matches_No9(void)
{
	Full_name people[] =
	{
	   {"������", "����", "��������"},
	   {"������", "����", "��������"},
	   {"�������", "������", "���������"},
	   {"�������", "����", "��������"}
	};
	int count = 4;
	char found_surnames[10][50];
	int found_count;

	found_count = find_testable(people, count, "��������", "�������", "����������", found_surnames);

	assert(found_count == 0);
	printf("���� 9 �������\n");
}

void Test_adding_invalid_format_string_No10(void)
{
	FILE* file = fopen("data_to_test10.txt", "w+");
	fprintf(file, "������ ���� ��������\n������������������\n������ ���� ��������\n");
	rewind(file);

	Full_name arr[MAX_LEN_FILE];

	int count = adding(file, arr);
	assert(count == 2);
	printf("���� 10 �������\n");
	remove("test_file_3.txt");
}