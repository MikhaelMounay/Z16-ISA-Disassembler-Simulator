    .text
    .org 0
main:
    li x0, 0x3F         # x0 = 0x3F (base address)
    li x1, 0x3A         # x1 = 0x3A (58 in decimal)
    sb x1, 0(x0)        # store byte at address 0x3F

    lbu a0, 0(x0)       # load byte at 0(x0) : should load 0x3A (58), zero-extended
    ecall 1             # Should print 58

    li x1, 0x3E         # x1 = 0x3E (62)
    sb x1, 1(x0)        # store 0x3E at address 0x40

    lbu a0, 1(x0)       # load byte at 1(x0) : should load 0x3E (62)
    ecall 1             # Should print 62

    li x1, 0x33         # x1 = 0x33 (51 in decimal)
    sb x1, -1(x0)       # store at -1(a0) = 0x33

    lbu a0, -1(x0)      # should load 0x33 (51)
    ecall 1             # Should print 51

    ecall 3             # exit

    .data
    .org 0x100
