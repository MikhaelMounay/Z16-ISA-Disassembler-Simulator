#include "Executor.h"

#include <fstream>

Executor::Executor() {
    log = new Logger{};
    pc = 0x0000;
}

Executor::Executor(Logger* Log, const string& filename) {
    log = Log;
    pc = 0x0000;

    loadMemoryFromFile(filename);
}

// Methods
void Executor::_setLogger(Logger* Log) {
    log = Log;
}

void Executor::disassemble(uint16_t inst, uint16_t pc) {
    uint8_t opcode = inst & 0x7;

    switch (opcode) {
        case 0x0: {
            // R-type: [15:12] funct4 | [11:9] rs2 | [8:6] rd/rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t funct4 = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            if (funct4 == 0x0 && funct3 == 0x0) {
                // printf("add %s, %s", regNames[rd_rs1], regNames[rs2]); // TODO:
            }
            // complete the rest
            break;
        }
        case 0x1: {
            // I-type: [15:9] imm[6:0] | [8:6] rd/rs1 | [5:3] funct3 | [2:0] opcode
            // your code goes here
            break;
        }
        case 0x2: {
            // B-type (branch): [15:12] offset[4:1] | [11:9] rs2 | [8:6] rs1 | [5:3] funct3 | [2:0] opcode
            // your code goes here
            break;
        }
        // complete the rest
        default:
            // snprintf(buf, bufSize, "Unknown opcode"); // TODO:
            break;
    }
}

bool Executor::executeInstruction(uint16_t inst) {
    uint8_t opcode = inst & 0x7;
    bool pcUpdated = false; // flag: if instruction updated PC directly

    switch (opcode) {
        case 0x0: {
            // R-type
            uint8_t funct4 = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            if (funct4 == 0x0 && funct3 == 0x0) {
                // add
                regs[rd_rs1] = regs[rd_rs1] + regs[rs2];
            } else if (funct4 == 0x1 && funct3 == 0x0) {
                // sub
                regs[rd_rs1] = regs[rd_rs1] - regs[rs2];
            }
            // complete the rest
            break;
        }
        case 0x1: {
            // I-type
            uint8_t imm7 = (inst >> 9) & 0x7F;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int16_t simm = (imm7 & 0x40) ? (imm7 | 0xFF80) : imm7;
            // your code goes here
            break;
        }
        case 0x2: {
            // B-type (branch)
            // your code goes here
            break;
        }
        case 0x3: {
            // L-type (load/store)
            // your code goes here
            break;
        }
        case 0x5: {
            // J-type (jump)
            // your code goes here
            break;
        }
        case 0x6: {
            // U-type
            // your code goes here
            break;
        }
        case 0x7: {
            // System instruction (ecall)
            // your code goes here
            break;
        }
        default:
            printf("Unknown instruction opcode 0x%X\n", opcode);
            break;
    }

    if (!pcUpdated) {
        pc += 2; // default: move to next instruction
    }
    return true;
}

void Executor::loadMemoryFromFile(const string& filename) {
    ifstream fp(filename, ios::binary);
    if (!fp.is_open()) {
        log->fatal("Error opening binary file");
    }

    // Make sure the file is not empty nor has a different extension other than .bin
    if (!filename.ends_with(".bin")) {
        log->fatal("Error: Not a .bin file");
    }

    if (fp.peek() == ifstream::traits_type::eof()) {
        log->fatal("Error: File " + filename + " is empty");
    }

    fp.read(reinterpret_cast<char*>(memory.data()), MEM_SIZE);
    size_t n = fp.gcount();

    fp.close();
    *log << "Loaded " << n << " bytes into memory" << endl;
}

void Executor::exec() {
    for (int i = 0; i < regs.size(); i++) {
        regs[i] = 0;
    }
    pc = 0;

    while (pc < MEM_SIZE) {
        // Fetch a 16-bit instruction from memory (little-endian)
        /*
         * Little-endian byte-ordering means the least significant byte (LSB) is assumed to come first in memory
         * Since memory is of type <unsigned char> which is of size 8 bits (1 byte)
         * and our ISA operates on 16-bit instructions (2 bytes),
         * we read the memory content at PC (lower half of the instruction)
         * and OR it with
         * the content of the next memory byte at PC+1 (higher half of the instruction)
         * after left shifting it by 8 bits
        */
        uint16_t inst = memory[pc] | (memory[pc + 1] << 8);

        disassemble(inst, pc);

        // Print human-readable assembly instruction to the log
        // printf("0x%04X: %04X %s\n", pc, inst, disasmBuf); // TODO:

        // Execute the instruction on registers/memory and terminate if it's 'ecall 3'
        if (!executeInstruction(inst)) {
            break;
        }

        // Terminate if PC goes out of bounds
        if (pc >= MEM_SIZE) {
            break;
        }
    }
}
