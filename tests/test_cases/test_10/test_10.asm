    .text
    .org 0
main:
    li a0, 32       # a0 = 32
    li a1, 2        # a1 = 2 (shift count in register)
    srl a0, a1      # a0 = a0 >> a1 (logical shift right): 32 >> 2 = 8
    ecall 1         # Print a0 (expected: 8)

    li a0, 8        # a0 = 8
    li a1, 2        # a1 = 2 (shift count)
    sll a0, a1      # a0 = a0 << a1 (logical shift left): 8 << 2 = 32
    ecall 1         # Print a0 (expected: 32)

    li a0, -16      # a0 = -16 (in two's complement)
    li a1, 2        # a1 = 2 (shift count)
    sra a0, a1      # a0 = a0 >> a1 (arithmetic shift right): -16 >> 2 = -4
    ecall 1         # Print a0 (expected: -4)

    li a0, 3        # a0 = 3
    li a1, 5        # a1 = 5
    sltu a0, a1     # a0 = (3 < 5) ? 1 : 0  → 1 (result in a0)
    ecall 1         # Print a0 (expected: 1)

    li a0, 1        # a0 = 1 (for comparison)
    sltui a0, 4     # a0 = (1 < 4) ? 1 : 0  → 1
    ecall 1         # Print a0 (expected: 1)

exit:
    ecall 3         # Exit program

    .data
    .org 0x100
