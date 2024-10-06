#include "poly.h"
#include <stdlib.h>

#include <gtest/gtest.h>

// Тесты для free_poly
TEST(PolyTest, FreePPoly_EmptyPoly_NoError_no1) {
	poly_t* empty_poly = initialize_poly();
	EXPECT_NO_THROW(free_poly(empty_poly));
}

TEST(PolyTest, FreePoly_WithMultipleMonoms_NoError_no2) {
	poly_t* poly = initialize_poly();
	new_monom_in_end(poly, 2, 5);
	new_monom_in_end(poly, 3, 10);
	EXPECT_NO_THROW(free_poly(poly));
}

// Тесты для find
TEST(PolyTest, FindMonom_ExistingDegree_returnValidVal_no3) {
	poly_t* poly = create_poly_from_data(new int[2]{ 2, 1}, new int[2]{ 5, 3 }, 3);

	monom_t* found = find(poly, 1);
	EXPECT_NE(found, nullptr);
	EXPECT_EQ(found->degree, 1);
	EXPECT_EQ(found->coeff, 3);

	found = find(poly, 2);
	EXPECT_NE(found, nullptr);
	EXPECT_EQ(found->degree, 2);
	EXPECT_EQ(found->coeff, 5);
}

TEST(PolyTest, FindMonom_NotExistingDegree_returnNULL_no4) {
	poly_t* poly = create_poly_from_data(new int[2]{ 2, 1 }, new int[2]{ 5, 3 }, 2);

	monom_t* found = find(poly, 3);
	EXPECT_EQ(found, nullptr);
}

// Тесты для new_monom_in_begin
TEST(PolyTest, AddInBegin_ToNullPoly_returnNULL_no5) {
	monom_t* result = new_monom_in_begin(NULL, 1, 10);
	EXPECT_EQ(result, nullptr);
}

TEST(PolyTest, AddInBegin_MonomInPoly_returnValidVal_no6) {
	poly_t* poly = create_poly_from_data(new int[2]{ 12, 7 }, new int[2]{ 5, 3 }, 2);

	monom_t* added1 = new_monom_in_begin(poly, 2, 10);
	monom_t* added2 = new_monom_in_begin(poly, 3, 15);

	EXPECT_NE(poly->head, nullptr);
	EXPECT_EQ(poly->head->degree, 3);
	EXPECT_EQ(poly->head->coeff, 15);
	EXPECT_EQ(poly->head->next->degree, 2);
	EXPECT_EQ(poly->head->next->coeff, 10);
	EXPECT_EQ(poly->head->next->next->next->next, nullptr);
	EXPECT_EQ(poly->tail, poly->head->next->next->next);
}

TEST(PolyTest, AddInBegin_ThereIsVal_returnValidVal_no7) {
	poly_t* poly = create_poly_from_data(new int[1]{2}, new int[1]{5}, 1);
	monom_t* added = new_monom_in_begin(poly, 2, -10);

	EXPECT_NE(poly->head, nullptr);
	EXPECT_EQ(poly->head->degree, 2);
	EXPECT_EQ(poly->head->coeff, -5);
	EXPECT_EQ(poly->tail, poly->head);
}

// Тесты для new_monom_in_end
TEST(PolyTest, AddInEnd_ToNullPoly_returnValidVal_no8) {
	monom_t* result = new_monom_in_end(NULL, 1, 10);
	EXPECT_EQ(result, nullptr);
}

TEST(PolyTest, AddInEnd_ThereIsVal_returnValidVal_no9) {
	poly_t* poly = initialize_poly();
	monom_t* added = new_monom_in_end(poly, 56, 8);
	monom_t* added2 = new_monom_in_end(poly, 56, -100);

	EXPECT_NE(poly->head, nullptr);
	EXPECT_EQ(poly->head->degree, 56);
	EXPECT_EQ(poly->head->coeff, -92);
	EXPECT_EQ(poly->head->next, nullptr);
	EXPECT_EQ(poly->tail, poly->head);
}

TEST(PolyTest, AddInEnd_MultipleMonoms_returnValidVal_no10) {
	poly_t* poly = initialize_poly();
	new_monom_in_end(poly, 2, 10);
	new_monom_in_end(poly, 1, 5);
	new_monom_in_end(poly, 0, 3);

	EXPECT_NE(poly->head, nullptr);
	EXPECT_EQ(poly->head->degree, 2);
	EXPECT_EQ(poly->head->coeff, 10);
	EXPECT_EQ(poly->head->next->degree, 1);
	EXPECT_EQ(poly->head->next->coeff, 5);
	EXPECT_EQ(poly->head->next->next->degree, 0);
	EXPECT_EQ(poly->head->next->next->coeff, 3);
	EXPECT_EQ(poly->tail->degree, 0);
}

// Тесты для sort_poly
TEST(PolyTest, SortPoly_AlreadySorted_returnValidVal_no11) {
	poly_t* poly = create_poly_from_data(new int[3]{ 0, 1, 2}, new int[3]{1, 2, 3}, 3);

	poly_t* sorted_poly = sort_poly(poly);

	EXPECT_NE(sorted_poly, nullptr);
	EXPECT_EQ(sorted_poly->head->degree, 0);
	EXPECT_EQ(sorted_poly->head->coeff, 1);
	EXPECT_EQ(sorted_poly->head->next->degree, 1);
	EXPECT_EQ(sorted_poly->head->next->coeff, 2);
	EXPECT_EQ(sorted_poly->tail->degree, 2);
	EXPECT_EQ(sorted_poly->tail->coeff, 3);
}

TEST(PolyTest, SortPoly_Unsorted_returnValidVal_no12) {
	poly_t* poly = create_poly_from_data(new int[3]{ 2, 0, 1}, new int[3]{ 3, 1, 2}, 3);

	poly_t* sorted_poly = sort_poly(poly);

	EXPECT_NE(sorted_poly, nullptr);
	EXPECT_EQ(sorted_poly->head->degree, 0);
	EXPECT_EQ(sorted_poly->head->coeff, 1);
	EXPECT_EQ(sorted_poly->head->next->degree, 1);
	EXPECT_EQ(sorted_poly->head->next->coeff, 2);
	EXPECT_EQ(sorted_poly->tail->degree, 2);
	EXPECT_EQ(sorted_poly->tail->coeff, 3);
}

TEST(PolyTest, SortPoly_EmptyPoly_returnNULL_no13) {
	poly_t* poly = initialize_poly();
	poly_t* sorted_poly = sort_poly(poly);

	EXPECT_EQ(sorted_poly, poly);
}

// Тесты для poly_in_str
TEST(PolyTest, PolyInStr_EmptyPoly_returnNULL_no14) {
	poly_t* empty_poly = initialize_poly();
	char* str = poly_in_str(empty_poly);
	EXPECT_EQ(str, nullptr);
}

TEST(PolyTest, PolyInStr_SingleMonom_returnValidVal_no15) {
	poly_t* poly = create_poly_from_data(new int[1]{2}, new int[1]{5}, 1);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "5*x^2");
	free(str);
}

TEST(PolyTest, PolyInStr_MultipleMonoms_returnValidVal_no16) {
	poly_t* poly = create_poly_from_data(new int[3]{ 2, 1, 0 }, new int[3]{ 5, -3, 1 }, 3);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "5*x^2-3*x+1");
	free(str);
}

TEST(PolyTest, PolyInStr_Degree1_returnValidVal_no17) {
	poly_t* poly = create_poly_from_data(new int[1]{1}, new int[1]{5}, 1);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "5*x");
	free(str);
}

TEST(PolyTest, PolyInStr_Coeff1_returnValidVal_no18) {
	poly_t* poly = create_poly_from_data(new int[1]{ 2 }, new int[1]{ 1 }, 1);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "x^2");
	free(str);
}

TEST(PolyTest, PolyInStr_ZeroDegree_returnValidVal_no19) {
	poly_t* poly = create_poly_from_data(new int[1]{ 0 }, new int[1]{ 5 }, 1);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "5");
	free(str);
}

TEST(PolyTest, PolyInStr_LeadingMinus_returnValidVal_no20) {
	poly_t* poly = create_poly_from_data(new int[2]{ 2, 0 }, new int[2]{-5, 3}, 2);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "-5*x^2+3");
	free(str);
}

// Тесты для read_poly_from_str
TEST(PolyTest, ReadPolyFromStr_EmptyStr_ReturnNull_no21) {
	char* str = "";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_EQ(poly, nullptr);
}

TEST(PolyTest, ReadPolyFromStr_SingleMonoms_returnValidVal_no22) {
	char* str = "5*x^2";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_NE(poly, nullptr);
	EXPECT_EQ(poly->head->degree, 2);
	EXPECT_EQ(poly->head->coeff, 5);
	EXPECT_EQ(poly->head->next, nullptr);
}

TEST(PolyTest, ReadPolyFromStr_MultipleMonoms_returnValidVal_no23) {
	char* str = "5*x^2-3*x+1";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_NE(poly, nullptr);
	EXPECT_EQ(poly->head->degree, 2);
	EXPECT_EQ(poly->head->coeff, 5);
	EXPECT_EQ(poly->head->next->degree, 1);
	EXPECT_EQ(poly->head->next->coeff, -3);
	EXPECT_EQ(poly->head->next->next->degree, 0);
	EXPECT_EQ(poly->head->next->next->coeff, 1);
	EXPECT_EQ(poly->head->next->next->next, nullptr);
}

TEST(PolyTest, ReadPolyFromStr_ZeroDegree_returnValidVal_no24) {
	char* str = "5";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_NE(poly, nullptr);
	EXPECT_EQ(poly->head->degree, 0);
	EXPECT_EQ(poly->head->coeff, 5);
	EXPECT_EQ(poly->head->next, nullptr);
}

TEST(PolyTest, ReadPolyFromStr_LeadingMinus_returnValidVal_no25) {
	char* str = "-5x^2-3";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_NE(poly, nullptr);
	EXPECT_EQ(poly->head->degree, 2);
	EXPECT_EQ(poly->head->coeff, -5);
	EXPECT_EQ(poly->head->next->degree, 0);
	EXPECT_EQ(poly->head->next->coeff, -3);
	EXPECT_EQ(poly->head->next->next, nullptr);
}

TEST(PolyTest, ReadPolyFromStr_Coeff1_returnValidVal_no26) {
	char* str = "x^2";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_NE(poly, nullptr);
	EXPECT_EQ(poly->head->degree, 2);
	EXPECT_EQ(poly->head->coeff, 1);
	EXPECT_EQ(poly->head->next, nullptr);
}

TEST(PolyTest, ReadPolyFromStr_Degree1_returnValidVal_no27) {
	char* str = "5*x";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_NE(poly, nullptr);
	EXPECT_EQ(poly->head->degree, 1);
	EXPECT_EQ(poly->head->coeff, 5);
	EXPECT_EQ(poly->head->next, nullptr);
	free_poly(poly);
}

// Тесты для diff_poly
TEST(PolyTest, DiffPoly_SingleMonom_returnValidVal_no28) {
	poly_t* poly = initialize_poly();
	new_monom_in_end(poly, 2, 3);
	poly_t* result_poly = diff_poly(poly);
	EXPECT_EQ(result_poly->head->degree, 1);
	EXPECT_EQ(result_poly->head->coeff, 6);
}

TEST(PolyTest, DiffPoly_WithMultipleMonoms_returnValidVal_no29) {
	poly_t* poly = create_poly_from_data(new int[3]{ 2, 1, 0 }, new int[3]{ 3, 4, 5 }, 3);
	poly_t* result_poly = diff_poly(poly);
	EXPECT_EQ(result_poly->head->degree, 1);
	EXPECT_EQ(result_poly->head->coeff, 6);
	EXPECT_EQ(result_poly->head->next->degree, 0);
	EXPECT_EQ(result_poly->head->next->coeff, 4);
}

TEST(PolyTest, DiffPoly_WithZeroCoeffs_returnValidVal_no30) {
	poly_t* poly = create_poly_from_data(new int[4]{ 2, 3, 1, 0 }, new int[4]{ 0, 0, 0, 5 }, 4);
	poly_t* result_poly = diff_poly(poly);
	EXPECT_EQ(result_poly->head, nullptr);
}

// Тесты для sum_poly
TEST(PolyTest, SumPoly_TwoEmptyPoly_returnNULL_no31) {
	poly_t* poly = initialize_poly();
	poly_t* poly2 = initialize_poly();
	poly_t* result_poly = sum_poly(poly, poly2);
	EXPECT_EQ(result_poly, nullptr);
}

TEST(PolyTest, SumPoly_WithSingleMonom_returnValidVal_no32) {
	poly_t* poly = create_poly_from_data(new int[1]{1}, new int[1]{2}, 1);
	poly_t* poly2 = create_poly_from_data(new int[1]{ 1 }, new int[2]{ 3 }, 1);
	poly_t* result_poly = sum_poly(poly, poly2);
	EXPECT_EQ(result_poly->head->degree, 1);
	EXPECT_EQ(result_poly->head->coeff, 5);
}

TEST(PolyTest, SumPoly_WithDifferentDegrees_returnValidVal_no33) {
	poly_t* poly = create_poly_from_data(new int[2]{ 2, 0 }, new int[2]{ 3, 4 }, 2);
	poly_t* poly2 = create_poly_from_data(new int[2]{ 1, 0 }, new int[2]{ 5, 6 }, 2);
	poly_t* result_poly = sum_poly(poly, poly2);
	EXPECT_EQ(result_poly->head->degree, 2);
	EXPECT_EQ(result_poly->head->coeff, 3);
	EXPECT_EQ(result_poly->head->next->degree, 0);
	EXPECT_EQ(result_poly->head->next->coeff, 10);
	EXPECT_EQ(result_poly->head->next->next->degree, 1);
	EXPECT_EQ(result_poly->head->next->next->coeff, 5);
}

TEST(PolyTest, SumPoly_EmptyPoly1_returnValidVal_no34) {
	poly_t* poly2 = create_poly_from_data(new int[2]{ 2, 1 }, new int[2]{ 3, 5 }, 2);
	poly_t* poly1 = initialize_poly();

	poly_t* sum_poly_result = sum_poly(poly1, poly2);
	EXPECT_NE(sum_poly_result, nullptr);
	EXPECT_EQ(sum_poly_result->head->degree, 2);
	EXPECT_EQ(sum_poly_result->head->coeff, 3);
	EXPECT_EQ(sum_poly_result->head->next->degree, 1);
	EXPECT_EQ(sum_poly_result->head->next->coeff, 5);
	EXPECT_EQ(sum_poly_result->head->next->next, nullptr);
}

// Тесты для mul_poly
TEST(PolyTest, MulPoly_WithZeroPoly_returnValidVal_no35) {
	poly_t* poly = initialize_poly();
	poly_t* poly2 = initialize_poly();
	poly_t* result_poly = mul_poly(poly, poly2);
	EXPECT_EQ(result_poly, nullptr);
}

TEST(PolyTest, MulPoly_WithSingleMonom_returnValidVal_no36) {
	poly_t* poly = create_poly_from_data(new int[1]{ 1 }, new int[1]{ 2 }, 1);
	poly_t* poly2 = create_poly_from_data(new int[1]{ 1 }, new int[1]{ 3 }, 1);
	poly_t* result_poly = mul_poly(poly, poly2);
	EXPECT_EQ(result_poly->head->degree, 2);
	EXPECT_EQ(result_poly->head->coeff, 6);
}

TEST(PolyTest, MulPoly_ZeroCoeff_returnValidVal_no37) {
	poly_t* poly1 = create_poly_from_data(new int[2]{ 2, 1 }, new int[2]{ 2, 1 }, 2);
	poly_t* poly2 = create_poly_from_data(new int[2]{ 2, 1 }, new int[2]{ 0, 2 }, 2);

	poly_t* mul_poly_result = mul_poly(poly1, poly2);
	EXPECT_NE(mul_poly_result, nullptr);
	EXPECT_EQ(mul_poly_result->head->degree, 3);
	EXPECT_EQ(mul_poly_result->head->coeff, 4);
	EXPECT_EQ(mul_poly_result->head->next->degree, 2);
	EXPECT_EQ(mul_poly_result->head->next->coeff, 2);
	EXPECT_EQ(mul_poly_result->head->next->next, nullptr);
}
TEST(PolyTest, MulPoly_TwoPoly_returnValidVal_no38) {
	poly_t* poly = create_poly_from_data(new int[3]{ 2, 1, 0 }, new int[3]{ 3, -4, 5 }, 3);
	poly_t* poly2 = create_poly_from_data(new int[2]{ 1, 0 }, new int[2]{ 2, 6 }, 2);
	poly_t* result_poly = mul_poly(poly, poly2);
	EXPECT_EQ(result_poly->head->degree, 3);
	EXPECT_EQ(result_poly->head->coeff, 6);
	EXPECT_EQ(result_poly->head->next->degree, 2);
	EXPECT_EQ(result_poly->head->next->coeff, 10);
	EXPECT_EQ(result_poly->head->next->next->degree, 1);
	EXPECT_EQ(result_poly->head->next->next->coeff, -14);
	EXPECT_EQ(result_poly->head->next->next->next->degree, 0);
	EXPECT_EQ(result_poly->head->next->next->next->coeff, 30);
}

TEST(PolyTest, MulPoly_MixedSigns_returnValidVal_no39) {
	poly_t* poly1 = create_poly_from_data(new int[2]{ 2, 1 }, new int[2]{ 2, -1 }, 2);
	poly_t* poly2 = create_poly_from_data(new int[2]{ 1, 0 }, new int[2]{ 3, -2 }, 2);

	poly_t* mul_poly_result = mul_poly(poly1, poly2);
	EXPECT_NE(mul_poly_result, nullptr);
	EXPECT_EQ(mul_poly_result->head->degree, 3);
	EXPECT_EQ(mul_poly_result->head->coeff, 6);
	EXPECT_EQ(mul_poly_result->head->next->degree, 2);
	EXPECT_EQ(mul_poly_result->head->next->coeff, -7);
	EXPECT_EQ(mul_poly_result->head->next->next->degree, 1);
	EXPECT_EQ(mul_poly_result->head->next->next->coeff, 2);
	EXPECT_EQ(mul_poly_result->head->next->next->next, nullptr);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
