#include "pch.h"
#include "..//Lab_E//Lab_E.cpp"


// Function to compare the contents of two files
int compareFiles(FILE* f1, FILE* f2) {
    // Check if both files were opened successfully
    if (f1 == NULL || f2 == NULL)
        return -1; // Return -1 if there was an error opening the files

    int ch1, ch2;
    while ((ch1 = fgetc(f1)) != EOF && (ch2 = fgetc(f2)) != EOF) {
        if (ch1 != ch2) {
            fclose(f1);
            fclose(f2);
            return 0; // Return 0 if files are not equal
        }
    }

    // Check for end of file condition
    if (ch1 != ch2) {
        fclose(f1);
        fclose(f2);
        return 0; // Return 0 if files are not equal
    }

    fclose(f1);
    fclose(f2);
    return 1; // Return 1 if files are equal
}

// Test case for an empty tree
TEST(LabETests, EmptyTest__2) {
    FILE* testFile = fopen("tests\\empty.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\empty_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\empty_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for a hard tree structure
TEST(LabETests, HardTest__3) {
    FILE* testFile = fopen("tests\\hard.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\hard_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\hard_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for invalid data in the tree
TEST(LabETests, InvalidDataTest__4) {
    FILE* testFile = fopen("tests\\invalid_data.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\invalid_data_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\invalid_data_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for null input in the tree
TEST(LabETests, NullTest__5) {
    FILE* testFile = fopen("tests\\null.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\null_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\null_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for small tree
TEST(LabETests, SmallTest__6) {
    FILE* testFile = fopen("tests\\small.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\small_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\small_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for a generic tree
TEST(LabETests, TreeTest__7) {
    FILE* testFile = fopen("tests\\tree.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\tree_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\tree_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for a full tree
TEST(LabETests, FullTreeTest__8) {
    FILE* testFile = fopen("tests\\full_tree.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\full_tree_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\full_tree_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for a partial tree
TEST(LabETests, ParticialTreeTest__9) {
    FILE* testFile = fopen("tests\\particial_tree.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\particial_tree_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\particial_tree_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}

// Test case for a huge tree
TEST(LabETests, HugeTreeTest__10) {
    FILE* testFile = fopen("tests\\huge_tree.txt", "r");

    Node* tree = readTree(testFile); // Read tree from test file
    FILE* resultFile1 = fopen("tests\\res1.txt", "w");
    FILE* resultFile2 = fopen("tests\\res2.txt", "w");

    displayTree1(resultFile1, tree); // Save the result1 to a file
    displayTree2(resultFile2, tree); // Save the result2 to a file

    fclose(resultFile1);
    fclose(resultFile2);

    freeNode(tree); // Free the allocated memory for the tree

    resultFile1 = fopen("tests\\res1.txt", "r");
    resultFile2 = fopen("tests\\res2.txt", "r");
    FILE* answerFile1 = fopen("tests\\huge_tree_ans1.txt", "r");
    FILE* answerFile2 = fopen("tests\\huge_tree_ans2.txt", "r");

    EXPECT_TRUE(compareFiles(answerFile1, resultFile1)); // Compare answer and result files
    EXPECT_TRUE(compareFiles(answerFile2, resultFile2));

    fclose(resultFile1);
    fclose(resultFile2);
    fclose(answerFile1);
    fclose(answerFile2);
    fclose(testFile);
}
