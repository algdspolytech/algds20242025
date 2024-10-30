#include "lab1.h"
#include "pch.h"
#include <gtest/gtest.h>
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
    strcpy(line, "Ivanov Ivan Ivanovich 11.11.2011");

    Node* New = parse(line);
    New->next = NULL;

    Node* Expected = (Node*)malloc(sizeof(Node));
    strcpy(Expected->surname, "Ivanov");
    strcpy(Expected->name, "Ivan");
    strcpy(Expected->patronymic, "Ivanovich");
    Expected->date.day = 11;
    Expected->date.month = 11;
    Expected->date.year = 2011;
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
    strcpy(line, "Ivanov Ivan Ivanovich");

    Node* New = parse(line);

    EXPECT_TRUE(compare_lists(New, NULL)); 

    free(line);
    free(New);
}

TEST(_sort_list, AddToEmptyList) {
    
    Node* head = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Ivanov"); 
    strcpy(New->name, "Ivan"); 
    strcpy(New->patronymic, "Ivanovich"); 
    New->date.day = 11;
    New->date.month = 11;
    New->date.year = 2011;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Ivanov");
    strcpy(Expected_Head->name, "Ivan");
    strcpy(Expected_Head->patronymic, "Ivanovich");
    Expected_Head->date.day = 11;
    Expected_Head->date.month = 11;
    Expected_Head->date.year = 2011;
    Expected_Head->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head));

    free(New);
    free(Expected_Head);
}

TEST(_sort_list, AddToNonEmptyList) {
    
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Smirnov");
    strcpy(head->name, "Pavel");
    strcpy(head->patronymic, "Pavlovich");
    head->date.day = 05;
    head->date.month = 05;
    head->date.year = 2012;
    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Ivanov"); 
    strcpy(New->name, "Ivan");
    strcpy(New->patronymic, "Ivanovich");
    New->date.day = 11;
    New->date.month = 11;
    New->date.year = 2011;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Ivanov");
    strcpy(Expected_Head->name, "Ivan");
    strcpy(Expected_Head->patronymic, "Ivanovich");
    Expected_Head->date.day = 11;
    Expected_Head->date.month = 11;
    Expected_Head->date.year = 2011;
    

    Node* Expected_Second = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Second->surname, "Smirnov");
    strcpy(Expected_Second->name, "Pavel");
    strcpy(Expected_Second->patronymic, "Pavlovich");
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
    strcpy(head->surname, "Gutara");
    strcpy(head->name, "Anna");
    strcpy(head->patronymic, "Ivanovna");
    head->date.day = 03;
    head->date.month = 06;
    head->date.year = 2004;
    
    Node* Second = (Node*)malloc(sizeof(Node));
    strcpy(Second->surname, "Laptev"); 
    strcpy(Second->name, "Vlad"); 
    strcpy(Second->patronymic, "Alekseevich");
    Second->date.day = 02;
    Second->date.month = 10;
    Second->date.year = 2006;

    head->next = Second;
    Second->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Grishin");
    strcpy(New->name, "Pavel");
    strcpy(New->patronymic, "Sergeevich");
    New->date.day = 26;
    New->date.month = 07;
    New->date.year = 2005;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Gutara");
    strcpy(Expected_Head->name, "Anna");
    strcpy(Expected_Head->patronymic, "Ivanovna");
    Expected_Head->date.day = 03;
    Expected_Head->date.month = 06;
    Expected_Head->date.year = 2004;

    Node* Expected_Middle = (Node*)malloc(sizeof(Node)); 
    strcpy(Expected_Middle->surname, "Grishin"); 
    strcpy(Expected_Middle->name, "Pavel"); 
    strcpy(Expected_Middle->patronymic, "Sergeevich"); 
    Expected_Middle->date.day = 26; 
    Expected_Middle->date.month = 07; 
    Expected_Middle->date.year = 2005; 

    Node* Expected_Tail = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Tail->surname, "Laptev"); 
    strcpy(Expected_Tail->name, "Vlad"); 
    strcpy(Expected_Tail->patronymic, "Alekseevich"); 
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
    strcpy(head->surname, "Gutara"); 
    strcpy(head->name, "Anna"); 
    strcpy(head->patronymic, "Ivanovna"); 
    head->date.day = 03; 
    head->date.month = 06; 
    head->date.year = 2004; 
    
    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Gutara");
    strcpy(New->name, "Anna");
    strcpy(New->patronymic, "Ivanovna");
    New->date.day = 03;
    New->date.month = 06;
    New->date.year = 2004;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Gutara"); 
    strcpy(Expected_Head->name, "Anna"); 
    strcpy(Expected_Head->patronymic, "Ivanovna"); 
    Expected_Head->date.day = 03; 
    Expected_Head->date.month = 06; 
    Expected_Head->date.year = 2004; 

    Expected_Head->next = NULL;

    EXPECT_TRUE(compare_lists(head, Expected_Head)); 

    free(New);
    free(Expected_Head);
}

TEST(_sort_list, AddSameDates) {
    
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->surname, "Gutara"); 
    strcpy(head->name, "Anna"); 
    strcpy(head->patronymic, "Ivanovna"); 
    head->date.day = 03; 
    head->date.month = 06; 
    head->date.year = 2004; 

    Node* Second = (Node*)malloc(sizeof(Node));
    strcpy(Second->surname, "Laptev"); 
    strcpy(Second->name, "Vlad"); 
    strcpy(Second->patronymic, "Alekseevich"); 
    Second->date.day = 03; 
    Second->date.month = 06; 
    Second->date.year = 2004; 

    head->next = Second;
    Second->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Grishin");
    strcpy(New->name, "Pavel");
    strcpy(New->patronymic, "Sergeevich");
    New->date.day = 03;
    New->date.month = 06;
    New->date.year = 2004;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Gutara"); 
    strcpy(Expected_Head->name, "Anna"); 
    strcpy(Expected_Head->patronymic, "Ivanovna"); 
    Expected_Head->date.day = 03; 
    Expected_Head->date.month = 06; 
    Expected_Head->date.year = 2004; 

    Node* Expected_Middle = (Node*)malloc(sizeof(Node)); 
    strcpy(Expected_Middle->surname, "Laptev"); 
    strcpy(Expected_Middle->name, "Vlad"); 
    strcpy(Expected_Middle->patronymic, "Alekseevich"); 
    Expected_Middle->date.day = 03;
    Expected_Middle->date.month = 06;
    Expected_Middle->date.year = 2004;


    Node* Expected_Tail = (Node*)malloc(sizeof(Node)); 
    strcpy(Expected_Tail->surname, "Grishin"); 
    strcpy(Expected_Tail->name, "Pavel"); 
    strcpy(Expected_Tail->patronymic, "Sergeevich"); 
    Expected_Tail->date.day = 03; 
    Expected_Tail->date.month = 06; 
    Expected_Tail->date.year = 2004; 

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
    strcpy(head->surname, "Gutara"); 
    strcpy(head->name, "Anna"); 
    strcpy(head->patronymic, "Ivanovna"); 
    head->date.day = 03; 
    head->date.month = 06; 
    head->date.year = 2006; 

    head->next = NULL;

    Node* New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Grishin"); 
    strcpy(New->name, "Pavel"); 
    strcpy(New->patronymic, "Sergeevich"); 
    New->date.day = 26;
    New->date.month = 07;
    New->date.year = 2005;

    head = sort_list(head, New);

    New = (Node*)malloc(sizeof(Node));
    strcpy(New->surname, "Grishkevich"); 
    strcpy(New->name, "Pasha"); 
    strcpy(New->patronymic, "Pavlovich"); 
    New->date.day = 29;
    New->date.month = 04;  
    New->date.year = 2004;

    head = sort_list(head, New);

    Node* Expected_Head = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Head->surname, "Grishkevich"); 
    strcpy(Expected_Head->name, "Pasha");  
    strcpy(Expected_Head->patronymic, "Pavlovich"); 
    Expected_Head->date.day = 29; 
    Expected_Head->date.month = 04; 
    Expected_Head->date.year = 2004; 

    Node* Expected_Middle = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Middle->surname, "Grishin");
    strcpy(Expected_Middle->name, "Pavel");
    strcpy(Expected_Middle->patronymic, "Sergeevich");
    Expected_Middle->date.day = 26; 
    Expected_Middle->date.month = 07; 
    Expected_Middle->date.year = 2005; 

    Node* Expected_Tail = (Node*)malloc(sizeof(Node));
    strcpy(Expected_Tail->surname, "Gutara"); 
    strcpy(Expected_Tail->name, "Anna"); 
    strcpy(Expected_Tail->patronymic, "Ivanovna"); 
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
    char* line = "Ivanov Ivan Ivanovich 10.01.1990a";
    Node* New = parse(line);
    EXPECT_EQ(New, nullptr);  
}
