#include "pch.h"
#include "../Lab_A/Lab_A.cpp"


TEST(AddElemTest, AddElemToEmptySet__1) {
    Node* set = NULL;
    AddElem(&set, 10);
    EXPECT_TRUE(CheckElem(set, 10));
}

TEST(AddElemTest, AddElemToStart__2) {
    Node* set = NULL;

  
    for (int i = 10; i <= 100; i += 10) {
        AddElem(&set, i);
    }


    AddElem(&set, 5);

    EXPECT_EQ(set->data, 5);
    EXPECT_TRUE(CheckElem(set, 5));

   
    Node* cur = set->next; 
    int exp_val = 10;
    while (cur) {
        EXPECT_EQ(cur->data, exp_val);
        exp_val += 10;
        cur = cur->next;
    }

    EXPECT_EQ(exp_val, 110); 

}


TEST(AddElemTest, AddElemToEnd__3) {
    Node* set = NULL;

    for (int i = 10; i <= 100; i += 10) {
        AddElem(&set, i);
    }

    AddElem(&set, 110);

    Node* cur = set;
    int exp_val = 10;
    while (cur->next) {  
        EXPECT_EQ(cur->data, exp_val);
        exp_val += 10;
        cur = cur->next;
    }

    EXPECT_TRUE(CheckElem(set, 110));
    EXPECT_EQ(cur->data, 110); 
    EXPECT_EQ(cur->next, nullptr);
      
}

TEST(AddElemTest, AddExistingElem__4) {
    Node* set = NULL;

    for (int i = 10; i <= 30; i += 10) {
        AddElem(&set, i);
    }

    AddElem(&set, 20);

    int exp_vals[] = { 10, 20, 30 };
    Node* cur = set;

    for (int index = 0; index < 3; index++) {
        EXPECT_EQ(cur->data, exp_vals[index]);
        cur = cur->next;
    }

    EXPECT_EQ(cur, nullptr);
   
}

TEST(UnionSetsTest, UnionOfTwoSets__5) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElem(&set1, i);
    }

    for (int i = 30; i <= 60; i += 10) {
        AddElem(&set2, i);
    }

    Node* unionSet = UnionSets(set1, set2);

    int exp_set[] = { 10, 20, 30, 40, 50, 60 };
    Node* cur = unionSet;
    
    int index = 0;

    while (cur != nullptr && index < 6) {
        EXPECT_EQ(cur->data, exp_set[index]);
      
        cur = cur->next;
        index++;
    }

    EXPECT_EQ(index, 6); 

}


TEST(UnionSetsTest, UnionWithEmptySet__6) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElem(&set1, i);
    }

    Node* unionSet = UnionSets(set1, set2);

    int exp_set[] = { 10, 20, 30, 40 };
    Node* cur = unionSet;
    int index = 0;

    while (cur != nullptr) {
        EXPECT_EQ(cur->data, exp_set[index]);
        cur = cur->next;
        index++;
    }

    EXPECT_EQ(index, 4);

}



TEST(IntersectionSetsTest, IntersectionOfTwoSets__7) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElem(&set1, i);
    }

    
    for (int i = 30; i <= 60; i += 10) {
        AddElem(&set2, i);
    }

    Node* intersectionSet = IntersectionSets(set1, set2);

    int exp_set[] = { 30, 40 };
    Node* cur = intersectionSet;
    int index=0;
    
    for (int i = 0; i < 2; i++, index++) {
        EXPECT_EQ(cur->data, exp_set[index]);
        cur = cur->next;

    }
 
    EXPECT_EQ(index, 2);

}

TEST(IntersectionSetsTest, IntersectionWithEmptySet__8) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElem(&set1, i);
    }

    Node* intersectionSet = IntersectionSets(set1, set2);

    EXPECT_EQ(intersectionSet, nullptr); 

}


TEST(IntersectionSetsTest, IntersectionOfDistinctElements__9) {
    Node* set1 = NULL;
    Node* set2 = NULL;

    for (int i = 10; i <= 30; i += 10) {
        AddElem(&set1, i);
    }

    for (int i = 40; i <= 60; i += 10) {
        AddElem(&set2, i);
    }

    Node* intersectionSet = IntersectionSets(set1, set2);
    EXPECT_EQ(intersectionSet, nullptr);

}

TEST(RemoveElementsTest, RemoveElementFromSet__10) {
    Node* set = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElem(&set, i);
    }

    RemoveElement(&set, 20);

    int exp_set[] = { 10, 30, 40 };
    Node* cur = set;
    int index = 0;

    while (cur != nullptr) {
        EXPECT_EQ(cur->data, exp_set[index]);
        cur = cur->next;
        ++index;
    }

    EXPECT_EQ(index, 3);
}



TEST(RemoveElementsTest, RemoveNonExistentElementFromSet__11) {
    Node* set = NULL;

    for (int i = 10; i <= 40; i += 10) {
        AddElem(&set, i);
    }

    Node* originalSet = set;
    RemoveElement(&set, 50);

    Node* curOriginal = originalSet;
    Node* curAfterRemove = set;
    int index = 0;

    while (curOriginal != nullptr) {
        EXPECT_EQ(curAfterRemove->data, curOriginal->data);
        curOriginal = curOriginal->next;
        curAfterRemove = curAfterRemove->next;
        ++index;
    }

    EXPECT_EQ(index, 4);

}




