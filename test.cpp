#include "pch.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "C:\Users\krulo\source\repos\labD\functions.h"
}

class TelegramSchedulerTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        remove("input.txt");
        remove("output.txt");
    }

    void writeInputToFile(const std::string& inputData, const std::string& filename = "input.txt") {
        std::ofstream inputFile(filename);
        inputFile << inputData;
        inputFile.close();
    }

    std::string readOutputFromFile(const std::string& filename = "output.txt") {
        std::ifstream outputFile(filename);
        std::string outputData;
        if (outputFile.is_open()) {
            std::getline(outputFile, outputData);
            outputFile.close();
        }
        return outputData;
    }
};

// 义耱 1: TestMinimumPenalty_SimpleCase_no1
TEST_F(TelegramSchedulerTest, TestMinimumPenalty_SimpleCase_no1) {
    std::string inputData =
        "3 0\n"
        "1 2 10\n"
        "2 4 15\n"
        "1 3 5\n";
    std::string expectedOutput = "1 3 2";

    writeInputToFile(inputData, "input.txt");

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile("output.txt");
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 2: TestPenaltyExceedsK_NoPossibleSchedule_no2
TEST_F(TelegramSchedulerTest, TestPenaltyExceedsK_NoPossibleSchedule_no2) {
    std::string inputData =
        "2 5\n"
        "3 2 10\n"
        "2 1 20\n";
    std::string expectedOutput = "0";

    writeInputToFile(inputData, "input.txt");

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile("output.txt");
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 3: TestSingleTelegram_ZeroPenalty_no3
TEST_F(TelegramSchedulerTest, TestSingleTelegram_ZeroPenalty_no3) {
    std::string inputData =
        "1 0\n"
        "2 5 10\n";
    std::string expectedOutput = "1";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}


// 义耱 4: TestSingleTelegram_WithPenalty_no4
TEST_F(TelegramSchedulerTest, TestSingleTelegram_WithPenalty_no4) {
    std::string inputData =
        "1 10\n"
        "5 2 3\n";
    std::string expectedOutput = "1";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 5: TestZeroPenaltyAllowed_NoTimeConstraint_no5
TEST_F(TelegramSchedulerTest, TestZeroPenaltyAllowed_NoTimeConstraint_no5) {
    std::string inputData =
        "4 100\n"
        "1 0 0\n"
        "2 0 0\n"
        "1 0 0\n"
        "3 0 0\n";
    std::string expectedOutput = "1 3 2 4";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 6: TestTightSchedule_ExactPenalty_no6
TEST_F(TelegramSchedulerTest, TestTightSchedule_ExactPenalty_no6) {
    std::string inputData =
        "2 15\n"
        "5 5 3\n"
        "5 5 0\n";
    std::string expectedOutput = "1 2";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 7: TestLargeNumberOfTelegrams_no7
TEST_F(TelegramSchedulerTest, TestLargeNumberOfTelegrams_no7) {
    std::string inputData =
        "10 50\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n"
        "1 5 5\n";
    std::string expectedOutput = "1 2 3 4 5 6 7 8 9 10";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 8: TestNegativeDelay_NoPenalty_no8
TEST_F(TelegramSchedulerTest, TestNegativeDelay_NoPenalty_no8) {
    std::string inputData =
        "2 0\n"
        "2 10 5\n"
        "1 10 5\n";
    std::string expectedOutput = "2 1";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 9: TestHighPenaltyPerUnitTime_no9
TEST_F(TelegramSchedulerTest, TestHighPenaltyPerUnitTime_no9) {
    std::string inputData =
        "2 30\n"
        "3 5 10\n"
        "2 4 20\n";
    std::string expectedOutput = "2 1";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

// 义耱 10: TestImpossibleToAvoidPenalty_no10
TEST_F(TelegramSchedulerTest, TestImpossibleToAvoidPenalty_no10) {
    std::string inputData =
        "3 25\n"
        "5 5 5\n"
        "5 5 5\n"
        "5 5 5\n";
    std::string expectedOutput = "0";

    writeInputToFile(inputData);

    int n;
    unsigned int K;
    Telegram* telegrams = nullptr;
    readInput("input.txt", &n, &K, &telegrams);

    Telegram* schedule = new Telegram[n];
    scheduleGreedy(n, telegrams, schedule);
    unsigned int totalPenalty = computeTotalPenalty(n, schedule);

    if (totalPenalty <= K) {
        writeOutput("output.txt", n, schedule);
    }
    else {
        std::ofstream outputFile("output.txt");
        outputFile << "0";
        outputFile.close();
    }

    std::string actualOutput = readOutputFromFile();
    EXPECT_EQ(expectedOutput, actualOutput);

    delete[] telegrams;
    delete[] schedule;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

