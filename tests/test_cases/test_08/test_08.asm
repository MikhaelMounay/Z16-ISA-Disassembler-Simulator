# Test file for beq, bz, bne, and bnz instructions

# the TEXT Section
    .text
    .org    0
main:
    # Test beq instruction
    li a0, 6
    li a1, 6
    beq a0, a1, equal_branch
    li a0, 1
    ecall 1        # Should not be executed

equal_branch:
    li a0, 2
    ecall 1        # Should print 2

    # Test bz instruction
    li a0, 0
    bz a0, zero_branch
    li a0, 3
    ecall 1        # Should not be executed

zero_branch:
    li a0, 4
    ecall 1        # Should print 4

    # Test bne instruction
    li a0, 6
    li a1, 7
    bne a0, a1, not_equal_branch
    li a0, 5
    ecall 1        # Should not be executed

not_equal_branch:
    li a0, 6
    ecall 1        # Should print 6

    # Test bnz instruction
    li a0, 1
    bnz a0, non_zero_branch
    li a0, 7
    ecall 1        # Should not be executed

non_zero_branch:
    li a0, 8
    ecall 1        # Should print 8

exit:
    li a0, 9
    ecall 1        # Should print 9
    ecall 3        # Terminate the program

    .data
    .org    0x100
