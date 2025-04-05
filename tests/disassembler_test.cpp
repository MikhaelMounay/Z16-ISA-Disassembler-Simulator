#include <gtest/gtest.h>

#include "../src/executor/Executor.h"

using namespace std;

class DisassemblerTest : public ::testing::Test {
protected:
    Executor _executor;

    void SetUp() override {
        _executor.pc = 0;
    }
};

TEST_F(DisassemblerTest, TestCase01) {
    uint16_t instruction = 0x0F80; // add a0, a1
    string disassembledInst = _executor.disassemble(instruction);
    EXPECT_EQ(disassembledInst, "add a0, a1");
}
