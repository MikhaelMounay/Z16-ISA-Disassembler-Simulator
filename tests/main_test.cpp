#include <gtest/gtest.h>

#include "../src/executor/Executor.h"

using namespace std;

TEST(MainTest, TestCase01) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_01/test_01.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("512\n1540\n", output);
}

TEST(MainTest, TestCase02) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_02/test_02.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("0\n1\n12\n8191\n-1\n", output);
}

TEST(MainTest, TestCase03) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_03/test_03.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("1\n2\n3\n4\n5\n", output);
}

TEST(MainTest, TestCase04) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_04/test_04.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    // TODO:
    EXPECT_EQ("2\n4\n6\n8\n9\n", output);
}

TEST(MainTest, TestCase05) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_05/test_05.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    // TODO:
    EXPECT_EQ("2\n4\n6\n8\n9\n", output);
}

TEST(MainTest, TestCase06) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_06/test_06.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("8\n32\n-4\n1\n1\n", output);
}

TEST(MainTest, TestCase07) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_07/test_07.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("70\n50\n80\n", output);
}

TEST(MainTest, TestCase08) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_08/test_08.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("012", output);
}

TEST(MainTest, TestCase09) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_09/test_09.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("4\nT", output);
}

TEST(MainTest, TestCase10) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_10/test_10.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("0\n45\n63\n29\n29\n33\n35\n34\n", output);
}

TEST(MainTest, TestCase11) {
    Logger log;
    Executor executor(&log, "../../tests/test_cases/test_11/test_11.bin");
    executor.exec();

    string output = executor.getOutput()->toString();
    EXPECT_EQ("58\n62\n51\n", output);
}
