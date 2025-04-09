# V1.0

## Class Diagram

![class_diagram_v1.0.png](v1.0/class_diagram_v1.0.png)

## [Change Log](CHANGELOG.md)

## Challenges Faced During Development
- Some issues regarding assembling files using the Z16 custom assembler regarding the existing bugs in the version of the assembler available during the development process.
- Correctly parsing offset/immediate values, especially 2's-complement-signed ones.
- Correctly implementing the B-type instructions which needed thorough debugging to debug several off-by-one bugs found during testing.

## Usage of AI
- Generative AI tools have been utilized to help catching some errors and generating/validating some test cases for the program.

## Test Coverage for the Z16 ISA


| #  | Instruction | Tests Covering It                                          |
|----|-------------|------------------------------------------------------------|
| 01 | ADD         | 01, 11                                                     |
| 02 | SUB         | 11                                                         |
| 03 | SLT         | 06                                                         |
| 04 | SLTU        | 10                                                         |
| 05 | SLL         | 10                                                         |
| 06 | SRL         | 10                                                         |
| 07 | SRA         | 10                                                         |
| 08 | OR          | 14                                                         |
| 09 | AND         | 14                                                         |
| 10 | XOR         | 14                                                         |
| 11 | MV          | 04, 14                                                     |
| 12 | JR          | 07                                                         |
| 13 | JALR        | 07                                                         |
|    |             |                                                            |
| 14 | ADDI        | 01, 02, 03, 07, 11, 13                                     |
| 15 | SLTI        | 06                                                         |
| 16 | SLTUI       | 10                                                         |
| 17 | SLLI        | 06                                                         |
| 18 | SRLI        | 06                                                         |
| 19 | SRAI        | 06                                                         |
| 20 | ORI         | 14                                                         |
| 21 | ANDI        | 14                                                         |
| 22 | XORI        | 14                                                         |
| 23 | LI          | 01, 02, 03, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15         |
|    |             |                                                            |
| 24 | BEQ         | 08                                                         |
| 25 | BNE         | 01, 08                                                     |
| 26 | BZ          | 03, 08                                                     |
| 27 | BNZ         | 08                                                         |
| 28 | BLT         | 09                                                         |
| 29 | BGE         | 09                                                         |
| 30 | BLTU        | 09                                                         |
| 31 | BGEU        | 09                                                         |
|    |             |                                                            |
| 32 | SB          | 12, 13, 15                                                 |
| 33 | SW          | 13                                                         |
|    |             |                                                            |
| 34 | LB          | 12                                                         |
| 35 | LW          | 13                                                         |
| 36 | LBU         | 15                                                         |
|    |             |                                                            |
| 37 | J           | 07                                                         |
| 38 | JAL         | 02, 04, 07                                                 |
|    |             |                                                            |
| 39 | LUI         | 04, 05                                                     |
| 40 | AUIPC       | 04, 05                                                     |
|    |             |                                                            |
| 41 | ECALL 1     | 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 13, 14, 15     |
| 42 | ECALL 5     | 12, 13                                                     |
| 43 | ECALL 3     | 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15 |

### Coverage Matrix


| #  | Inst/Test | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 | 13 | 14 | 15 |  
|----|-----------|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| 01 | ADD       | X  |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |
| 02 | SUB       |    |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |
| 03 | SLT       |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |    |
| 04 | SLTU      |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |
| 05 | SLL       |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |
| 06 | SRL       |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |
| 07 | SRA       |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |
| 08 | OR        |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |
| 09 | AND       |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |
| 10 | XOR       |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |
| 11 | MV        |    |    |    | X  |    |    |    |    |    |    |    |    |    | X  |    |
| 12 | JR        |    |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |
| 13 | JALR      |    |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 14 | ADDI      | X  | X  | X  |    |    |    | X  |    |    |    | X  |    | X  |    |    |
| 15 | SLTI      |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |    |
| 16 | SLTUI     |    |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |
| 17 | SLLI      |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |    |
| 18 | SRLI      |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |    |
| 19 | SRAI      |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |    |
| 20 | ORI       |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |
| 21 | ANDI      |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |
| 22 | XORI      |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |
| 23 | LI        | X  | X  | X  |    |    | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 24 | BEQ       |    |    |    |    |    |    |    | X  |    |    |    |    |    |    |    |
| 25 | BNE       | X  |    |    |    |    |    |    | X  |    |    |    |    |    |    |    |
| 26 | BZ        |    |    | X  |    |    |    |    | X  |    |    |    |    |    |    |    |
| 27 | BNZ       |    |    |    |    |    |    |    | X  |    |    |    |    |    |    |    |
| 28 | BLT       |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |    |
| 29 | BGE       |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |    |
| 30 | BLTU      |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |    |
| 31 | BGEU      |    |    |    |    |    |    |    |    | X  |    |    |    |    |    |    |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 32 | SB        |    |    |    |    |    |    |    |    |    |    |    | X  | X  |    | X  |
| 33 | SW        |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |    |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 34 | LB        |    |    |    |    |    |    |    |    |    |    |    | X  |    |    |    |
| 35 | LW        |    |    |    |    |    |    |    |    |    |    |    |    | X  |    |    |
| 36 | LBU       |    |    |    |    |    |    |    |    |    |    |    |    |    |    | X  |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 37 | J         |    |    |    |    |    |    | X  |    |    |    |    |    |    |    |    |
| 38 | JAL       |    | X  |    | X  |    |    | X  |    |    |    |    |    |    |    |    |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 39 | LUI       |    |    |    | X  | X  |    |    |    |    |    |    |    |    |    |    |
| 40 | AUIPC     |    |    |    | X  | X  |    |    |    |    |    |    |    |    |    |    |
|    |           |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 41 | ECALL 1   | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  |    | X  | X  | X  |
| 42 | ECALL 5   |    |    |    |    |    |    |    |    |    |    |    | X  | X  |    |    |
| 43 | ECALL 3   | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  |
