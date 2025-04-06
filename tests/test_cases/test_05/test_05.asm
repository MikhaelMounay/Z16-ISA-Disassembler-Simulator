# Test file for BLT, BGE, BLTU, and BGEU instructions

# the TEXT Section
    .text
    .org    0
main:
    # Test BLT instruction (signed)
    li a0, -5
    li a1, 5
    blt a0, a1, blt_taken
    li a0, 1
    ecall 1        # Should not be executed

blt_taken:
    li a0, 2
    ecall 1        # Should print 2

    # Test BGE instruction (signed)
    li a0, 10
    li a1, -10
    bge a0, a1, bge_taken
    li a0, 3
    ecall 1        # Should not be executed

bge_taken:
    li a0, 4
    ecall 1        # Should print 4

    # Test BLTU instruction (unsigned)
    li a0, 0x0000  # Largest unsigned 16-bit value
    li a1, 0x0001
    bltu a0, a1, bltu_not_taken
    li a0, 5
    ecall 1        # Shouldn't print 5

bltu_not_taken:
    li a0, 6
    ecall 1        # Should print 6

    # Test BGEU instruction (unsigned)
    li a0, 0x7FFF  # Smallest negative signed 16-bit value, but large unsigned value
    li a1, 0x7FF0  # Largest positive signed 16-bit value
    bgeu a0, a1, bgeu_taken
    li a0, 7
    ecall 1        # Should not be executed

bgeu_taken:
    li a0, 8
    ecall 1        # Should print 8

exit:
    li a0, 9
    ecall 1        # Should print 9
    ecall 3        # Terminate the program

    .data
    .org    0x100
