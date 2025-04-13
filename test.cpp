#include "code.h"
#include <gtest/gtest.h>

int compare(FILE* f1, FILE* f2) {
    if (f1 == NULL || f2 == NULL)
        return -1; 

    int ch1, ch2;
    while ((ch1 = fgetc(f1)) != EOF && (ch2 = fgetc(f2)) != EOF) {
        if (ch1 != ch2) {
            fclose(f1);
            fclose(f2);
            return 0; 
        }
    }

    if (ch1 != ch2) {
        fclose(f1);
        fclose(f2);
        return 0; 
    }

    fclose(f1);
    fclose(f2);
    return 1; 
}


TEST(Test_1) {
    FILE* testFile = fopen("1.txt", "r");

    Node* tree = read(testFile); 
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree); 
    Tree2(resultFile2, tree); 

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree); 

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans1_1.txt", "r");
    FILE* answerFile2 = fopen("ans1_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1)); 
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}


TEST(Test_2) {
    FILE* testFile = fopen("2.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans2_1.txt", "r");
    FILE* answerFile2 = fopen("ans2_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}


TEST(Test_3) {
    FILE* testFile = fopen("3.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans3_1.txt", "r");
    FILE* answerFile2 = fopen("ans3_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}


TEST(Test_4) {
    FILE* testFile = fopen("4.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans4_1.txt", "r");
    FILE* answerFile2 = fopen("ans4_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}


TEST(Test_5) {
    FILE* testFile = fopen("5.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans5_1.txt", "r");
    FILE* answerFile2 = fopen("ans5_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

TEST(Test_6) {
    FILE* testFile = fopen("6.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans6_1.txt", "r");
    FILE* answerFile2 = fopen("ans6_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

TEST(Test_7) {
    FILE* testFile = fopen("7.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans7_1.txt", "r");
    FILE* answerFile2 = fopen("ans7_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}


TEST(Test_8) {
    FILE* testFile = fopen("8.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans8_1.txt", "r");
    FILE* answerFile2 = fopen("ans8_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}


TEST(Test_9) {
    FILE* testFile = fopen("9.txt", "r");

    Node* tree = read(testFile);
    FILE* resultFile1 = fopen("res1.txt", "w");
    FILE* resultFile2 = fopen("res2.txt", "w");

    Tree1(resultFile1, tree);
    Tree2(resultFile2, tree);

    fclose(resultFile1);
    fclose(resultFile2);

    free(tree);

    resultFile1 = fopen("res1.txt", "r");
    resultFile2 = fopen("res2.txt", "r");
    FILE* answerFile1 = fopen("ans9_1.txt", "r");
    FILE* answerFile2 = fopen("ans9_2.txt", "r");

    EXPECT_TRUE(compare(answerFile1, resultFile1));
    EXPECT_TRUE(compare(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
