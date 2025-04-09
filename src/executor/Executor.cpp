#include "Executor.h"

#include <format>
#include <fstream>
#include <iomanip>

Executor::Executor() {
    log = new Logger{};
    pc = 0x0000;
}

Executor::Executor(Logger* Log, const string& filename) {
    log = Log;
    pc = 0x0000;

    loadMemoryFromFile(filename);
}

// Getters
Logger* Executor::getOutput() {
    return &output;
}

Logger* Executor::getMemoryDump() {
    return &memoryDump;
}

// Methods
void Executor::_setLogger(Logger* Log) {
    log = Log;
}

string Executor::disassemble(uint16_t inst) {
    uint8_t opcode = inst & 0x7;

    stringstream ss;

    switch (opcode) {
        case 0x0: {
            // R-type: [15:12] funct4 | [11:9] rs2 | [8:6] rd/rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t funct4 = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;

            if (funct4 == 0b0000 && funct3 == 0b000) {
                ss << "add " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0001 && funct3 == 0b000) {
                ss << "sub " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b001) {
                ss << "slt " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b010) {
                ss << "sltu " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0010 && funct3 == 0b011) {
                ss << "sll " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0100 && funct3 == 0b011) {
                ss << "srl " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b1000 && funct3 == 0b011) {
                ss << "sra " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0001 && funct3 == 0b100) {
                ss << "or " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b101) {
                ss << "and " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b110) {
                ss << "xor " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b111) {
                ss << "mv " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else if (funct4 == 0b0100 && funct3 == 0b000) {
                ss << "jr " << regNames[rs2];
            } else if (funct4 == 0b1000 && funct3 == 0b000) {
                ss << "jalr " << regNames[rd_rs1] << ", " << regNames[rs2];
            } else {
                log->fatal("Unknown R-type instruction");
            }
            break;
        }
        case 0x1: {
            // I-type: [15:9] imm[6:0] | [8:6] rd/rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t imm7 = (inst >> 9) & 0x7F;
            uint8_t imm3 = (inst >> 13) & 0x7;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int16_t simm = (imm7 & 0x40) ? (imm7 | 0xFF80) : imm7;

            if (funct3 == 0b000) {
                ss << "addi " << regNames[rd_rs1] << ", " << simm;
            } else if (funct3 == 0b001) {
                ss << "slti " << regNames[rd_rs1] << ", " << simm;
            } else if (funct3 == 0b010) {
                ss << "sltui " << regNames[rd_rs1] << ", " << imm7;
            } else if (funct3 == 0b011 && imm3 == 0b001) {
                ss << "slli " << regNames[rd_rs1] << ", " << (simm & 0xF);
            } else if (funct3 == 0b011 && imm3 == 0b010) {
                ss << "srli " << regNames[rd_rs1] << ", " << (simm & 0xF);
            } else if (funct3 == 0b011 && imm3 == 0b100) {
                ss << "srai " << regNames[rd_rs1] << ", " << (simm & 0xF);
            } else if (funct3 == 0b100) {
                ss << "ori " << regNames[rd_rs1] << ", " << simm;
            } else if (funct3 == 0b101) {
                ss << "andi " << regNames[rd_rs1] << ", " << simm;
            } else if (funct3 == 0b110) {
                ss << "xori " << regNames[rd_rs1] << ", " << simm;
            } else if (funct3 == 0b111) {
                ss << "li " << regNames[rd_rs1] << ", " << simm;
            } else {
                log->fatal("Unknown I-type instruction");
            }
            break;
        }
        case 0x2: {
            // B-type (branch): [15:12] offset[4:1] | [11:9] rs2 | [8:6] rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t offset = ((inst >> 12) & 0xF);
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int8_t sOffset = (offset & 0x8) ? (offset | 0xF0) : offset;
            int16_t sOffset16 = 2 + sOffset * 2;

            if (funct3 == 0b000) {
                ss << "beq " << regNames[rs1] << ", " << regNames[rs2] << ", "
                    << static_cast<int>(sOffset16);
            } else if (funct3 == 0b001) {
                ss << "bne " << regNames[rs1] << ", " << regNames[rs2] << ", "
                    << static_cast<int>(sOffset16);
            } else if (funct3 == 0b010) {
                ss << "bz " << regNames[rs1] << ", " << static_cast<int>(
                    sOffset16 - 2);
            } else if (funct3 == 0b011) {
                ss << "bnz " << regNames[rs1] << ", " << static_cast<int>(
                    sOffset16 - 2);
            } else if (funct3 == 0b100) {
                ss << "blt " << regNames[rs1] << ", " << regNames[rs2] << ", "
                    << static_cast<int>(sOffset16);
            } else if (funct3 == 0b101) {
                ss << "bge " << regNames[rs1] << ", " << regNames[rs2] << ", "
                    << static_cast<int>(sOffset16);
            } else if (funct3 == 0b110) {
                ss << "bltu " << regNames[rs1] << ", " << regNames[rs2] << ", "
                    << static_cast<int>(sOffset16);
            } else if (funct3 == 0b111) {
                ss << "bgeu " << regNames[rs1] << ", " << regNames[rs2] << ", "
                    << static_cast<int>(sOffset16);
            } else {
                log->fatal("Unknown B-type instruction");
            }
            break;
        }
        case 0x3: {
            // S-Type: [15:12] offset[3:0] | [11:9] rs2 | [8:6] rs1 | [5:3] funct3 | [2:0] opcode
            int8_t offset = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int8_t sOffset = (offset & 0x8) ? (offset | 0xF0) : offset;
            int16_t sOffset16 = sOffset;

            if (funct3 == 0b000) {
                ss << "sb " << regNames[rs2] << ", " << sOffset16 << "(" <<
                    regNames[rs1] << ")";
            } else if (funct3 == 0b001) {
                ss << "sw " << regNames[rs2] << ", " << sOffset16 << "(" <<
                    regNames[rs1] << ")";
            } else {
                log->fatal("Unknown S-type instruction");
            }
            break;
        }
        case 0x4: {
            // L-Type: [15:12] offset[3:0] | [11:9] rs2 | [8:6] rd | [5:3] funct3 | [2:0] opcode
            int8_t offset = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rd = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int8_t sOffset = (offset & 0x8) ? (offset | 0xF0) : offset;
            int16_t sOffset16 = sOffset * 2;

            if (funct3 == 0b000) {
                ss << "lb " << regNames[rd] << ", " << sOffset16 << "(" <<
                    regNames[rs2] << ")";
            } else if (funct3 == 0b001) {
                ss << "lw " << regNames[rd] << ", " << sOffset16 << "(" <<
                    regNames[rs2] << ")";
            } else if (funct3 == 0b100) {
                ss << "lbu " << regNames[rd] << ", " << sOffset16 << "(" <<
                    regNames[rs2] << ")";
            } else {
                log->fatal("Unknown L-type instruction");
            }
            break;
        }
        case 0x5: {
            // J-Type: [15:15] f | [14:9] I[9:4] | [8:6] rd | [5:3] I[3:1] | [2:0] opcode
            uint8_t f = (inst >> 15) & 0x1;
            uint8_t imm6 = (inst >> 9) & 0x3F;
            uint8_t rd = (inst >> 6) & 0x7;
            uint8_t imm3 = (inst >> 3) & 0x7;

            uint16_t imm = imm3 | (imm6 << 3);
            int16_t simm = (imm & 0x100) ? (imm | 0xFE00) : imm;
            int16_t simm16 = simm * 2;

            if (f == 0b0) {
                ss << "j " << simm16;
            } else if (f == 0b1) {
                ss << "jal " << regNames[rd] << ", " << simm16;
            } else {
                log->fatal("Unknown J-type instruction");
            }
            break;
        }
        case 0x6: {
            // U-Type: [15:15] f | [14:9] I[15:10] | [8:6] rd | [5:3] I[9:7] | [2:0] opcode
            uint8_t f = (inst >> 15) & 0x1;
            uint8_t imm6 = (inst >> 9) & 0x3F;
            uint8_t rd = (inst >> 6) & 0x7;
            uint8_t imm3 = (inst >> 3) & 0x7;

            uint16_t imm = imm3 | (imm6 << 3);
            int16_t simm = (imm & 0x100) ? (imm | 0xFE00) : imm;

            if (f == 0b0) {
                ss << "lui " << regNames[rd] << ", " << simm;
            } else if (f == 0b1) {
                ss << "auipc " << regNames[rd] << ", " << simm;
            } else {
                log->fatal("Unknown J-type instruction");
            }
            break;
        }
        case 0x7: {
            // SYS-Type: [15:6] Service[11:0] | [5:3] funct3 | [2:0] opcode
            uint16_t service10 = (inst >> 6) & 0x3FF;
            uint8_t funct3 = (inst >> 3) & 0x7;

            if (funct3 == 0b000) {
                ss << "ecall " << service10;
            } else {
                log->fatal("Unknown SYS-type instruction");
            }
            break;
        }
        default:
            ss << "Unknown instruction with opcode 0x" << hex <<
                static_cast<int>(opcode);
            break;
    }

    return ss.str();
}

bool Executor::executeInstruction(uint16_t inst) {
    uint8_t opcode = inst & 0x7;
    bool pcUpdated = false; // flag: if instruction updated PC directly

    switch (opcode) {
        case 0x0: {
            // R-type: [15:12] funct4 | [11:9] rs2 | [8:6] rd/rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t funct4 = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;

            if (funct4 == 0b0000 && funct3 == 0b000) {
                // add
                regs[rd_rs1] = regs[rd_rs1] + regs[rs2];
            } else if (funct4 == 0b0001 && funct3 == 0b000) {
                // sub
                regs[rd_rs1] = regs[rd_rs1] - regs[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b001) {
                // slt
                if (regs[rd_rs1] < regs[rs2]) {
                    regs[rd_rs1] = 1;
                } else {
                    regs[rd_rs1] = 0;
                }
            } else if (funct4 == 0b0000 && funct3 == 0b010) {
                // sltu
                if (regs[rd_rs1] < regs[rs2]) {
                    regs[rd_rs1] = 1;
                } else {
                    regs[rd_rs1] = 0;
                }
            } else if (funct4 == 0b0010 && funct3 == 0b011) {
                // sll
                regs[rd_rs1] = regs[rd_rs1] << regs[rs2];
            } else if (funct4 == 0b0100 && funct3 == 0b011) {
                // srl
                regs[rd_rs1] = regs[rd_rs1] >> regs[rs2];
            } else if (funct4 == 0b1000 && funct3 == 0b011) {
                // sra
                uint8_t MSB = regs[rd_rs1] >> 15;
                regs[rd_rs1] = regs[rd_rs1] >> regs[rs2];
                // TODO: could throw an error if the shift value is > 16
                if (MSB & 0b1) {
                    regs[rd_rs1] = regs[rd_rs1] | (0xFFFF << (16 - regs[rs2]));
                }
            } else if (funct4 == 0b0001 && funct3 == 0b100) {
                // or
                regs[rd_rs1] = regs[rd_rs1] | regs[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b101) {
                // and
                regs[rd_rs1] = regs[rd_rs1] & regs[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b110) {
                // xor
                regs[rd_rs1] = regs[rd_rs1] ^ regs[rs2];
            } else if (funct4 == 0b0000 && funct3 == 0b111) {
                // mv
                regs[rd_rs1] = regs[rs2];
            } else if (funct4 == 0b0100 && funct3 == 0b000) {
                // jr
                pc = regs[rs2];
                pcUpdated = true;
            } else if (funct4 == 0b1000 && funct3 == 0b000) {
                // jalr
                regs[rd_rs1] = pc + 2;
                // According to the ISA: All branches and jumps are PC-relative, except for JALR
                pc = regs[rs2];
                pcUpdated = true;
            } else {
                log->fatal("Unknown R-type instruction");
            }
            break;
        }
        case 0x1: {
            // I-type: [15:9] imm[6:0] | [8:6] rd/rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t imm7 = (inst >> 9) & 0x7F;
            uint8_t imm3 = (inst >> 13) & 0x7;
            uint8_t rd_rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int16_t simm = (imm7 & 0x40) ? (imm7 | 0xFF80) : imm7;

            if (funct3 == 0b000) {
                // addi
                regs[rd_rs1] = regs[rd_rs1] + simm;
            } else if (funct3 == 0b001) {
                // slti
                if (regs[rd_rs1] < simm) {
                    regs[rd_rs1] = 1;
                } else {
                    regs[rd_rs1] = 0;
                }
            } else if (funct3 == 0b010) {
                // sltui
                if (regs[rd_rs1] < imm7) {
                    regs[rd_rs1] = 1;
                } else {
                    regs[rd_rs1] = 0;
                }
            } else if (funct3 == 0b011 && imm3 == 0b001) {
                // slli
                // TODO: double check on that because of the 3 MSBs being reserved
                simm = simm & 0xF;
                simm = (simm & 0x8) ? (simm | 0xFFF0) : simm;
                regs[rd_rs1] = regs[rd_rs1] << simm;
            } else if (funct3 == 0b011 && imm3 == 0b010) {
                // srli
                simm = simm & 0xF;
                simm = (simm & 0x8) ? (simm | 0xFFF0) : simm;
                regs[rd_rs1] = regs[rd_rs1] >> simm;
            } else if (funct3 == 0b011 && imm3 == 0b100) {
                // srai
                simm = simm & 0xF;
                simm = (simm & 0x8) ? (simm | 0xFFF0) : simm;
                uint8_t MSB = regs[rd_rs1] >> 15;
                regs[rd_rs1] = regs[rd_rs1] >> simm;
                if (MSB & 0b1) {
                    regs[rd_rs1] =
                        regs[rd_rs1] | (0xFFFF << (16 - simm));
                }
            } else if (funct3 == 0b100) {
                // ori
                regs[rd_rs1] = regs[rd_rs1] | simm;
            } else if (funct3 == 0b101) {
                // andi
                regs[rd_rs1] = regs[rd_rs1] & simm;
            } else if (funct3 == 0b110) {
                // xori
                regs[rd_rs1] = regs[rd_rs1] ^ simm;
            } else if (funct3 == 0b111) {
                // li
                regs[rd_rs1] = simm;
            } else {
                log->fatal("Unknown I-type instruction");
            }
            break;
        }
        case 0x2: {
            // B-type (branch): [15:12] offset[4:1] | [11:9] rs2 | [8:6] rs1 | [5:3] funct3 | [2:0] opcode
            uint8_t offset = ((inst >> 12) & 0xF);
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int8_t sOffset = (offset & 0x8) ? (offset | 0xF0) : offset;
            int16_t sOffset16 = sOffset * 2;

            if (funct3 == 0b000) {
                // beq
                if (regs[rs1] == regs[rs2]) {
                    pc += 2 + sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b001) {
                // bne
                if (regs[rs1] != regs[rs2]) {
                    pc += 2 + sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b010) {
                // bz
                if (regs[rs1] == 0) {
                    pc += sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b011) {
                // bnz
                if (regs[rs1] != 0) {
                    pc += sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b100) {
                // blt
                if (static_cast<int16_t>(regs[rs1]) < static_cast<int16_t>(regs[
                        rs2])) {
                    pc += 2 + sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b101) {
                // bge
                if (static_cast<int16_t>(regs[rs1]) >= static_cast<int16_t>(regs
                        [rs2])) {
                    pc += 2 + sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b110) {
                // bltu
                if (regs[rs1] < regs[rs2]) {
                    pc += 2 + sOffset16;
                    pcUpdated = true;
                }
            } else if (funct3 == 0b111) {
                // bgeu
                if (regs[rs1] >= regs[rs2]) {
                    pc += 2 + sOffset16;
                    pcUpdated = true;
                }
            } else {
                log->fatal("Unknown B-type instruction");
            }
            break;
        }
        case 0x3: {
            // S-Type: [15:12] offset[3:0] | [11:9] rs2 | [8:6] rs1 | [5:3] funct3 | [2:0] opcode
            int8_t offset = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rs1 = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int8_t sOffset = (offset & 0x8) ? (offset | 0xF0) : offset;
            int16_t sOffset16 = sOffset;

            if (funct3 == 0b000) {
                // sb
                memory[regs[rs1] + sOffset16] = regs[rs2] & 0xFF;
            } else if (funct3 == 0b001) {
                // sw
                memory[regs[rs1] + sOffset16] = regs[rs2];
            } else {
                log->fatal("Unknown S-type instruction");
            }
            break;
        }
        case 0x4: {
            // L-Type: [15:12] offset[3:0] | [11:9] rs2 | [8:6] rd | [5:3] funct3 | [2:0] opcode
            int8_t offset = (inst >> 12) & 0xF;
            uint8_t rs2 = (inst >> 9) & 0x7;
            uint8_t rd = (inst >> 6) & 0x7;
            uint8_t funct3 = (inst >> 3) & 0x7;
            int8_t sOffset = (offset & 0x8) ? (offset | 0xF0) : offset;
            int16_t sOffset16 = sOffset;

            if (funct3 == 0b000) {
                // lb
                regs[rd] = memory[regs[rs2] + sOffset16];
                uint8_t MSB = regs[rd] >> 7;
                if (MSB & 0b1) {
                    regs[rd] = regs[rd] | 0xFF00;
                }
            } else if (funct3 == 0b001) {
                // lw
                regs[rd] = memory[regs[rs2] + sOffset16];
                regs[rd] = (memory[regs[rs2] + sOffset16 + 1] << 8) | regs[rd];
            } else if (funct3 == 0b100) {
                // lbu
                regs[rd] = memory[regs[rs2] + sOffset16];
            } else {
                log->fatal("Unknown L-type instruction");
            }
            break;
        }
        case 0x5: {
            // J-Type: [15:15] f | [14:9] I[9:4] | [8:6] rd | [5:3] I[3:1] | [2:0] opcode
            uint8_t f = (inst >> 15) & 0x1;
            uint8_t imm6 = (inst >> 9) & 0x3F;
            uint8_t rd = (inst >> 6) & 0x7;
            uint8_t imm3 = (inst >> 3) & 0x7;

            uint16_t imm = imm3 | (imm6 << 3);
            int16_t simm = (imm & 0x100) ? (imm | 0xFE00) : imm;
            int16_t simm16 = simm * 2;

            if (f == 0b0) {
                // j
                pc = pc + simm16;
                pcUpdated = true;
            } else if (f == 0b1) {
                // jal
                regs[rd] = pc + 2;
                pc = pc + simm16;
                pcUpdated = true;
            } else {
                log->fatal("Unknown J-type instruction");
            }
            break;
        }
        case 0x6: {
            // U-Type: [15:15] f | [14:9] I[15:10] | [8:6] rd | [5:3] I[9:7] | [2:0] opcode
            uint8_t f = (inst >> 15) & 0x1;
            uint8_t imm6 = (inst >> 9) & 0x3F;
            uint8_t rd = (inst >> 6) & 0x7;
            uint8_t imm3 = (inst >> 3) & 0x7;

            uint16_t imm = imm3 | (imm6 << 3);
            int16_t simm = (imm & 0x100) ? (imm | 0xFE00) : imm;

            if (f == 0b0) {
                // lui
                regs[rd] = simm << (16 - 9);
            } else if (f == 0b1) {
                // auipc
                regs[rd] = pc + (simm << (16 - 9));
            } else {
                log->fatal("Unknown J-type instruction");
            }
            break;
        }
        case 0x7: {
            // SYS-Type: [15:6] Service[11:0] | [5:3] funct3 | [2:0] opcode
            uint16_t service10 = (inst >> 6) & 0x3FF;
            uint8_t funct3 = (inst >> 3) & 0x7;

            if (funct3 == 0b000) {
                // TODO: what ECALLs should the program support ?!
                if (service10 == 1) {
                    // print integer in a0
                    output << static_cast<int16_t>(regs[6]) << endl;
                    // TODO: this may be considered an extra endl because it's not printed by the disassembled program
                } else if (service10 == 5) {
                    // print string in a0
                    uint16_t baseAddress = regs[6];
                    while (memory[baseAddress] != '\0') {
                        output << memory[baseAddress];
                        baseAddress++;
                    }
                } else if (service10 == 3) {
                    // terminate
                    return false;
                }
            } else {
                log->fatal("Unknown SYS-type instruction");
            }
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

        string disassembledInstruction = disassemble(inst);

        // Print human-readable assembly instruction to the log
        *log << setw(30) << left << format("0x{:04X}: {:04X} {}", pc, inst,
                       disassembledInstruction);

        // Execute the instruction on registers/memory and terminate if it's 'ecall 3'
        if (!executeInstruction(inst)) {
            break;
        }

        // Print the reg file after each execution next to the disassembled instruction
        *log << " |  Reg File: [ ";
        for (int i = 0; i < regs.size(); i++) {
            *log << regs[i];
            if (i != regs.size() - 1) {
                *log << ", ";
            }
        }
        *log << " ]\n";

        // Terminate if PC goes out of bounds
        if (pc >= MEM_SIZE) {
            break;
        }
    }

    // Print the reg file after each execution next to the disassembled instruction
    *log << " |  Reg File: [ ";
    for (int i = 0; i < regs.size(); i++) {
        *log << regs[i];
        if (i != regs.size() - 1) {
            *log << ", ";
        }
    }
    *log << " ]\n";

    // Dump the memory content after terminating execution
    memoryDump << "Final memory state after execution:\n";
    for (size_t i = 0; i < MEM_SIZE; i++) {
        memoryDump << setw(15) << left << format("0x{:04X}: ", i) << left << static_cast<int>(memory[i]) << endl;
    }

    *log << "Memory content has been dumped into ./Z16Simulator.memoryDump.txt\n";
}
