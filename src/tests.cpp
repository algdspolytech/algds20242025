#include <gtest/gtest.h>
#include <cstdio>
#include <string>
#include <fstream>

extern "C" {
    #include "rucksack.h"
}

FILE* tmp(const char* name, const char* data) {
    FILE* f = fopen(name, "w");
    fprintf(f, "%s", data);
    fclose(f);

    f = fopen(name, "r");
    return f;
}

std::vector<int> parseString(std::string& str) {
    std::stringstream ss(str);
    std::vector<int> res;

    while (!ss.eof()) {
        std::string token;
        std::getline(ss, token, ' ');
        if(!token.empty())
            res.push_back(std::stoi(token));
    }

    return res;
}

bool isValid(std::string& str, std::pair<int, int> bound,
             std::vector<int>& s, std::vector<int>& v) {
    auto data = parseString(str);

    if(data[0] == 0)
        return false;

    int size = 0;
    int value = 0;

    for(auto val : data) {
        size += s[val - 1];
        value += v[val - 1];
    }

    return size <= bound.first && value >= bound.second;
}

TEST(exec, TaskExampleNo1) {
    const char* data =
        "5 5 20 \n"
        "1 2 2 2 3 \n"
        "7 1 1 4 10 \n";
    std::vector<int> s = {1, 2, 2, 2, 3};
    std::vector<int> v = {7, 1, 1, 4, 10};
    int B = 5;
    int K = 20;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_STREQ("0", res_str.c_str());
}

TEST(exec, TaskExampleNo2) {
    const char* data =
        "5 5 10 \n"
        "1 2 2 2 3 \n"
        "7 1 1 4 10 \n";
    std::vector<int> s = {1, 2, 2, 2, 3};
    std::vector<int> v = {7, 1, 1, 4, 10};
    int B = 5;
    int K = 10;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}

TEST(exec, TaskExampleNo3) {
    const char* data =
        "5 200 2 \n"
        "1 2 2 2 3 \n"
        "7 1 1 4 10 \n";
    std::vector<int> s = {1, 2, 2, 2, 3};
    std::vector<int> v = {7, 1, 1, 4, 10};
    int B = 200;
    int K = 2;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}

TEST(exec, OneElementFitsNo4) {
    const char* data =
        "1 200 2 \n"
        "1 \n"
        "7 \n";
    std::vector<int> s = {1};
    std::vector<int> v = {7};
    int B = 200;
    int K = 2;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}

TEST(exec, OneElementNotFitsNo5) {
    const char* data =
        "1 1 33 \n"
        "1 \n"
        "7 \n";
    std::vector<int> s = {1};
    std::vector<int> v = {7};
    int B = 1;
    int K = 33;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_STREQ("0", res_str.c_str());
}

TEST(exec, OnlyMaxValFitsNo6) {
    const char* data =
        "3 5 6 \n"
        "1 1 1\n"
        "1 2 3\n";
    std::vector<int> s = {1, 1, 1};
    std::vector<int> v = {1, 2, 3};
    int B = 5;
    int K = 6;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}

TEST(exec, OnlyMaxSizeFitsNo7) {
    const char* data =
        "3 3 6 \n"
        "1 1 1\n"
        "2 2 3\n";
    std::vector<int> s = {1, 1, 1};
    std::vector<int> v = {2, 2, 3};
    int B = 5;
    int K = 6;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}

TEST(exec, OnlyOneElementFitsNo8) {
    const char* data =
        "3 3 6 \n"
        "1 1 3\n"
        "2 2 6\n";
    std::vector<int> s = {1, 1, 3};
    std::vector<int> v = {2, 2, 6};
    int B = 3;
    int K = 6;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}

TEST(exec, NoElementsNo9) {
    const char* data =
        "0 3 6 \n"
        "\n"
        "\n";
    std::vector<int> s = {};
    std::vector<int> v = {};
    int B = 3;
    int K = 6;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(res_str.empty());
}

TEST(exec, RandomBigExampleNo10) {
    const char* data =
        "20 33 70\n"
        "2 7 5 3 9 1 2 33 1 23 4 5 6 9 2 5 10 2 3 5\n"
        "11 21 3 4 5 77 9 22 3 4 5 2 1 2 3 4 77 9 9 2\n";
    std::vector<int> s = {
        2, 7, 5, 3, 9, 1, 2, 33, 1, 23,
        4, 5, 6, 9, 2, 5, 10, 2, 3, 5
    };
    std::vector<int> v = {
        11, 21, 3, 4, 5, 77, 9, 22, 3,
        4, 5, 2, 1, 2, 3, 4, 77, 9, 9, 2
    };
    int B = 33;
    int K = 70;

    FILE* in = tmp("in_test1.txt", data);
    FILE* out = fopen("out_test1.txt", "w");

    RUCKSACK_exec(in, out);
    fclose(in);
    fclose(out);

    std::string res_str;
    std::ifstream res;
    res.open("out_test1.txt");

    std::getline(res, res_str);

    ASSERT_TRUE(isValid(
        res_str, {B, K}, s, v));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}