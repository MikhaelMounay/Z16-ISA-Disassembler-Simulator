    .text
    .org 0
main:
    li a0, 50       # a0 = 50
    li a1, 20       # a1 = 20

    add a0, a1     # a0 = a0 + a1: 50 + 20 = 70
    ecall 1        # Print a0

    sub a0, a1     # a0 = a0 - a1: 70 - 20 = 50
    ecall 1        # Print a0

    addi a0, 30    # a0 = a0 + 30: 50 + 30 = 80
    ecall 1        # Print a0

    ecall 3        # Exit program

    .data
    .org 0x100
