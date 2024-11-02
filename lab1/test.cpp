#include "pch.h"
#include "../Lab_A/Lab_A.cpp"


TEST(AddElementsTest, AddElementToEmptySet__1) {
    Node* set = NULL;
    AddElement(&set, 10);
    EXPECT_TRUE(CheckElement(set, 10));
}

TEST(AddElementsTest, AddToElementToStart__2) {
    Node* set = NULL;

  
    for (int i = 10; i <= 100; i += 10) {
        AddElement(&set, i);
    }


    AddElement(&set, 5);

    EXPECT_EQ(set->data, 5);
    EXPECT_TRUE(CheckElement(set, 5));

   
    Node* current = set->next; 
    int expected_value = 10;
    while (current) {
        EXPECT_EQ(current->data, expected_value);
        expected_value += 10;
        current = current->next;
    }

    EXPECT_EQ(expected_value, 110); 

}


TEST(AddElementsTest, AddToElementToEnd__3) {
    Node* set = NULL;

    for (int i = 10; i <= 100; i += 10) {
        AddElement(&set, i);
    }

    AddElement(&set, 110);

    Node* current = set;
    int expected_value = 10;
    while (current->next) {  
        EXPECT_EQ(current->data, expected_value);
        expected_value += 10;
        current = current->next;
    }

    EXPECT_TRUE(CheckElement(set, 110));
    EXPECT_EQ(current->data, 110); 
    EXPECT_EQ(current->next, nullptr);
      
}

TEST(AddElementsTest, AddExistingElement__4) {
    Node* set = NULL;

    for (int i = 10; i <= 30; i += 10) {
        AddElement(&set, i);
    }

    AddElement(&set, 20);

    int expected_values[] = { 10, 20, 30 };
    Node* current = set;

    for (int index = 0; index < 3; index++) {
        EXPECT_EQ(current->data, expected_values[index]);
        current = current->next;
    }

    EXPECT_EQ(current, nullptr);
   
}

TEST(UnionSetsTest, UnionOfTwoSets__5) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElement(&set1, i);
    }

    for (int i = 30; i <= 60; i += 10) {
        AddElement(&set2, i);
    }

    Node* unionSet = UnionSets(set1, set2);

    int expected_set[] = { 10, 20, 30, 40, 50, 60 };
    Node* current = unionSet;
    
    int index = 0;

    while (current != nullptr && index < 6) {
        EXPECT_EQ(current->data, expected_set[index]);
      
        current = current->next;
        index++;
    }

    EXPECT_EQ(index, 6); 

}


TEST(UnionSetsTest, UnionWithEmptySet__6) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElement(&set1, i);
    }

    Node* unionSet = UnionSets(set1, set2);

    int expected_set[] = { 10, 20, 30, 40 };
    Node* current = unionSet;
    int index = 0;

    while (current != nullptr) {
        EXPECT_EQ(current->data, expected_set[index]);
        current = current->next;
        index++;
    }

    EXPECT_EQ(index, 4);

}



TEST(IntersectionSetsTest, IntersectionOfTwoSets__7) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElement(&set1, i);
    }

    
    for (int i = 30; i <= 60; i += 10) {
        AddElement(&set2, i);
    }

    Node* intersectionSet = IntersectionSets(set1, set2);

    int expected_set[] = { 30, 40 };
    Node* current = intersectionSet;
    int index=0;
    
    for (int i = 0; i < 2; i++, index++) {
        EXPECT_EQ(current->data, expected_set[index]);
        current = current->next;

    }
 
    EXPECT_EQ(index, 2);

}

TEST(IntersectionSetsTest, IntersectionWithEmptySet__8) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElement(&set1, i);
    }

    Node* intersectionSet = IntersectionSets(set1, set2);

    EXPECT_EQ(intersectionSet, nullptr); 

}


TEST(IntersectionSetsTest, IntersectionOfDistinctElements__9) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 30; i += 10) {
        AddElement(&set1, i);
    }

    for (int i = 40; i <= 60; i += 10) {
        AddElement(&set2, i);
    }

    Node* intersectionSet = IntersectionSets(set1, set2);
    EXPECT_EQ(intersectionSet, nullptr);

}

TEST(RemoveElementsTest, RemoveElementFromSet__10) {
    Node* set = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElement(&set, i);
    }

    RemoveElement(&set, 20);

    int expected_set[] = { 10, 30, 40 };
    Node* current = set;
    int index = 0;

    while (current != nullptr) {
        EXPECT_EQ(current->data, expected_set[index]);
        current = current->next;
        ++index;
    }

    EXPECT_EQ(index, 3);
}



TEST(RemoveElementsTest, RemoveNonExistentElementFromSet__11) {
    Node* set = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElement(&set, i);
    }

    Node* originalSet = set;
    RemoveElement(&set, 50);

    Node* currentOriginal = originalSet;
    Node* currentAfterRemove = set;
    int index = 0;

    while (currentOriginal != nullptr) {
        EXPECT_EQ(currentAfterRemove->data, currentOriginal->data);
        currentOriginal = currentOriginal->next;
        currentAfterRemove = currentAfterRemove->next;
        ++index;
    }

    EXPECT_EQ(index, 4);

}




