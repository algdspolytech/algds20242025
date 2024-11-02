
#include "func_lab1.h"


typedef struct Person
{
    char name[50];
    char surname[50];
    char patronymic[50];
    struct Person *next;
} Person;

Person *Create_Person(char *surname, char *name, char *patronymic)
{
    Person *NewPerson = (Person*)malloc(sizeof(Person));

    if (NewPerson == NULL) {
        return NULL;
    }

    strcpy(NewPerson->name, name);
    strcpy(NewPerson->surname, surname);
    strcpy(NewPerson->patronymic, patronymic);

    NewPerson->next = NULL;
    return NewPerson;
}

int Compare_Names(Person *person_first, Person *person_second)
{
    if (person_first == NULL || person_second == NULL) {
        return -1; 
    }

    if (strcmp(person_second->surname, "") == 0 && strcmp(person_second->name, "") == 0) {
      return -1;
    }
  

    int cmp = strcmp(person_first->surname, person_second->surname);
    if (cmp != 0) {
        return cmp;
    }

    cmp = strcmp(person_first->name, person_second->name);
    if (cmp != 0) {
        return cmp;
    }

    return strcmp(person_first->patronymic, person_second->patronymic);
}

void Add_Person_Sorted(Person **head, char *surname, char *name, char *patronymic) 
{
    Person *New_Person = Create_Person(surname, name, patronymic);

    if (New_Person == NULL) {
        return;
    }

    if (*head == NULL || Compare_Names(New_Person, *head) < 0) {
        New_Person->next = *head;
        *head = New_Person;
    } 
    
    else {

        Person *current = *head;

        while (current->next != NULL && Compare_Names(New_Person, current->next) > 0) {
            current = current->next;
        }

        New_Person->next = current->next;
        current->next = New_Person;
    }
}

void Print_Surnames(Person *head)
{
    while (head != NULL) {
        printf("%s\n", head->surname);
        head = head->next;
    }
}

char *Search_By_Initials(Person *head, char *surname_init, char *name_init, char *patronymic_init)
{
    char *result = (char *)malloc(256 * sizeof(char));

    strcpy(result, "");
    int found = 0;

    while (head != NULL) {

        if ((surname_init[0] == '\0' || strncmp(head->surname, surname_init, strlen(surname_init)) == 0) &&
            (name_init[0] == '\0' || strncmp(head->name, name_init, strlen(name_init)) == 0) &&
            (patronymic_init[0] == '\0' || strncmp(head->patronymic, patronymic_init, strlen(patronymic_init)) == 0)) {

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

    if (!found) {
        strcpy(result, "");;
    }

    return result;
}

void test_Compare_Fullnames_no_patrn()
{
    Person *person1 = Create_Person("", "", ""); 
    Person *person2 = Create_Person("", "", ""); 

    assert(Compare_Names(person2, person1) == -1);

    free(person1); 
    free(person2); 
}

void test_Compare_Fullnames_standard()
{   
    Person *person1 = Create_Person("Куракин", "Андрей", "Владимирович");
    Person *person2 = Create_Person("Хохлова", "Маргарита", "Александровна");

    assert(Compare_Names(person1, person2) < 0);

    free(person1);
    free(person2);
}

void test_Compare_Fullnames_same()
{
    Person *person1 = Create_Person("Иванов", "Иван", "Иванович");
    Person *person2 = Create_Person("Иванов", "Иван", "Иванович");

    assert(Compare_Names(person1, person2) == 0);

    free(person1);
    free(person2);
}


void test_Create_Person_standard()
{
    char surname[50] = "Куракин";
    char name[50] = "Андрей";
    char patronymic[50] = "Владимирович";

    Person *testing = Create_Person(surname, name, patronymic);

    assert(strcmp(testing->surname, surname) == 0);
    assert(strcmp(testing->name, name) == 0);
    assert(strcmp(testing->patronymic, patronymic) == 0);

    free(testing);
}

void test_Create_Person_no_patrn()
{
    char surname[50] = "Иванов";
    char name[50] = "Иван";

    Person *testing = Create_Person(surname, name, "");

    assert(strcmp(testing->surname, surname) == 0);
    assert(strcmp(testing->name, name) == 0);
    assert(strcmp(testing->patronymic, "") == 0);

    free(testing);
}

void test_Compare_Names_Surname()
{
    Person *person_first = Create_Person("Петров", "Петр", "");
    Person *person_second = Create_Person("Сидорович", "Сидор", "");

    assert(Compare_Names(person_first, person_second) < 0);

    free(person_first);
    free(person_second);
}

void test_Add_Person_Sorted_first()
{
    Person *head = NULL;

    Add_Person_Sorted(&head, "Иванов", "Иван", "Иванович");

    assert(strcmp(head->surname, "Иванов") == 0);
    assert(strcmp(head->name, "Иван") == 0);
    assert(strcmp(head->patronymic, "Иванович") == 0);

    free(head);
}

void test_Add_Sorted_middle()
{
    Person *head = NULL;

    Add_Person_Sorted(&head, "Иванов", "Иван", "Иванович");
    Add_Person_Sorted(&head, "Петров", "Петр", "Петрович");
    Add_Person_Sorted(&head, "Сидоров", "Сидор", "Сидорович");

    assert(strcmp(head->next->surname, "Петров") == 0);
    assert(strcmp(head->surname, "Иванов") == 0);

    while (head != NULL) {
        Person *temp = head;
        head = head->next;
        free(temp);
    }
}

void test_Search_By_Initials_not_found()
{

    Person *head = Create_Person("Иванов", "Иван", "Иванович");

    head->next = Create_Person("Петров", "Петр", "Петрович");
    head->next->next = Create_Person("Сидоров", "Сидор", "Сидорович");

    char *result = Search_By_Initials(head, "A", "A", "A");

    assert(strcmp(result, "Иванов Иван Иванович\n") != 0);
    assert(strcmp(result, "Петров Петр Петрович\n") != 0);
    assert(strcmp(result, "Сидоров Сидор Сидорович\n") != 0);

    free(head);
}


void test_Search_By_Initials_found()
{

    Person *head = Create_Person("Иванов", "Иван", "Иванович");

    head->next = Create_Person("Петров", "Петр", "Петрович");
    head->next->next = Create_Person("Сидоров", "Сидор", "Сидорович");

    char *result = Search_By_Initials(head, "И", "И", "И");

    assert(strcmp(result, "Иванов Иван Иванович\n") == 0);

    free(head);
}

void run_tests()
{   
    test_Compare_Fullnames_no_patrn();
    test_Compare_Fullnames_standard();
    test_Compare_Fullnames_same();
    test_Create_Person_no_patrn();
    test_Create_Person_standard();
    test_Compare_Names_Surname();
    test_Add_Person_Sorted_first();
    test_Add_Sorted_middle();
    test_Search_By_Initials_not_found();
    test_Search_By_Initials_found();
}

int main()
{

    setlocale(LC_CTYPE, "Russian");

    Person *head = NULL;

    FILE *file = fopen("names.txt", "r");

    if (!file) {
        return 1;
    }

    char surname[50], name[50], patronymic[50];
    while (fscanf(file, "%49s %49s %49s", surname, name, patronymic) == 3) {
        Add_Person_Sorted(&head, surname, name, patronymic);
    }
    fclose(file);

    Print_Surnames(head);

    char surname_init[50], name_init[50], patronymic_init[50];
    printf(": ");
    scanf("%49s %49s %49s", surname_init, name_init, patronymic_init);

    printf(":\n");
    printf("%s", Search_By_Initials(head, surname_init, name_init, patronymic_init));

    while (head != NULL) {
        Person *temp = head;
        head = head->next;
        free(temp);
    }

    run_tests();

    return 0;
}   