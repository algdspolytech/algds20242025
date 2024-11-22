#include <iostream>
#include <gtest/gtest.h>
#include <string.h>
#include "main.h"
#include <string.h>

bool check() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "r");

    int n;
    fscanf(input, "%d", &n);

    int *rows = (int*)malloc(sizeof(int) * n);
    int *cols = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        fscanf(output, "%d %d\n", &rows[i], &cols[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rows[i] == rows[j] || // same row
                cols[i] == cols[j] || // same column
                rows[i] - cols[i] == rows[j] - cols[j] || 
                rows[i] + cols[i] == rows[j] + cols[j]
                ) { // same diag
                return false;
            }
        }
    }
    return true;
}

TEST(SampleTests, TestFromTask) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 4);
    fclose(input);
    solve();
    ASSERT_TRUE(check());
}

TEST(SampleTests, SampleBoard) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 8);
    fclose(input);
    solve();
    ASSERT_TRUE(check());
}

TEST(SampleTests, ImpossibleCase) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 3);
    fclose(input);
    solve();
    FILE* output = fopen("output.txt", "r");
    char s[50];
    char expect[] = "no solution\n";
    fgets(s, 50, output);
    fclose(output);
    ASSERT_EQ(strcmp(s, expect), 0);
}

TEST(SampleTests, Even) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 200000);
    fclose(input);
    solve();
    ASSERT_TRUE(check());
}

TEST(SampleTests, NotEven) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 200001);
    fclose(input);
    solve();
    ASSERT_TRUE(check());
}

TEST(SampleTests, BigData) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 999999);
    fclose(input);
    solve();
    ASSERT_TRUE(check());
}

TEST(SampleTests, One) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 1);
    fclose(input);
    solve();
    ASSERT_TRUE(check());
}

TEST(SampleTests, Two) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 2);
    fclose(input);
    solve();
    FILE* output = fopen("output.txt", "r");
    char s[50];
    char expect[] = "no solution\n";
    fgets(s, 50, output);
    fclose(output);
    ASSERT_EQ(strcmp(s, expect), 0);
}

TEST(TestForInput, invalidData) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", -1);
    fclose(input);
    solve();
    FILE* output = fopen("output.txt", "r");
    char s[50];
    char expect[] = "invalid input\n";
    fgets(s, 50, output);
    fclose(output);
    ASSERT_EQ(strcmp(s, expect), 0);
}

TEST(TestForInput, TooBigN) {
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d", 10000000);
    fclose(input);
    solve();
    FILE* output = fopen("output.txt", "r");
    char s[50];
    char expect[] = "invalid input\n";
    fgets(s, 50, output);
    fclose(output);
    ASSERT_EQ(strcmp(s, expect), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}