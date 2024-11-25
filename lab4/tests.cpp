#include "pch.h"
#include "..//LabD//LabD.cpp"


TEST(LabDTests, ExampleTest__1) {
	LabD("test/example.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, EmptyTest__2) {
	LabD("test/empty.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, HardTest__3) {
	LabD("test/hard.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 15;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, InvalidDataTest__4) {
	LabD("test/invalid.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, NullTest__5) {
	LabD("test/Null.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, SmallTest__6) {
	LabD("test/Small.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 5;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, SolvedTest__7) {
	LabD("test/Solved.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 14;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, UnsolvableTest__8) {
	LabD("test/Unsolvabl.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, BigTest__9) {
	LabD("test/Big.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 29;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}

TEST(LabDTests, InvalidNTest__10) {
	LabD("test/InvalidN.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int a1, a2, b1, b2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &a1, &a2);
		fscanf(ans, "%i %i", &b1, &b2);
		EXPECT_EQ(a1, b1);
		EXPECT_EQ(a2, b2);
	}
	fclose(test);
	fclose(ans);
}
