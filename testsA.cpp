#include "LibA.h"
#include "C:\Users\User\Documents\projects C++\MY_LIBRARY\Windows-Machine-Learning-master\Samples\WinMLSamplesGallery\WinMLSamplesGalleryNative\External\pch.h"
#include "C:\Users\User\Documents\projects C++\MY_LIBRARY\gtests\googletest\include\gtest\gtest.h"
#include <iostream>

using namespace std;

int compare_lists(Node* head1, Node* head2) {
    while (head1 && head2) {
        if (strcmp(head1->surname, head2->surname) != 0 || strcmp(head1->name, head2->name) != 0 ||
            strcmp(head1->patronymic, head2->patronymic) != 0 ||
            head1->date.day != head2->date.day ||
            head1->date.month != head2->date.month ||
            head1->date.year != head2->date.year) {
            return 0;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    if (head1 == NULL && head2 == NULL)
        return 1;
    else
        return 0;
}

TEST(_parse_, NormalInput) {

    char* line = (char *)malloc(sizeof(char) * 1000);
    strcpy(line, "Petrov Petr Petrovich 22.02.1975");

    Node* New = parse(line);
    New->next = NULL;

    Node* Expected = (Node*)malloc(sizeof(Node));
    strcpy(Expected->surname, "Petrov");
    strcpy(Expected->name, "Petr");
    strcpy(Expected->patronymic, "Petrovich");
    Expected->date.day =22;
    Expected->date.month =02;
    Expected->date.year = 1975;
    Expected->next = NULL;

    EXPECT_TRUE(compare_lists(New, Expected));  

    free(line);
    free(New);
    free(Expected);
}

TEST(_parse_, NoInput) { 

    char* line = (char *)malloc(sizeof(char) * 1000);
    strcpy(line, "");

    Node* New = parse(line);

    EXPECT_TRUE(compare_lists(New, NULL)); 

    free(line);
    free(New);
}

TEST(_parse_, IncompleteInput) { 

    char* line = (char *)malloc(sizeof(char) * 1000);
    strcpy(line, "Petrov Petr Petrovich");

    Node* New = parse(line);

    EXPECT_TRUE(compare_lists(New, NULL)); 

    free(line);
    free(New);
}

TEST(_sort_list, AddToEmptyList) {

    Node* head = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Petrov"); 
    strcpy(New->name, "Petr"); 
    strcpy(New->patronymic, "Petrovich"); 
    New->date.day =22;
    New->date.month =02;
    New->date.year = 1975;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Petrov");
    strcpy(Expected_Head->name, "Petr");
    strcpy(Expected_Head->patronymic, "Petrovich");
    Expected_Head->date.day =22;
    Expected_Head->date.month =02;
    Expected_Head->date.year = 1975;
    Expected_Head->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(Expected_Head);
}

TEST(_sort_list, AddToNonEmptyList) {

    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Sidorov");
    strcpy(head->name, "Sidor");
    strcpy(head->patronymic, "Sidorovich");
    head->date.day = 05;
    head->date.month = 05;
    head->date.year = 2012;
    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Petrov"); 
    strcpy(New->name, "Petr");
    strcpy(New->patronymic, "Petrovich");
    New->date.day =22;
    New->date.month =02;
    New->date.year = 1975;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Petrov");
    strcpy(Expected_Head->name, "Petr");
    strcpy(Expected_Head->patronymic, "Petrovich");
    Expected_Head->date.day =22;
    Expected_Head->date.month =02;
    Expected_Head->date.year = 1975;


    Node* Expected_Second = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Second->surname, "Sidorov");
    strcpy(Expected_Second->name, "Sidor");
    strcpy(Expected_Second->patronymic, "Sidorovich");
    Expected_Second->date.day = 05;
    Expected_Second->date.month = 05;
    Expected_Second->date.year = 2012;
    Expected_Head->next = Expected_Second;
    Expected_Second->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(Expected_Head);
    free(Expected_Second);
}

TEST(_sort_list, AddToMiddle) {

    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Belova");
    strcpy(head->name, "Olga");
    strcpy(head->patronymic, "Igorevna");
    head->date.day = 03;
    head->date.month = 06;
    head->date.year = 1899;

    Node* Second = (Node*)malloc(sizeof(Node));
    strcpy(Second->surname, "Popov"); 
    strcpy(Second->name, "Nikolai"); 
    strcpy(Second->patronymic, "Alexandrovich");
    Second->date.day = 02;
    Second->date.month = 10;
    Second->date.year = 2006;

    head->next = Second;
    Second->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Vilka");
    strcpy(New->name, "Kolot");
    strcpy(New->patronymic, "Rudnikovich");
    New->date.day = 29;
    New->date.month = 03;
    New->date.year = 2020;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Belova");
    strcpy(Expected_Head->name, "Olga");
    strcpy(Expected_Head->patronymic, "Igorevna");
    Expected_Head->date.day = 03;
    Expected_Head->date.month = 06;
    Expected_Head->date.year = 1899;

    Node* Expected_Middle = (Node*)malloc(sizeof(Node)); 
    strcpy(Expected_Middle->surname, "Vilka"); 
    strcpy(Expected_Middle->name, "Kolot"); 
    strcpy(Expected_Middle->patronymic, "Rudnikovich"); 
    Expected_Middle->date.day = 29; 
    Expected_Middle->date.month = 03; 
    Expected_Middle->date.year = 2020; 

    Node* Expected_Tail = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Tail->surname, "Popov"); 
    strcpy(Expected_Tail->name, "Nikolai"); 
    strcpy(Expected_Tail->patronymic, "Alexandrovich"); 
    Expected_Tail->date.day = 02; 
    Expected_Tail->date.month = 10; 
    Expected_Tail->date.year = 2006; 

    Expected_Head->next = Expected_Middle; 
    Expected_Middle->next = Expected_Tail;
    Expected_Tail->next = NULL; 

    EXPECT_TRUE(compare_lists(head, Expected_Head)); 

    free(New); 
    free(head); 
    free(Second); 
    free(Expected_Head); 
    free(Expected_Middle); 
    free(Expected_Tail); 
} 

TEST(_sort_list, AddDuplicate) {
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Belova"); 
    strcpy(head->name, "Olga"); 
    strcpy(head->patronymic, "Igorevna"); 
    head->date.day = 03; 
    head->date.month = 06; 
    head->date.year = 1899; 

    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Belova");
    strcpy(New->name, "Olga");
    strcpy(New->patronymic, "Igorevna");
    New->date.day = 03;
    New->date.month = 06;
    New->date.year = 1899;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Belova"); 
    strcpy(Expected_Head->name, "Olga"); 
    strcpy(Expected_Head->patronymic, "Igorevna"); 
    Expected_Head->date.day = 03; 
    Expected_Head->date.month = 06; 
    Expected_Head->date.year = 1899; 

    Expected_Head->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head)); 

    free(New);
    free(Expected_Head);
}

TEST(_sort_list, AddSameDates) {

    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Belova"); 
    strcpy(head->name, "Olga"); 
    strcpy(head->patronymic, "Igorevna"); 
    head->date.day = 03; 
    head->date.month = 06; 
    head->date.year = 1899; 

    Node* Second = (Node*)malloc(sizeof(Node));
    strcpy(Second->surname, "Popov"); 
    strcpy(Second->name, "Nikolai"); 
    strcpy(Second->patronymic, "Alexandrovich"); 
    Second->date.day = 03; 
    Second->date.month = 06; 
    Second->date.year = 1899; 

    head->next = Second;
    Second->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Vilka");
    strcpy(New->name, "Kolot");
    strcpy(New->patronymic, "Rudnikovich");
    New->date.day = 03;
    New->date.month = 06;
    New->date.year = 1899;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Belova"); 
    strcpy(Expected_Head->name, "Olga"); 
    strcpy(Expected_Head->patronymic, "Igorevna"); 
    Expected_Head->date.day = 03; 
    Expected_Head->date.month = 06; 
    Expected_Head->date.year = 1899; 

    Node* Expected_Middle = (Node*)malloc(sizeof(Node)); 
    strcpy(Expected_Middle->surname, "Popov"); 
    strcpy(Expected_Middle->name, "Nikolai"); 
    strcpy(Expected_Middle->patronymic, "Alexandrovich"); 
    Expected_Middle->date.day = 03;
    Expected_Middle->date.month = 06;
    Expected_Middle->date.year = 1899;


    Node* Expected_Tail = (Node*)malloc(sizeof(Node)); 
    strcpy(Expected_Tail->surname, "Vilka"); 
    strcpy(Expected_Tail->name, "Kolot"); 
    strcpy(Expected_Tail->patronymic, "Rudnikovich"); 
    Expected_Tail->date.day = 03; 
    Expected_Tail->date.month = 06; 
    Expected_Tail->date.year = 1899; 

    Expected_Head->next = Expected_Middle;
    Expected_Middle->next = Expected_Tail;
    Expected_Tail->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head)); 

    free(New);
    free(Expected_Head);
    free(Expected_Middle); 
    free(Expected_Tail); 
}

TEST(_sort_list, AddReverseOrder) {

    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Belova"); 
    strcpy(head->name, "Olga"); 
    strcpy(head->patronymic, "Igorevna"); 
    head->date.day = 03; 
    head->date.month = 06; 
    head->date.year = 1999; 

    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Vilka"); 
    strcpy(New->name, "Kolot"); 
    strcpy(New->patronymic, "Rudnikovich"); 
    New->date.day = 29;
    New->date.month = 03;
    New->date.year = 2020;

    head = sort_list(head, New);

    New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Vilochka"); 
    strcpy(New->name, "Pasha"); 
    strcpy(New->patronymic, "Ruda"); 
    New->date.day = 31;
    New->date.month = 02;  
    New->date.year = 2005;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Vilochka"); 
    strcpy(Expected_Head->name, "Pasha");  
    strcpy(Expected_Head->patronymic, "Ruda"); 
    Expected_Head->date.day = 31; 
    Expected_Head->date.month = 02; 
    Expected_Head->date.year = 2005; 

    Node* Expected_Middle = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Middle->surname, "Vilka");
    strcpy(Expected_Middle->name, "Kolot");
    strcpy(Expected_Middle->patronymic, "Rudnikovich");
    Expected_Middle->date.day = 29; 
    Expected_Middle->date.month = 03; 
    Expected_Middle->date.year = 2020; 

    Node* Expected_Tail = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Tail->surname, "Belova"); 
    strcpy(Expected_Tail->name, "Olga"); 
    strcpy(Expected_Tail->patronymic, "Igorevna"); 
    Expected_Tail->date.day = 03; 
    Expected_Tail->date.month = 06; 
    Expected_Tail->date.year = 2006; 

    Expected_Head->next = Expected_Middle;
    Expected_Middle->next = Expected_Tail;
    Expected_Tail->next = NULL; 

    EXPECT_TRUE(compare_lists(head, Expected_Head)); 

    free(New);
    free(Expected_Head);
    free(Expected_Middle); 
    free(Expected_Tail); 
}

TEST(_parse_, InvalidFormat) {
    char* line = "Petrov Petr Petrovich 22.02.1975a";
    Node* New = parse(line);
    EXPECT_EQ(New, nullptr);  
}