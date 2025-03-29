#include "pch.h"
#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern "C" {
#include "..\PrintTree\printtree.h"
#include "..\PrintTree\printtree.c"
}

int comparefiles(FILE* f1, FILE* f2) {
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

    ch2 = fgetc(f2);
    if (ch1 != ch2) {
        fclose(f1);
        fclose(f2);
        return 0;
    }

    fclose(f1);
    fclose(f2);
    return 1;
}

TEST(PrintTreeTest, HugeTreeTest_1) {
    FILE* inp = fopen("input.txt", "r");
    FILE* out1 = fopen("output1.txt", "w");
    FILE* out2 = fopen("output2.txt", "w");
    node* node = readtree(inp);

    displaytree1(out1, node);
    displaytree2(out2, node);

    fclose(inp);
    fclose(out1);
    fclose(out2);

    out1 = fopen("output1.txt", "r");
    out2 = fopen("output2.txt", "r");

    displayfile(out1);
    displayfile(out2);
    printf("\n");

    fclose(out1);
    fclose(out2);

    ASSERT_EQ(1, 1);
}

TEST(PrintTreeTest, EmptyTest_2) {
    FILE* testfile = fopen("tests\\empty.txt", "r");
    node* tree = readtree(testfile);
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree);
    displaytree2(resultfile2, tree);

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\empty_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\empty_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1)); 
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

TEST(PrintTreeTest, HardTest_3) {
    FILE* testfile = fopen("tests\\hard.txt", "r");

    node* tree = readtree(testfile);
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree);
    displaytree2(resultfile2, tree);
    fclose(resultfile1);
    fclose(resultfile2);
    freetree(tree); 
    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\hard_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\hard_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1)); 
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

TEST(PrintTreeTest, InvalidDataTest_4) {
    FILE* testfile = fopen("tests\\invalid_data.txt", "r");

    node* tree = readtree(testfile);
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree); 
    displaytree2(resultfile2, tree); 

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\invalid_data_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\invalid_data_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1));
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

TEST(PrintTreeTest, NullTest_5) {
    FILE* testfile = fopen("tests\\null.txt", "r");

    node* tree = readtree(testfile); 
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree); 
    displaytree2(resultfile2, tree); 

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\null_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\null_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1));
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}


TEST(PrintTreeTest, SmallTest_6) {
    FILE* testfile = fopen("tests\\small.txt", "r");

    node* tree = readtree(testfile);
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree); 
    displaytree2(resultfile2, tree); 

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree); 

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\small_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\small_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1));
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

TEST(PrintTreeTest, TreeTest_7) {
    FILE* testfile = fopen("tests\\tree.txt", "r");

    node* tree = readtree(testfile); 
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree); 
    displaytree2(resultfile2, tree);

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\tree_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\tree_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1)); 
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

TEST(PrintTreeTest, FullTreeTest_8) {
    FILE* testfile = fopen("tests\\full_tree.txt", "r");

    node* tree = readtree(testfile);
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree);
    displaytree2(resultfile2, tree);

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\full_tree_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\full_tree_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1));
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

TEST(PrintTreeTest, ParticialTreeTest_9) {
    FILE* testfile = fopen("tests\\particial_tree.txt", "r");

    node* tree = readtree(testfile);
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree);
    displaytree2(resultfile2, tree);

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\particial_tree_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\particial_tree_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1));
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}


TEST(PrintTreeTest, HugeTreeTest_10) {
    FILE* testfile = fopen("tests\\huge_tree.txt", "r");

    node* tree = readtree(testfile); 
    FILE* resultfile1 = fopen("tests\\res1.txt", "w");
    FILE* resultfile2 = fopen("tests\\res2.txt", "w");

    displaytree1(resultfile1, tree); 
    displaytree2(resultfile2, tree); 

    fclose(resultfile1);
    fclose(resultfile2);

    freetree(tree);

    resultfile1 = fopen("tests\\res1.txt", "r");
    resultfile2 = fopen("tests\\res2.txt", "r");
    FILE* answerfile1 = fopen("tests\\huge_tree_ans1.txt", "r");
    FILE* answerfile2 = fopen("tests\\huge_tree_ans2.txt", "r");

    EXPECT_TRUE(comparefiles(answerfile1, resultfile1));
    EXPECT_TRUE(comparefiles(answerfile2, resultfile2));

    fclose(resultfile1);
    fclose(resultfile2);
    fclose(answerfile1);
    fclose(answerfile2);
    fclose(testfile);
}

