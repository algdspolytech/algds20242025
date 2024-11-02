#define _CRT_SECURE_NO_WARNINGS

#include "funcs.h"

FILE* init(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Ошибка открытия файла");
		return;
	}

	return file;
}


int compare(const void* a, const void* b)
{
    Full_name* personA = (Full_name*)a;
    Full_name* personB = (Full_name*)b;

    int SurnameCmp = strcmp(personA->surname, personB->surname);
    if (SurnameCmp != 0) {
        return SurnameCmp;
    }

    int NameCmp = strcmp(personA->name, personB->name);
    if (NameCmp != 0) {
        return NameCmp;
    }

    return strcmp(personA->patronymic, personB->patronymic);
}



int adding(FILE* file, Full_name* arr)
{
	int count = 0;

	while (fscanf(file, "%s %s %s", arr[count].surname, arr[count].name, arr[count].patronymic) == 3)
	{
		count++;
		if (count >= MAX_LEN_FILE)
		{
			printf("Достигнут предел записей");
			break;
		}
	}

	fclose(file);

	return count;
}


void find(Full_name* people, int count)
{
	Full_name fullname;
	scanf("%s %s %s", fullname.surname, fullname.name, fullname.patronymic);
	fullname.patronymic[strcspn(fullname.patronymic, "\n")] = '\0';

	printf("Íàéäåííûå ÔÈÎ:\n");
	for (int i = 0; i < count; i++)
	{
		if ((fullname.surname[0] == '\0' || strstr(people[i].surname, fullname.surname) == people[i].surname) &&
			(fullname.name[0] == '\0' || strstr(people[i].name, fullname.name) == people[i].name) &&
			(fullname.patronymic[0] == '\0' || strstr(people[i].patronymic, fullname.patronymic) == people[i].patronymic))
		{
			printf("%s\n", people[i].surname);
		}
	}
	return;
}


int find_testable(Full_name* people, int count, const char* surname, const char* name, const char* patronymic, char found_surnames[][50])
{
	int found_count = 0;

	for (int i = 0; i < count; i++)
	{
		if ((surname[0] == '\0' || strstr(people[i].surname, surname) == people[i].surname) &&
			(name[0] == '\0' || strstr(people[i].name, name) == people[i].name) &&
			(patronymic[0] == '\0' || strstr(people[i].patronymic, patronymic) == people[i].patronymic))
		{
			strcpy(found_surnames[found_count++], people[i].surname);
		}
	}

	return found_count;
}
