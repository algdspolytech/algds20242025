#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_NAMES 100
#define MAX_LENGTH 50

typedef struct Person
{
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    char patronymic[MAX_LENGTH];
    struct Person *next;
} Person;

//Функция для создания нового узла списка
Person *CreatePerson(const char *surname, const char *name, const char *patronymic)
{
    Person *NewPerson = (Person *)malloc(sizeof(Person));

    if (NewPerson == NULL)
    {
        perror("Ошибка выделения памяти");
        return 1;
    }

    strcpy(NewPerson->name, name);
    strcpy(NewPerson->surname, surname);
    strcpy(NewPerson->patronymic, patronymic);

    NewPerson->next = NULL;
    return NewPerson;
}

int compare_names(const char *a, const char *b)
{
    Person *person_a = (Person *)a;
    Person *person_b = (Person *)b;

    if (person_a == NULL || person_b == NULL)
    {
        printf("Нечего сравнивать");
    }

    // Сравниваем фамилии
    int cmp = strcmp(person_a->surname, person_b->surname);
    if (cmp != 0)
    {
        return cmp;
    }

    // Если фамилии одинаковы, сравниваем имена
    cmp = strcmp(person_a->name, person_b->name);
    if (cmp != 0)
    {
        return cmp;
    }

    // Если имена тоже одинаковы, сравниваем отчества
    return strcmp(person_a->patronymic, person_b->patronymic);
}

//Функция добавления узла в отсортированный список
void addPersonSorted(Person **head, const char *surname, const char *name, const char *patronymic)
{
    Person *NewPerson = CreatePerson(surname, name, patronymic);

    if (*head == NULL || compare_names((*head), NewPerson) > 0)
    {
        NewPerson->next = *head;
        *head = NewPerson;
    }

    else
    {
        Person *current = *head;
        while (current->next != NULL && (compare_names(NewPerson, current->next)))
        {
            current = current->next;
        }
        NewPerson->next = current->next;
        current->next = NewPerson;
    }
}

//Функция для вывода списка фамилий
void PrintSurnames(Person *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->surname);
        head = head->next;
    }
}

//Функция для поиска по начальным буквам
char *SearchByInitials(Person *head, const char *surnameInit, const char *nameInit, const char *patronymicInit)
{
    const char result[256];
    strcpy(result, "");
    int found = 0;
    while (head != NULL)
    {
        if ((surnameInit[0] == '\0' || strncmp(head->surname, surnameInit, strlen(surnameInit)) == 0) &&
            (nameInit[0] == '\0' || strncmp(head->name, nameInit, strlen(nameInit)) == 0) &&
            (patronymicInit[0] == '\0' || strncmp(head->patronymic, patronymicInit, strlen(patronymicInit)) == 0))
        {
            strcat(result, head->surname);
            strcat(result, " ");
            strcat(result, head->name);
            strcat(result, " ");
            strcat(result, head->patronymic);
            strcat(result, "\n");
            found = 1;
        }
        head = head->next;
    }

    if (!found)
    {
        strcpy(result, "Нет совпадений.\n");
    }

    return result;
}

void test_comare_names_if_no_patr()
{
    assert(compare_names("Ivanov Ivan Ivanovich", "Ibanov Ivan") == -1);
}

void testCompare_names_norm()
{
    assert(compare_names("Lukashev Artem Romanovich", "Abyshov Mikail Shamilevich") == -1);
}

void test_compareNames_ident()
{
    assert(compare_names("Ivanov Ivan Ivanovich", "Ivanov Ivan Ivanovich") == 0);
}

void test_CreatePerson_norm()
{
    char surname[50] = "Иванов";
    char name[50] = "Иван";
    char patronymic[50] = "Иванович";

    Person *testing = CreatePerson(surname, name, patronymic);

    assert(strcmp(testing->surname, surname) == 0);
    assert(strcmp(testing->name, name) == 0);
    assert(strcmp(testing->patronymic, patronymic) == 0);
}

void test_CreatePerson_noPatr()
{
    char surname[50] = "Иванов";
    char name[50] = "Иван";

    Person *testing = CreatePerson(surname, name, "");

    assert(strcmp(testing->surname, surname) == 0);
    assert(strcmp(testing->name, name) == 0);
    assert(strcmp(testing->patronymic, "") == 0);
}

void test_compare_names_surname_only()
{
    Person *person_a = CreatePerson("Петров", "Алексей", "Александрович");
    Person *person_b = CreatePerson("Иванов", "Иван", "Иванович");

    assert(compare_names(person_a, person_b) > 0);

    free(person_a);
    free(person_b);
}

void test_addPersonSorted_first()
{
    Person *head = NULL;
    addPersonSorted(&head, "Иванов", "Иван", "Иванович");

    assert(strcmp(head->surname, "Иванов") == 0);
    assert(strcmp(head->name, "Иван") == 0);
    assert(strcmp(head->patronymic, "Иванович") == 0);

    free(head);
}

void test_addPersonSorted_middle()
{
    Person *head = NULL;
    addPersonSorted(&head, "Иванов", "Иван", "Иванович");
    addPersonSorted(&head, "Петров", "Петр", "Петрович");
    addPersonSorted(&head, "Сидоров", "Сидор", "Сидорович");

    assert(strcmp(head->next->surname, "Петров") == 0);
    assert(strcmp(head->surname, "Иванов") == 0);

    while (head != NULL)
    {
        Person *temp = head;
        head = head->next;
        free(temp);
    }
}

void test_SearchByInitials_found()
{

    Person *head = CreatePerson("Ivanov", "Ivan", "Ivanovich");
    head->next = CreatePerson("Petrov", "Petr", "Petrovich");
    head->next->next = CreatePerson("Sidorov", "Sidor", "Sidorovich");

    char *result = SearchByInitials(head, "I", "I", "I");
    assert(strcmp(result, "Ivanov Ivan Ivanovich\n") == 0);

    free(head);
}

void test_SearchByInitials_notfound()
{

    Person *head = CreatePerson("Ivanov", "Ivan", "Ivanovich");
    head->next = CreatePerson("Petrov", "Petr", "Petrovich");
    head->next->next = CreatePerson("Sidorov", "Sidor", "Sidorovich");

    char *result = SearchByInitials(head, "A", "A", "A");
    assert(strcmp(result, "Ivanov Ivan Ivanovich\n") != 0);
    assert(strcmp(result, "Petrov Petr Petrovich\n") != 0);
    assert(strcmp(result, "Sidorov Sidor Sidorovich\n") != 0);

    free(head);
}

void runTests()
{
    test_comare_names_if_no_patr();
    testCompare_names_norm();
    test_compareNames_ident();
    test_CreatePerson_norm();
    test_CreatePerson_noPatr();
    test_compare_names_surname_only();
    test_addPersonSorted_first();
    test_addPersonSorted_middle();
    test_SearchByInitials_found();
    test_SearchByInitials_notfound();
}

int main()
{

    setlocale(LC_CTYPE, "Russian");

    runTests();

    Person *head = NULL;
    FILE *file = fopen("List1.txt", "r");
    if (!file)
    {
        perror("Не удалось открыть файл");
        return 1;
    }

    char surname[50], name[50], patronymic[50];
    while (fscanf(file, "%49s %49s %49s", surname, name, patronymic) == 3)
    {
        addPersonSorted(&head, surname, name, patronymic);
    }
    fclose(file);

    printf("Список фамилий:\n");
    PrintSurnames(head);

    char surnameInit[50], nameInit[50], patronymicInit[50];
    printf("Введите инициалы через пробел (фамилия имя отчество): ");
    scanf("%49s %49s %49s", surnameInit, nameInit, patronymicInit);

    printf("Результаты поиска:\n");
    printf("%s", SearchByInitials(head, surnameInit, nameInit, patronymicInit, 0));

    // Освобождение памяти
    while (head != NULL)
    {
        Person *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
