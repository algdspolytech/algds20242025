#include "LibD.c"


TEST(DTests, ExampleTest__1) {
	LibD("test/example.txt", "test/output.txt");

	FILE* ans = fopen("test/ans_output.txt", "r");
	FILE* test = fopen("test/output.txt", "r");
	int x1, y2, x1, y2;
	for (int i = 0;i < 7;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(ans);
	fclose(test);
}

TEST(DTests, EmptyTest__2) {
	LibD("test/empty.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, HardTest__3) {
	LibD("test/hard.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 15;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, InvalidDataTest__4) {
	LibD("test/invalid.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, NullTest__5) {
	LibD("test/Null.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, SmallTest__6) {
	LibD("test/Small.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 5;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, SolvedTest__7) {
	LibD("test/Solved.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 14;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, UnsolvableTest__8) {
	LibD("test/Unsolvabl.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, BigTest__9) {
	LibD("test/Big.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 29;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}

TEST(DTests, InvalidNTest__10) {
	LibD("test/InvalidN.txt", "test/output.txt");

	FILE* test = fopen("test/output.txt", "r");
	FILE* ans = fopen("test/ans_output.txt", "r");
	int x1, x2, y1, y2;
	for (int i = 0;i < 1;i++) {
		fscanf(test, "%i %i", &x1, &x2);
		fscanf(ans, "%i %i", &y1, &y2);
		EXPECT_EQ(x1, y1);
		EXPECT_EQ(x2, y2);
	}
	fclose(test);
	fclose(ans);
}
