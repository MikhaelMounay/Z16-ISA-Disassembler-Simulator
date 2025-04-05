# the TEXT Section
    .text
    .org    0
main:

    # slti test
    li a0, 21		# A sample instruction
    slti a0, 4
    ecall 1		# should print 0
    # slt test
    li a0, 21
    li s0, 32
    slt a0, s0
    ecall 1		# should print 1
    # slli test
    li a0, 3
    slli a0, 2 
    ecall 1		# should print 3 * 2^2 = 12
    # srli test
    li a0, -1
    srli a0, 3 
    ecall 1		# should print 2^13 - 1 = 8191 
    # srai test
    li a0, -1
    srai a0, 3
    ecall 1		# should print -1

exit:
    ecall 3

    .data
    .org    0x100
