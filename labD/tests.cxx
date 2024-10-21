#include <gtest/gtest.h>

extern "C" {
#include "sudoku.h"
}

//test 1
TEST(LABD, solve_sudoku_normal_return0) {
    int r = solve_sudoku("../files/normal.txt", "../files/o.txt");
    ASSERT_EQ(r, NO_ERR); //no error
    //check solution
    ASSERT_EQ(check(open_sudoku("../files/o.txt")), 1);
}

//test 2
TEST(LABD, solve_sudoku_bad_input_return_validval) {
    int r = solve_sudoku("../files/ksjdbfksjbtjkerbtkjbsdfkj.txt", "../files/o.txt");
    ASSERT_EQ(r, BAD_INPUT); //bad input error
}

//test 3
TEST(LABD, solve_sudoku_bad_output_return_validval) {
    int r = solve_sudoku("../files/normal.txt", "<?<?<?,_-+==123nkqweg5k233");
    ASSERT_EQ(r, BAD_OUTPUT);
}

//test 4
TEST(LABD, solve_sudoku_bad_sudoku_return_validval) {
    int r = solve_sudoku("../files/bad.txt", "../files/o.txt");
    ASSERT_EQ(r, NO_SOLUTION);
}

//test 5
TEST(LABD, open_sudoku_err_return_err) {
    sudoku r = open_sudoku("../files/lakfnaldgn");
    ASSERT_EQ(r.data == nullptr, true);
    ASSERT_EQ(r.n, -1);
}

//test 6
TEST(LABD, open_sudoku_small_return_err) {
    sudoku r = open_sudoku("../files/small.txt");
    ASSERT_EQ(r.data == nullptr, true);
    ASSERT_EQ(r.n, -1);
}

//test 7
TEST(LABD, open_sudoku_corrupter_return_err) {
    sudoku r = open_sudoku("../files/corrupted.txt");
    ASSERT_EQ(r.data == nullptr, true);
    ASSERT_EQ(r.n, -1);
}

//test 8
TEST(LABD, open_sudoku_larger_val_return_err) {
    sudoku r = open_sudoku("../files/larger_val.txt");
    ASSERT_EQ(r.data == nullptr, true);
    ASSERT_EQ(r.n, -1);
}

//test 9
TEST(LABD, check_return_validval) {
    ASSERT_EQ(check(open_sudoku("../files/normal.txt")), 1);
    ASSERT_EQ(check(open_sudoku("../files/bad.txt")), 0);
}

//test 10
TEST(LABD, check_done_return_validval) {
    solve_sudoku("../files/normal.txt", "../files/temp");
    ASSERT_EQ(check_done(open_sudoku("../files/temp")), 1);
    ASSERT_EQ(check_done(open_sudoku("../files/normal.txt")), 0);
    ASSERT_EQ(check(open_sudoku("../files/bad.txt")), 0);
}
