#include "pch.h"
#include "..//main//Solution.cpp"


TEST(SolutionTests, ExampleTest__1) {
	solution("test/example.txt", "test/output.txt");
    
	int r[] = {1, 3, 2, 5, 6, 7, 8};

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, EmptyTest__2) {
	solution("test/empty.txt", "test/output.txt");

	int r[] = { 0 };

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, HardTest__3) {
	solution("test/hard.txt", "test/output.txt");

	int r[] = { 5, 3, 4, 5, 1, 2, 11, 8, 9, };

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 9;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, InvalidDataTest__4) {
	solution("test/invalid.txt", "test/output.txt");

	int r[] = { 6, 2, 3, 5, 1, 8, 9};

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, NullTest__5) {
	solution("test/Null.txt", "test/output.txt");

	int r[] = { 3, 1, 4, 2, 7, 6, 9 };

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, SmallTest__6) {
	solution("test/Small.txt", "test/output.txt");

	int r[] = { 9, 7, 5, 3, 4, 1, 8};

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, SolvedTest__7) {
	solution("test/Solved.txt", "test/output.txt");

	int r[] = { 2, 3, 1, 4, 5, 9, 6, 7, 8, 12, 11};

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 11;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, UnsolvableTest__8) {
	solution("test/Unsolvabl.txt", "test/output.txt");

	int r[] = { 3, 2, 1, 4, 6, 7, 8 };

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, BigTest__9) {
	solution("test/Big.txt", "test/output.txt");

	int r[] = { 9, 1, 7, 2, 4, 5, 6 };

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}

TEST(SolutionTests, InvalidNTest__10) {
	solution("test/InvalidN.txt", "test/output.txt");

	int r[] = { 6, 8, 2, 3, 4, 1, 9 };

	FILE* test = fopen("test/output.txt", "r");
	int a;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i", &a);
		EXPECT_EQ(r[i], a);
	}
	fclose(test);
}