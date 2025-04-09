# the TEXT Section
    .text
    .org    0
main:

    lui a0, 4      # A sample instruction
    ecall 1        # should print 4 * 2^7 = 512
    auipc a0, 12   # should print (PC = 4) + 13 * 2^7 = 1540
    ecall 1

exit:
    ecall 3

    .data
    .org    0x100
