#include "l1_polynom.h"
#include <stdlib.h>

#include <gtest/gtest.h>

// ňĺńň äë˙ free_poly
TEST(PolyTest, FreePPoly_EmptyPoly_NoError_no1) {
	poly_t* empty_poly = initialize_poly();
	EXPECT_NO_THROW(free_poly(empty_poly));
}



// ňĺńň äë˙ find
TEST(PolyTest, FindMonom_ExistingDegree_returnValidVal_no3) {
	poly_t* poly = create_poly_from_data(new int[2]{ 2, 1 }, new int[2]{ 5, 3 }, 3);

	monom_t* found = find(poly, 1);
	EXPECT_NE(found, nullptr);
	EXPECT_EQ(found->degree, 1);
	EXPECT_EQ(found->coeff, 3);

	found = find(poly, 2);
	EXPECT_NE(found, nullptr);
	EXPECT_EQ(found->degree, 2);
	EXPECT_EQ(found->coeff, 5);
}

// ňĺńň äë˙ new_monom_in_begin
TEST(PolyTest, AddInBegin_ToNullPoly_returnNULL_no5) {
	monom_t* result = new_monom_in_begin(NULL, 1, 10);
	EXPECT_EQ(result, nullptr);
}

// ňĺńň äë˙ new_monom_in_end
TEST(PolyTest, AddInEnd_ToNullPoly_returnValidVal_no8) {
	monom_t* result = new_monom_in_end(NULL, 1, 10);
	EXPECT_EQ(result, nullptr);
}

// ňĺńň äë˙ sort_poly
TEST(PolyTest, SortPoly_EmptyPoly_returnNULL_no13) {
	poly_t* poly = initialize_poly();
	poly_t* sorted_poly = sort_poly(poly);

	EXPECT_EQ(sorted_poly, poly);
}

// ňĺńň äë˙ poly_in_str
TEST(PolyTest, PolyInStr_EmptyPoly_returnNULL_no14) {
	poly_t* empty_poly = initialize_poly();
	char* str = poly_in_str(empty_poly);
	EXPECT_EQ(str, nullptr);
}

TEST(PolyTest, PolyInStr_Coeff1_returnValidVal_no18) {
	poly_t* poly = create_poly_from_data(new int[1]{ 2 }, new int[1]{ 1 }, 1);
	char* str = poly_in_str(poly);
	ASSERT_STREQ(str, "x^2");
	free(str);
}

// ňĺńň äë˙ read_poly_from_str
TEST(PolyTest, ReadPolyFromStr_EmptyStr_ReturnNull_no21) {
	char* str = "";
	poly_t* poly = read_poly_from_str(str);
	EXPECT_EQ(poly, nullptr);
}

// ňĺńň äë˙ diff_poly
TEST(PolyTest, DiffPoly_WithZeroCoeffs_returnValidVal_no30) {
	poly_t* poly = create_poly_from_data(new int[4]{ 2, 3, 1, 0 }, new int[4]{ 0, 0, 0, 5 }, 4);
	poly_t* result_poly = diff_poly(poly);
	EXPECT_EQ(result_poly->head, nullptr);
}

// ňĺńň äë˙ sum_poly
TEST(PolyTest, SumPoly_TwoEmptyPoly_returnNULL_no31) {
	poly_t* poly = initialize_poly();
	poly_t* poly2 = initialize_poly();
	poly_t* result_poly = sum_poly(poly, poly2);
	EXPECT_EQ(result_poly, nullptr);
}

// ňĺńň äë˙ mul_poly
TEST(PolyTest, MulPoly_WithZeroPoly_returnValidVal_no35) {
	poly_t* poly = initialize_poly();
	poly_t* poly2 = initialize_poly();
	poly_t* result_poly = mul_poly(poly, poly2);
	EXPECT_EQ(result_poly, nullptr);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
 3 changes: 3 additions & 0 deletions3
lab1/output.txt
//
// Created by User on 20.11.2024.
//
