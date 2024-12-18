#include <stdio.h>
#include <gtest/gtest.h>

extern "C" {
#include <tree.h>
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}