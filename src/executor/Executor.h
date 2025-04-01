#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <cstdint>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdint.h>
using namespace std;

#include "../logger/Logger.h"

class Executor {
private:
    Logger* log;
    const int MEM_SIZE = 65536; // 2^16 Bytes = 64 KB;

    vector<unsigned char> memory = vector<unsigned char>(MEM_SIZE);
    // 8 registers (16-bit each): x0, x1, x2, x3, x4, x5, x6, x7
    vector<uint16_t> regs = vector<uint16_t>(8);
    uint16_t pc; // Program counter (16-bit)
    // Register ABI names for display
    vector<string> regNames = {"t0", "ra", "sp", "s0", "s1", "t1", "a0", "a1"};

public:
    // Constructors
    Executor();
    Executor(Logger* Log, const string& filename);

    // Methods
    void _setLogger(Logger* Log);

    // -----------------------
    // Disassembly Function
    // -----------------------
    //
    // Decodes a 16-bit instruction 'inst' (fetched at address 'pc') and writes a human-readable
    // string to *log*. This decoder uses the opcode (bits [2:0]) to distinguish
    // among R-, I-, B-, L-, J-, U-, and System instructions.
    void disassemble(uint16_t inst, uint16_t pc);

    // -----------------------
    // Instruction Execution
    // -----------------------
    //
    // Executes the instruction 'inst' (a 16-bit word) by updating registers, memory, and PC.
    // Returns 1 to continue simulation or 0 to terminate (if ecall 3 is executed).
    bool executeInstruction(uint16_t inst);

    // -----------------------
    // Memory Loading
    // -----------------------
    //
    // Loads the binary machine code image from the specified file into simulated memory.
    void loadMemoryFromFile(const string& filename);

    // -----------------------
    // Main Simulation Loop
    // -----------------------
    void exec();
};

#endif //EXECUTOR_H
