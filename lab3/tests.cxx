#include <gtest/gtest.h>

extern "C" {
    #include "lab3.h"
}

TEST(Lab3Test, minlen_invalid_filename_returnNotFound) {
    const char *invalid_filename = "../files/kgslkgnslfgnkd bfldknrtlksnmdvlnr t-1,,kejg";
    ASSERT_EQ(minlen(invalid_filename), NOT_FOUND);
}

TEST(Lab3Test, minlen_other_format_file_returnNotFound) {
    ASSERT_EQ(minlen("../files/text.txt"), NOT_FOUND);
}

TEST(Lab3Test, minlen_invalid_file_matrix_size_returnNotFound) {
    const char *file = "../files/zeromatrix.txt";
    ASSERT_EQ(minlen(file), NOT_FOUND);
}

TEST(Lab3Test, minlen_not_enough_matrix_data_returnNotFound) {
    const char *file = "../files/not_enough_data.txt";
    ASSERT_EQ(minlen(file), NOT_FOUND);
}

TEST(Lab3Test, minlen_not_symmetric_matrix_returnNotFound) {
    const char *file = "../files/not_symmetric_matrix.txt";
    ASSERT_EQ(minlen(file), NOT_FOUND);
}

TEST(Lab3Test, minlen_no_route_data_returnNotFound) {
    const char *file = "../files/no_route_data.txt";
    ASSERT_EQ(minlen(file), NOT_FOUND);
}

TEST(Lab3Test, minlen_bad_start_val_returnNotFound) {
    const char *bad_filename = "../files/bad_start.txt";
    ASSERT_EQ(minlen(bad_filename), NOT_FOUND);
}

TEST(Lab3Test, minlen_bad_end_val_returnNotFound) {
    const char *bad_filename = "../files/bad_end.txt";
    ASSERT_EQ(minlen(bad_filename), NOT_FOUND);
}

TEST(Lab3Test, minlen_validFile1_returnValidVal) {
    const char *bad_filename = "../files/data1.txt";
    ASSERT_EQ(minlen(bad_filename), 3);
}

TEST(Lab3Test, minlen_validFile2_returnValidVal) {
    const char *bad_filename = "../files/data2.txt";
    ASSERT_EQ(minlen(bad_filename), 3);
}